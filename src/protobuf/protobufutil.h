#pragma once
#include <QByteArray>

namespace ProtobufUtil
{
    QString randomString(qsizetype count);
    QByteArray uleb128(uint64_t val);
}
