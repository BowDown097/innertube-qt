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
    };
}
