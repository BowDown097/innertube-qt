#ifndef METADATABADGE_H
#define METADATABADGE_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class MetadataBadge
    {
    public:
        QString accessibilityLabel;
        QString iconType;
        QString style;
        QString tooltip;

        MetadataBadge() = default;
        explicit MetadataBadge(const QJsonValue& metadataBadgeRenderer)
            : accessibilityLabel(metadataBadgeRenderer["accessibilityData"]["label"].toString()),
              iconType(metadataBadgeRenderer["icon"]["iconType"].toString()),
              style(metadataBadgeRenderer["style"].toString()),
              tooltip(metadataBadgeRenderer["tooltip"].toString()) {}
    };
}

#endif // METADATABADGE_H
