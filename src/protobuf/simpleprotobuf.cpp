// much of this logic comes from https://github.com/Nightlinbit/yt-search-params and https://github.com/Rehike/Rehike, ported to C++
#include "simpleprotobuf.h"

QByteArray SimpleProtobuf::compile(const QVariantMap& obj, const QVariantMap& fields)
{
    QByteArray response;
    for (QVariantMap::const_iterator iter = obj.begin(); iter != obj.end(); ++iter)
        response += compileKeyValuePair(iter.key(), iter.value(), fields);
    return response.toLower().replace(" ", "");
}

QByteArray SimpleProtobuf::compileKeyValuePair(const QString& key, const QVariant& val, const QVariantMap& fields)
{
    if (!fields.contains(key))
        return QByteArray();

    const QVariantList field = fields[key].toList();
    if (field.isEmpty())
        return QByteArray();

    bool ok;
    int wireType = field[1].toInt(&ok);
    if (!ok)
        return QByteArray();

    QByteArray keyHeader = compileKey(field);
    switch (wireType)
    {
    case 0: // number
        return keyHeader + uleb128(val.toInt()).toHex();
    case 2: // map (could also be a string but we aren't concerned with supporting it)
        return keyHeader + compileLd(compile(val.toMap(), field[2].toMap()));
    }

    return QByteArray();
}

QByteArray SimpleProtobuf::compileKey(const QVariantList &keyField)
{
    bool numOk, wireOk;
    int num = keyField[0].toInt(&numOk);
    int wireType = keyField[1].toInt(&wireOk);
    return numOk && wireOk ? uleb128((num << 3) | wireType).toHex() : QByteArray("00");
}

QByteArray SimpleProtobuf::compileLd(const QByteArray& in)
{
    int ldLen = (in.length() + (in.length() % 2)) / 2;
    return uleb128(ldLen).toHex() + in;
}

QByteArray SimpleProtobuf::padded(const QString& str)
{
    return QByteArray("\x0a" + uleb128(str.length()) + str.toLatin1() + "\x28" + uleb128(time(0))).toBase64().toPercentEncoding();
}

QByteArray SimpleProtobuf::uleb128(uint64_t val)
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
