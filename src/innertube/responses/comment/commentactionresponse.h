#pragma once
#include <QJsonArray>

namespace InnertubeEndpoints
{
    struct CommentActionResponse
    {
        QJsonArray actionResults;
        QJsonArray actions;
    };
}
