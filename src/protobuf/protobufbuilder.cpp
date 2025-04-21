#include "protobufbuilder.h"
#include "protobufutil.h"
#include <QUrl>

QString ProtobufBuilder::urlEncodedBase64() const
{
    return QString::fromUtf8(QUrl::toPercentEncoding(QString::fromUtf8(m_data.toBase64(QByteArray::Base64UrlEncoding))));
}

ProtobufBuilder& ProtobufBuilder::bytes(int field, const QByteArray& val)
{
    this->field(field, 2);
    writeVarint(val.size());
    m_data.append(val);
    return *this;
}

ProtobufBuilder& ProtobufBuilder::field(int field, uint8_t wireType)
{
    return writeVarint((field << 3) | (wireType & 0x07));
}

ProtobufBuilder& ProtobufBuilder::string(int field, const QString& val)
{
    return bytes(field, val.toUtf8());
}

ProtobufBuilder& ProtobufBuilder::varint(int field, uint64_t val)
{
    this->field(field, 0);
    return writeVarint(val);
}

ProtobufBuilder& ProtobufBuilder::writeVarint(uint64_t val)
{
    m_data.append(ProtobufUtil::uleb128(val));
    return *this;
}
