#ifndef COMMENTACTIONRESPONSE_H
#define COMMENTACTIONRESPONSE_H
#include <QJsonArray>

namespace InnertubeEndpoints
{
    struct CommentActionResponse
    {
        QJsonArray actionResults;
        QJsonArray actions;
    };
}

#endif // COMMENTACTIONRESPONSE_H
