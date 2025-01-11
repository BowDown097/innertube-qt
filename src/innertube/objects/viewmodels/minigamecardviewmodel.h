#pragma once
#include "buttonviewmodel.h"
#include "innertube/objects/images/responsiveimage.h"

namespace InnertubeObjects
{
    struct EntityRedesignExperiments
    {
        bool changePlayablesLayoutWithContentTypeBadge{};
        bool changePlayablesLayoutWithCta{};
        bool changePlayablesLayoutWithCtaBelowMetadata{};
        bool enable11ThumbnailOnHomeShelves{};
        bool enable169ThumbnailOnHomeShelves{};
        bool enableGameConsoleWithCinematicContainer{};
        bool enableGameConsoleWithSubtleColor{};
        bool enableResponsiveWidth{};

        EntityRedesignExperiments() = default;
        explicit EntityRedesignExperiments(const QJsonValue& entityRedesignExperiments)
            : changePlayablesLayoutWithContentTypeBadge(
                  entityRedesignExperiments["changePlayablesLayoutWithContentTypeBadge"].toBool()),
              changePlayablesLayoutWithCta(
                  entityRedesignExperiments["changePlayablesLayoutWithCta"].toBool()),
              changePlayablesLayoutWithCtaBelowMetadata(
                  entityRedesignExperiments["changePlayablesLayoutWithCtaBelowMetadata"].toBool()),
              enable11ThumbnailOnHomeShelves(
                  entityRedesignExperiments["enable11ThumbnailOnHomeShelves"].toBool()),
              enable169ThumbnailOnHomeShelves(
                  entityRedesignExperiments["enable169ThumbnailOnHomeShelves"].toBool()),
              enableGameConsoleWithCinematicContainer(
                  entityRedesignExperiments["enableGameConsoleWithCinematicContainer"].toBool()),
              enableGameConsoleWithSubtleColor(
                  entityRedesignExperiments["enableGameConsoleWithSubtleColor"].toBool()),
              enableResponsiveWidth(
                  entityRedesignExperiments["enableResponsiveWidth"].toBool()) {}
    };

    struct InlinePlaybackExperiments
    {
        bool disableCinematicContainer{};
        bool enableLoggingDirectivesForAndroidInlinePlayback{};
        bool enableSimplifiedAndroidUi{};
        bool enableSquaredThumbnails{};

        InlinePlaybackExperiments() = default;
        explicit InlinePlaybackExperiments(const QJsonValue& inlinePlaybackExperiments)
            : disableCinematicContainer(
                  inlinePlaybackExperiments["disableCinematicContainer"].toBool()),
              enableLoggingDirectivesForAndroidInlinePlayback(
                  inlinePlaybackExperiments["enableLoggingDirectivesForAndroidInlinePlayback"].toBool()),
              enableSimplifiedAndroidUi(
                  inlinePlaybackExperiments["enableSimplifiedAndroidUi"].toBool()),
              enableSquaredThumbnails(
                  inlinePlaybackExperiments["enableSquaredThumbnails"].toBool()) {}
    };

    // the color palette for this view model is different from the standard ColorPalette
    struct MiniGameCardColorPalette
    {
        uint32_t sectionTwoColor{};
        uint32_t sectionFourColor{};
        uint32_t textPrimaryColor{};

        MiniGameCardColorPalette() = default;
        explicit MiniGameCardColorPalette(const QJsonValue& colorPalette)
            : sectionTwoColor(colorPalette["sectionTwoColor"].toVariant().toUInt()),
              sectionFourColor(colorPalette["sectionFourColor"].toVariant().toUInt()),
              textPrimaryColor(colorPalette["textPrimaryColor"].toVariant().toUInt()) {}
    };

    struct MiniGameCardViewModel
    {
        QString accessibilityText;
        ButtonViewModel actionButton;
        MiniGameCardColorPalette colorPalette;
        EntityRedesignExperiments entityRedesignExperiments;
        QString genre;
        ResponsiveImage image;
        int indexInShelf{};
        InlinePlaybackExperiments inlinePlaybackExperiments;
        QString layout;
        QJsonValue onTap;
        ButtonViewModel overflowButton;
        int responsiveNumVisibleItems{};
        QString style;
        QString title;

        MiniGameCardViewModel() = default;
        explicit MiniGameCardViewModel(const QJsonValue& miniGameCardViewModel)
            : accessibilityText(miniGameCardViewModel["accessibilityText"].toString()),
              actionButton(miniGameCardViewModel["actionButton"]["buttonViewModel"]),
              colorPalette(miniGameCardViewModel["colorPalette"]),
              entityRedesignExperiments(miniGameCardViewModel["entityRedesignExperiments"]),
              genre(miniGameCardViewModel["genre"].toString()),
              image(miniGameCardViewModel["image"]["sources"]),
              indexInShelf(miniGameCardViewModel["indexInShelf"].toInt()),
              inlinePlaybackExperiments(miniGameCardViewModel["inlinePlaybackExperiments"]),
              layout(miniGameCardViewModel["layout"].toString()),
              onTap(miniGameCardViewModel["onTap"]),
              overflowButton(miniGameCardViewModel["overflowButton"]["buttonViewModel"]),
              responsiveNumVisibleItems(miniGameCardViewModel["responsiveNumVisibleItems"].toInt()),
              style(miniGameCardViewModel["style"].toString()),
              title(miniGameCardViewModel["title"].toString()) {}
    };
}
