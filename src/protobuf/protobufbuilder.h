#pragma once
#include <QList>

// courtesy of https://github.com/kkdai/youtube/blob/master/client.go
class ProtobufBuilder
{
public:
    const QByteArray& data() const { return m_data; }
    QString urlEncodedBase64() const;

    ProtobufBuilder& bytes(int field, const QByteArray& val);
    ProtobufBuilder& field(int field, uint8_t wireType);
    ProtobufBuilder& string(int field, const QString& val);
    ProtobufBuilder& varint(int field, uint64_t val);
private:
    QByteArray m_data;

    ProtobufBuilder& writeVarint(uint64_t val);
};
