#ifndef TOGGLEBUTTONVIEWMODEL_H
#define TOGGLEBUTTONVIEWMODEL_H
#include "buttonviewmodel.h"

namespace InnertubeObjects
{
    struct ToggleButtonViewModel
    {
        ButtonViewModel defaultButtonViewModel;
        QString identifier;
        bool isTogglingDisabled;
        ButtonViewModel toggledButtonViewModel;

        ToggleButtonViewModel() = default;
        explicit ToggleButtonViewModel(const QJsonValue& toggleButtonViewModel)
            : defaultButtonViewModel(toggleButtonViewModel["defaultButtonViewModel"]["buttonViewModel"]),
              identifier(toggleButtonViewModel["identifier"].toString()),
              isTogglingDisabled(toggleButtonViewModel["isTogglingDisabled"].toBool()),
              toggledButtonViewModel(toggleButtonViewModel["toggledButtonViewModel"]["buttonViewModel"]) {}
    };
}

#endif // TOGGLEBUTTONVIEWMODEL_H
