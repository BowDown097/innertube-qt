#include "thumbnailhoveroverlaytoggleactionsviewmodel.h"
#include <QJsonArray>

namespace InnertubeObjects
{
    ThumbnailHoverOverlayToggleActionsViewModel::ThumbnailHoverOverlayToggleActionsViewModel(
        const QJsonValue& thumbnailHoverOverlayToggleActionsViewModel)
    {
        const QJsonArray buttonsJson = thumbnailHoverOverlayToggleActionsViewModel["buttons"].toArray();
        for (const QJsonValue& button : buttonsJson)
            buttons.append(ToggleButtonViewModel(button["toggleButtonViewModel"]));
    }
}
