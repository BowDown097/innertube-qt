#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct MetadataBadge
    {
        QString accessibilityLabel;
        QString iconType;
        QString label;
        QString style;
        QString tooltip;

        MetadataBadge() = default;

        explicit MetadataBadge(const QJsonValue& metadataBadgeRenderer)
            : accessibilityLabel(metadataBadgeRenderer["accessibilityData"]["label"].toString()),
              iconType(metadataBadgeRenderer["icon"]["iconType"].toString()),
              label(metadataBadgeRenderer["label"].toString()),
              style(metadataBadgeRenderer["style"].toString()),
              tooltip(metadataBadgeRenderer["tooltip"].toString()) {}

        explicit MetadataBadge(const QString& imageName)
        {
            if (imageName == "CHECK_CIRCLE_FILLED")
                label = "✔";
            else if (imageName == "AUDIO_BADGE")
                label = "♪";
        }
    };
}
