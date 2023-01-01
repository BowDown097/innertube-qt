#ifndef COMMANDMETADATA_H
#define COMMANDMETADATA_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class CommandMetadata
    {
    public:
        QString apiUrl;
        int rootVe;
        QString url;
        QString webPageType;
        explicit CommandMetadata(const QJsonValue& commandMetadata);
    };
}

#endif // COMMANDMETADATA_H
