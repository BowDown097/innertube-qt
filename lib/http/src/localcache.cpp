#include "localcache.h"
#include <QCryptographicHash>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>

LocalCache* LocalCache::instance(const char* name)
{
    static QMap<QByteArray, LocalCache*> instances;
    if (auto it = instances.constFind(QByteArray::fromRawData(name, strlen(name))); it != instances.constEnd())
        return it.value();

    LocalCache* instance = new LocalCache(name);
    instances.insert(instance->getName(), instance);
    return instance;
}

LocalCache::LocalCache(const QByteArray& name) : name(name)
{
    directory = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + '/' + QLatin1String(name) + '/';
#ifdef HTTP_DEBUG
    hits = 0;
    misses = 0;
#endif
}

LocalCache::~LocalCache()
{
#ifdef HTTP_DEBUG
    debugStats();
#endif
}

void LocalCache::clear()
{
#ifdef HTTP_DEBUG
    hits = 0;
    misses = 0;
#endif
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
        qint64 size = file.size();
        file.remove();
        totalSize -= size;
    }

#ifdef HTTP_DEBUG
    debugStats();
    if (removedFiles > 0)
    {
        qDebug() << "Removed:" << removedFiles << "Kept:" << cacheItems.count() - removedFiles
                 << "New Size:" << totalSize;
    }
#endif

    size = totalSize;
    mutex.unlock();
}

QByteArray LocalCache::hash(const QByteArray& s)
{
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(s);
    const QByteArray h = QByteArray::number(*(qlonglong *)hash.result().constData(), 36);
    return h.at(0) + '/' + h.at(1) + '/' + h.mid(2);
}

void LocalCache::insert(const QByteArray& key, const QByteArray& value)
{
#ifdef HTTP_DEBUG
    qDebug() << "Inserting" << key;
#endif

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
                  (maxSeconds == 0 || QFileInfo(path).birthTime().secsTo(
                                              QDateTime::currentDateTimeUtc()) < maxSeconds);
#ifdef HTTP_DEBUG
    if (!cached)
        misses++;
#endif
    return cached;
}

QByteArray LocalCache::possiblyStaleValue(const QByteArray& key)
{
    if (QFile file(cachePath(key)); file.open(QIODevice::ReadOnly))
    {
#ifdef HTTP_DEBUG
        hits++;
#endif
        return file.readAll();
    }

#ifdef HTTP_DEBUG
    misses++;
#endif
    return QByteArray();
}

QByteArray LocalCache::value(const QByteArray& key)
{
    const QString path = cachePath(key);
    if (!isCached(path))
        return QByteArray();

    if (QFile file(path); file.open(QIODevice::ReadOnly))
    {
#ifdef HTTP_DEBUG
        hits++;
#endif
        return file.readAll();
    }
    else
    {
        qWarning() << file.fileName() << file.errorString();
#ifdef HTTP_DEBUG
        misses++;
#endif
        return QByteArray();
    }
}

#ifdef HTTP_DEBUG
void LocalCache::debugStats()
{
    if (int total = hits + misses; total > 0)
    {
        qDebug() << "Cache:" << name << '\n'
                 << "Inserts:" << insertCount << '\n'
                 << "Requests:" << total << '\n'
                 << "Hits:" << hits << (hits * 100) / total << "%\n"
                 << "Misses:" << misses << (misses * 100) / total << "%";
    }
}
#endif
