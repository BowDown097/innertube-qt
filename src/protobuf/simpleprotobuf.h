#ifndef SIMPLEPROTOBUF_H
#define SIMPLEPROTOBUF_H
#include <QVariantMap>

namespace SimpleProtobuf
{
    QByteArray compile(const QVariantMap& obj, const QVariantMap& fields);
    QByteArray padded(const QString& str);
};

#endif // SIMPLEPROTOBUF_H
