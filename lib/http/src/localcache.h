#pragma once
#include <QMutex>

/**
 * @brief Not thread-safe
 */
class LocalCache
{
public:
    static LocalCache* instance(const char* name);
    ~LocalCache();
    static QByteArray hash(const QByteArray& s);

    const QByteArray& getName() const { return name; }

    void setMaxSeconds(uint value) { maxSeconds = value; }
    void setMaxSize(uint value) { maxSize = value; }

    void clear();
    void insert(const QByteArray& key, const QByteArray& value);
    QByteArray possiblyStaleValue(const QByteArray& key);
    QByteArray value(const QByteArray& key);
private:
    LocalCache(const QByteArray& name);
    QString cachePath(const QByteArray& key) const { return directory + QLatin1String(key); }
    void expire();
    bool isCached(const QString& path);

#ifdef HTTP_DEBUG
    void debugStats();
#endif

    QString directory;
    uint insertCount{};
    uint maxSeconds = 86400 * 30;
    qint64 maxSize = 1024 * 1024 * 100;
    QMutex mutex;
    QByteArray name;
    qint64 size{};

#ifdef HTTP_DEBUG
    uint hits;
    uint misses;
#endif
};
