#ifndef PROTOBUFCOMPILER_H
#define PROTOBUFCOMPILER_H
#include <QVariantMap>

namespace ProtobufCompiler
{
    QByteArray compile(const QVariantMap& obj, QVariantMap fields = QVariantMap());
    QByteArray padded(const QString& str);
};

#endif // PROTOBUFCOMPILER_H
