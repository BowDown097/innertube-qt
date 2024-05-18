#pragma once
#include <QJsonValue>

namespace InnertubeObjects
{
    struct ButtonViewModel
    {
        QString accessibilityId;
        QString accessibilityText;
        QString buttonSize;
        QString iconName;
        bool isFullWidth;
        QJsonValue onTap;
        QJsonValue onVisible;
        QString state;
        QString style;
        QString targetId;
        QString title;
        QString tooltip;
        QString type;

        ButtonViewModel() = default;
        explicit ButtonViewModel(const QJsonValue& buttonViewModel)
            : accessibilityId(buttonViewModel["accessibilityId"].toString()),
              accessibilityText(buttonViewModel["accessibilityText"].toString()),
              buttonSize(buttonViewModel["buttonSize"].toString()),
              iconName(buttonViewModel["iconName"].toString()),
              isFullWidth(buttonViewModel["isFullWidth"].toBool()),
              onTap(buttonViewModel["onTap"]),
              onVisible(buttonViewModel["onVisible"]),
              state(buttonViewModel["state"].toString()),
              style(buttonViewModel["style"].toString()),
              targetId(buttonViewModel["targetId"].toString()),
              title(buttonViewModel["title"].toString()),
              tooltip(buttonViewModel["tooltip"].toString()),
              type(buttonViewModel["type"].toString()) {}
    };
}
