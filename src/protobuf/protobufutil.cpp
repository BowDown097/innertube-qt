#include "protobufutil.h"
#include <QRandomGenerator>
#include <QVariant>

namespace ProtobufUtil
{
    QString randomString(qsizetype count)
    {
        QString out;
        out.reserve(count);

        constexpr QLatin1String chars("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
        for (int i = 0; i < out.capacity(); i++)
            out += chars[QRandomGenerator::global()->bounded(chars.size())];

        return out;
    }

    QByteArray uleb128(uint64_t val)
    {
        uint8_t buf[128];
        size_t i = 0;
        do
        {
            if (i < 255)
            {
                uint8_t b = val & 0x7F;
                val >>= 7;
                if (val != 0)
                    b |= 0x80;
                buf[i++] = b;
            }
            else
            {
                return 0;
            }
        } while (val != 0);

        return QByteArray(reinterpret_cast<char*>(buf), i);
    }
}
