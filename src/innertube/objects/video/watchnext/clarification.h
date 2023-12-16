#ifndef CLARIFICATION_H
#define CLARIFICATION_H
#include "innertube/objects/innertubestring.h"
#include "innertube/objects/items/button.h"

namespace InnertubeObjects
{
    struct Clarification
    {
        Button actionButton;
        QString background;
        InnertubeString contentTitle;
        bool ctaHasBottomSection;
        QJsonValue endpoint;
        QJsonValue secondaryEndpoint;
        QString secondaryIconType;
        QString secondarySource;
        QString source;
        QString sourceIconType;
        QString style;
        InnertubeString text;

        explicit Clarification(const QJsonValue& clarificationRenderer)
            : actionButton(clarificationRenderer["actionButton"]["buttonRenderer"]),
              background(clarificationRenderer["background"].toString()),
              contentTitle(clarificationRenderer["contentTitle"]),
              ctaHasBottomSection(clarificationRenderer["ctaHasBottomSection"].toBool()),
              endpoint(clarificationRenderer["endpoint"]),
              secondaryEndpoint(clarificationRenderer["secondaryEndpoint"]),
              secondaryIconType(clarificationRenderer["secondaryIcon"]["iconType"].toString()),
              secondarySource(clarificationRenderer["secondarySource"]["simpleText"].toString()),
              source(clarificationRenderer["source"]["simpleText"].toString()),
              sourceIconType(clarificationRenderer["sourceIcon"]["iconType"].toString()),
              style(clarificationRenderer["style"].toString()),
              text(clarificationRenderer["text"]) {}
    };
}

#endif // CLARIFICATION_H
