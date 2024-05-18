#pragma once
#include <QVariantMap>

namespace ProtobufCompiler
{
    QByteArray compile(const QVariantMap& obj, QVariantMap fields = QVariantMap());
    QByteArray padded(const QString& str);
}
