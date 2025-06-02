#include "localcache.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QStandardPaths>

LocalCache* LocalCache::instance(const char* name)
{
    static std::unordered_map<QByteArray, std::unique_ptr<LocalCache>> instances;
    if (auto it = instances.find(QByteArray::fromRawData(name, strlen(name))); it != instances.end())
        return it->second.get();

    std::unique_ptr<LocalCache> instance(new LocalCache(name)); // make_unique can't be used because ctor is private
    LocalCache* instancePtr = instance.get();
    instances.emplace(instance->getName(), std::move(instance));
    return instancePtr;
}

LocalCache::LocalCache(const QByteArray& name)
    : directory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + '/' + QLatin1String(name) + '/'),
      name(name) {}

void LocalCache::clear()
{
    size = 0;
    insertCount = 0;
    mutex.lock();
    QDir(directory).removeRecursively();
    mutex.unlock();
}

void LocalCache::expire()
{
    if (!mutex.tryLock())
        return;

    QDirIterator dirIter(directory, QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QMultiMap<QDateTime, QString> cacheItems;
    qint64 totalSize = 0;
    while (dirIter.hasNext())
    {
        QString path = dirIter.next();
        QFileInfo info = dirIter.fileInfo();
        cacheItems.insert(info.birthTime(), path);
        totalSize += info.size();
    }

    int removedFiles = 0;
    qint64 goal = (maxSize * 9) / 10;

    for (auto it = cacheItems.constBegin(); it != cacheItems.constEnd(); ++it, ++removedFiles)
    {
        if (totalSize < goal)
            break;
        QFile file(it.value());
        qint64 fileSize = file.size();
        file.remove();
        totalSize -= fileSize;
    }

    size = totalSize;
    mutex.unlock();
}

QByteArray LocalCache::hash(const QByteArray& s)
{
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(s);
    const QByteArray h = QByteArray::number(*reinterpret_cast<const qlonglong *>(hash.result().constData()), 36);
    QByteArray p;
    p.reserve(h.length() + 2);
    p.append(h.at(0));
    p.append('/');
    p.append(h.at(1));
    p.append('/');
    p.append(h.mid(2));
    return p;
}

void LocalCache::insert(const QByteArray& key, const QByteArray& value)
{
    const QString path = cachePath(key);
    if (const QString parentDir = path.left(path.lastIndexOf('/')); !QFile::exists(parentDir))
        QDir().mkpath(parentDir);

    if (QFile file(path); file.open(QIODevice::WriteOnly))
    {
        file.write(value);
        if (size > 0)
            size += value.size();

        // expire cache every n inserts
        if (maxSize > 0 && ++insertCount % 100 == 0 && (size == 0 || size > maxSize))
            expire();
    }
    else
    {
        qWarning() << "Cannot create" << path;
    }
}

bool LocalCache::isCached(const QString& path)
{
    bool cached = QFile::exists(path) &&
        (maxSeconds == 0 || QFileInfo(path).birthTime().secsTo(QDateTime::currentDateTimeUtc()) < maxSeconds);
    return cached;
}

QByteArray LocalCache::possiblyStaleValue(const QByteArray& key)
{
    if (QFile file(cachePath(key)); file.open(QIODevice::ReadOnly))
        return file.readAll();
    return QByteArray();
}

QByteArray LocalCache::value(const QByteArray& key)
{
    const QString path = cachePath(key);
    if (!isCached(path))
        return QByteArray();

    if (QFile file(path); file.open(QIODevice::ReadOnly))
    {
        return file.readAll();
    }
    else
    {
        qWarning() << file.fileName() << file.errorString();
        return QByteArray();
    }
}
