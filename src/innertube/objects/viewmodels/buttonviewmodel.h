#ifndef BUTTONVIEWMODEL_H
#define BUTTONVIEWMODEL_H
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
        QString style;
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
              style(buttonViewModel["style"].toString()),
              title(buttonViewModel["title"].toString()),
              tooltip(buttonViewModel["tooltip"].toString()),
              type(buttonViewModel["type"].toString()) {}
    };
}

#endif // BUTTONVIEWMODEL_H
