#ifndef SIMPLEPROTOBUF_H
#define SIMPLEPROTOBUF_H
#include <QVariantMap>

class SimpleProtobuf
{
public:
    static QByteArray compile(const QVariantMap& obj, const QVariantMap& fields);
    static QByteArray padded(const QString& str);
    static QByteArray uleb128(uint64_t val);
private:
    static QByteArray compileKey(const QVariantList& keyField);
    static QByteArray compileKeyValuePair(const QString& key, const QVariant& val, const QVariantMap& fields);
    static QByteArray compileLd(const QByteArray& in);
};

#endif // SIMPLEPROTOBUF_H
