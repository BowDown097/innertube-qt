#include "protobufcompiler.h"

namespace ProtobufCompiler
{
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

    QByteArray compileKey(const QVariantList &keyField)
    {
        bool numOk, wireOk;
        int num = keyField[0].toInt(&numOk);
        int wireType = keyField[1].toInt(&wireOk);
        return numOk && wireOk ? uleb128((num << 3) | wireType).toHex() : QByteArray("00");
    }

    QByteArray compileLd(const QByteArray& in)
    {
        int ldLen = (in.length() + (in.length() % 2)) / 2;
        return uleb128(ldLen).toHex() + in;
    }

    QByteArray compileKeyValuePair(const QString& key, const QVariant& val, const QVariantMap& fields)
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
        int typeId = val.typeId();
        switch (wireType)
        {
        case 0:
            return keyHeader + uleb128(val.toInt()).toHex();
        case 1: // may not work
            return keyHeader + (typeId == QMetaType::Double
                                    ? QByteArray::fromHex(QByteArray::number(val.toDouble()))
                                    : QByteArray::fromHex(QByteArray::number(val.toLongLong())));
        case 2:
            switch (typeId)
            {
            case QMetaType::QVariantMap:
                return keyHeader + compileLd(compile(val.toMap(), field[2].toMap()));
            case QMetaType::QByteArray:
                return keyHeader + compileLd(val.toByteArray());
            default:
                return keyHeader + compileLd(val.toString().toLatin1().toHex());
            }
        case 5: // may not work
            return keyHeader + (typeId == QMetaType::Float
                                    ? QByteArray::fromHex(QByteArray::number(val.toFloat()))
                                    : QByteArray::fromHex(QByteArray::number(val.toInt())));
        }

        return QByteArray();
    }

    int resolveWireType(int typeId, const QVariant& variant)
    {
        switch (typeId)
        {
        case QMetaType::QVariantMap:
        case QMetaType::QString:
        case QMetaType::QByteArray:
            return 2;
        case QMetaType::Bool:
            return 0;
        case QMetaType::Int:
        case QMetaType::UInt:
        case QMetaType::Char32:
        case QMetaType::Float:
            return 5;
        case QMetaType::Double:
        case QMetaType::Long:
        case QMetaType::LongLong:
        case QMetaType::ULong:
        case QMetaType::ULongLong:
            return 1;
        default:
            bool ok;
            double value = variant.toDouble(&ok);
            if (ok)
            {
                if (value == floor(value))
                    return 0;
                else if (value == (int)value)
                    return 5;
            }
            return 1;
        }
    }

    QVariantMap compileFields(const QVariantMap& obj)
    {
        QVariantMap out;

        int i = 0;
        for (QVariantMap::const_iterator iter = obj.begin(); iter != obj.end(); ++iter)
        {
            const QString& key = iter.key();
            const QVariant& value = iter.value();
            int typeId = value.typeId();

            QVariantMap innerFields;
            int wireType = 0;

            if (typeId == QMetaType::QVariantList || typeId == QMetaType::QStringList)
            {
                QVariantList list = value.toList();
                for (int i = 0; i < list.size(); i++)
                {
                    const QVariant& innerValue = list.at(i);
                    int innerTypeId = innerValue.typeId();

                    if (innerTypeId == QMetaType::QVariantMap)
                        innerFields = compileFields(innerValue.toMap());

                    wireType = resolveWireType(innerTypeId, innerValue);
                    out.insert(QStringLiteral("%1_%2").arg(key).arg(i), QVariantList { i, wireType, innerFields });
                }
            }
            else
            {
                wireType = resolveWireType(typeId, value);
                if (typeId == QMetaType::QVariantMap)
                    innerFields = compileFields(value.toMap());
            }

            out.insert(key, QVariantList { ++i, wireType, innerFields });
        }

        return out;
    }

    QByteArray compile(const QVariantMap& obj, QVariantMap fields)
    {
        if (fields.isEmpty())
            fields = compileFields(obj);

        QByteArray response;

        for (QVariantMap::const_iterator iter = obj.begin(); iter != obj.end(); ++iter)
        {
            const QString& key = iter.key();
            const QVariant& value = iter.value();

            if (value.typeId() == QMetaType::QVariantList || value.typeId() == QMetaType::QStringList)
            {
                QVariantList list = value.toList();
                for (int i = 0; i < list.size(); i++)
                {
                    const QVariant& innerValue = list.at(i);
                    response += compileKeyValuePair(QStringLiteral("%1_%2").arg(key).arg(i), innerValue, fields);
                }
            }
            else
            {
                response += compileKeyValuePair(key, value, fields);
            }
        }

        return response.toLower().replace(" ", "");
    }

    QByteArray padded(const QString& str)
    {
        return QByteArray("\x0a" + uleb128(str.length()) + str.toLatin1() + "\x28" + uleb128(time(0))).toBase64().toPercentEncoding();
    }
}
