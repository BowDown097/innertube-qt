#include "protobufcompiler.h"
#include "protobufutil.h"
#include <cmath>

namespace ProtobufCompiler
{
    int resolveWireType(int metaType, const QVariant& variant)
    {
        switch (metaType)
        {
        case QMetaType::QVariantMap:
        case QMetaType::QString:
        case QMetaType::QByteArray:
            return 2;
        case QMetaType::Bool:
            return 0;
        case QMetaType::Int:
        case QMetaType::UInt:
    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        case QMetaType::Char32:
    #endif
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
    QByteArray compileKey(const QVariantList &keyField)
    {
        bool numOk, wireOk;
        int num = keyField[0].toInt(&numOk);
        int wireType = keyField[1].toInt(&wireOk);
        return numOk && wireOk ? ProtobufUtil::uleb128((num << 3) | wireType).toHex() : QByteArray("00");
    }

    QByteArray compileLd(const QByteArray& in)
    {
        int ldLen = (in.length() + (in.length() % 2)) / 2;
        return ProtobufUtil::uleb128(ldLen).toHex() + in;
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
        int metaType = val.userType();
        switch (wireType)
        {
        case 0:
            return keyHeader + ProtobufUtil::uleb128(val.toInt()).toHex();
        case 1: // may not work
            return keyHeader + (metaType == QMetaType::Double
                                    ? QByteArray::fromHex(QByteArray::number(val.toDouble()))
                                    : QByteArray::fromHex(QByteArray::number(val.toLongLong())));
        case 2:
            switch (metaType)
            {
            case QMetaType::QVariantMap:
                return keyHeader + compileLd(compile(val.toMap(), field[2].toMap()));
            case QMetaType::QByteArray:
                return keyHeader + compileLd(val.toByteArray());
            default:
                return keyHeader + compileLd(val.toString().toLatin1().toHex());
            }
        case 5: // may not work
            return keyHeader + (metaType == QMetaType::Float
                                    ? QByteArray::fromHex(QByteArray::number(val.toFloat()))
                                    : QByteArray::fromHex(QByteArray::number(val.toInt())));
        }

        return QByteArray();
    }

    QVariantMap compileFields(const QVariantMap& obj)
    {
        QVariantMap out;

        int i = 0;
        for (QVariantMap::const_iterator iter = obj.begin(); iter != obj.end(); ++iter)
        {
            const QString& key = iter.key();
            const QVariant& value = iter.value();
            int metaType = value.userType();

            QVariantMap innerFields;
            int wireType = 0;

            if (metaType == QMetaType::QVariantList || metaType == QMetaType::QStringList)
            {
                QVariantList list = value.toList();
                for (int j = 0; j < list.size(); j++)
                {
                    int innerMetaType = list[j].userType();
                    if (innerMetaType == QMetaType::QVariantMap)
                        innerFields = compileFields(list[j].toMap());

                    wireType = resolveWireType(innerMetaType, list[j]);
                    out.insert(QStringLiteral("%1_%2").arg(key).arg(j), QVariantList { j, wireType, innerFields });
                }
            }
            else
            {
                wireType = resolveWireType(metaType, value);
                if (metaType == QMetaType::QVariantMap)
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
            int metaType = value.userType();

            if (metaType == QMetaType::QVariantList || metaType == QMetaType::QStringList)
            {
                QVariantList list = value.toList();
                for (int i = 0; i < list.size(); i++)
                    response += compileKeyValuePair(QStringLiteral("%1_%2").arg(key).arg(i), list[i], fields);
            }
            else
            {
                response += compileKeyValuePair(key, value, fields);
            }
        }

        return response.toLower().replace(" ", "");
    }

    QByteArray compileEncoded(const QVariantMap& obj, QVariantMap fields)
    {
        return QByteArray::fromHex(compile(obj, fields)).toBase64().toPercentEncoding();
    }

    QByteArray padded(const QString& str)
    {
        return QByteArray(
            "\x0a" +
            ProtobufUtil::uleb128(str.length()) +
            str.toLatin1() +
            "\x28" +
            ProtobufUtil::uleb128(time(0)))
            .toBase64().toPercentEncoding();
    }
}
