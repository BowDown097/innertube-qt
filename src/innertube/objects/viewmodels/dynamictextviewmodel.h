#pragma once
#include "innertube/objects/dynamictext.h"
#include <optional>

namespace InnertubeObjects
{
    struct DynamicTextViewModel
    {
        bool alwaysShowTruncationText{};
        int maxLines{};
        QJsonValue rendererContext;
        std::optional<DynamicText> suffix;
        DynamicText text;
        std::optional<DynamicText> truncationText;

        DynamicTextViewModel() = default;
        explicit DynamicTextViewModel(const QJsonValue& viewModel, const QString& textKey = "text")
            : alwaysShowTruncationText(viewModel["alwaysShowTruncationText"].toBool()),
              maxLines(viewModel["maxLines"].toInt()),
              rendererContext(viewModel["rendererContext"]),
              suffix(viewModel["suffix"].isObject() ? std::make_optional(viewModel["suffix"]) : std::nullopt),
              text(viewModel[textKey]),
              truncationText(viewModel["truncationText"].isObject()
                             ? std::make_optional(viewModel["truncationText"]) : std::nullopt) {}
    };
}
