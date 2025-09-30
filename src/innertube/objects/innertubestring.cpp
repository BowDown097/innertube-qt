#include "innertubestring.h"
#include <QJsonArray>
#include <QUrlQuery>

void truncateUrlString(QString& url, bool prefix)
{
    constexpr int MaxUrlLength = 37;
    if (prefix)
    {
        url.prepend("https://www.youtube.com");
    }
    if (url.length() > MaxUrlLength)
    {
        url.truncate(MaxUrlLength);
        url.append("...");
    }
}

void insertEmoji(QString& str, const QJsonValue& emoji)
{
    str += QStringLiteral("<img src=\"%1\" width=\"20\" height=\"20\">").arg(
        emoji["image"]["thumbnails"][0]["url"].toString());
}

void insertBrowseEndpoint(
    QString& href, QString& text, const QJsonValue& browseEndpoint,
    const QJsonValue& navigationEndpoint, bool useLinkText)
{
    const QString browseId = browseEndpoint["browseId"].toString();
    if (browseId.startsWith("UC"))
    {
        text.replace(text.indexOf('/'), 1, "").replace("\u202A", "");
        if (text[0] != '@')
            text.prepend('@');
        href = "/channel/" + browseId;
    }
    else if (browseId.startsWith("FE"))
    {
        href = navigationEndpoint["commandMetadata"]["webCommandMetadata"]["url"].toString();
        if (!useLinkText)
        {
            text = href;
            truncateUrlString(text, true);
        }
    }
}

void insertOtherNavEndpoint(QString& href, QString& text, const QJsonValue& navigationEndpoint, bool useLinkText)
{
    href = navigationEndpoint["commandMetadata"]["webCommandMetadata"]["url"].toString();
    if (const QJsonValue watchEndpoint = navigationEndpoint["watchEndpoint"]; watchEndpoint.isObject())
    {
        if (!watchEndpoint["continuePlayback"].isBool())
        {
            if (!useLinkText)
            {
                text = "https://www.youtube.com" + href;
            }
        }
        else
        {
            href += "&continuePlayback=1";
        }
    }

    if (!useLinkText)
        truncateUrlString(text, false);
}

void insertUrlEndpoint(QString& href, QString& text, const QJsonValue& urlEndpoint, bool useLinkText)
{
    const QString urlStr = urlEndpoint["url"].toString();
    const QUrl url(urlStr);
    const QUrlQuery urlQuery(url);

    if (urlQuery.hasQueryItem("q"))
    {
        href = QUrl::fromPercentEncoding(urlQuery.queryItemValue("q").toUtf8());
        if (!useLinkText)
            text = href;
    }
    else if (urlStr.contains("youtube.com/channel"))
    {
        href = url.path();
        if (!useLinkText)
            text = urlStr;
    }
    else
    {
        href = urlStr;
        if (!useLinkText)
            text = href;
    }

    if (!useLinkText)
        truncateUrlString(text, false);
}

void insertNavigationEndpoint(QString& str, const QJsonValue& navigationEndpoint, QString text, bool useLinkText)
{
    QString href;

    if (const QJsonValue urlEndpoint = navigationEndpoint["urlEndpoint"]; urlEndpoint.isObject())
        insertUrlEndpoint(href, text, urlEndpoint, useLinkText);
    else if (const QJsonValue browseEndpoint = navigationEndpoint["browseEndpoint"]; browseEndpoint.isObject())
        insertBrowseEndpoint(href, text, browseEndpoint, navigationEndpoint, useLinkText);
    else
        insertOtherNavEndpoint(href, text, navigationEndpoint, useLinkText);

    str += QStringLiteral("<a href=\"%1\">%2</a>").arg(href, text);
}

void insertTextFormatted(QString& str, const InnertubeObjects::InnertubeRun& run)
{
    QString style;
    if (run.strikeOut)
        style += "text-decoration: line-through;";
    if (run.style != QFont::StyleNormal)
        style += "font-style: italic;";
    if (run.weight != QFont::Normal)
        style += QStringLiteral("font-weight: %1;").arg(run.weight);

    QString escaped = run.text.toHtmlEscaped().replace('\n', "<br>");
    if (!style.isEmpty())
        str += QStringLiteral("<span style=\"%1\">%2</span>").arg(style, escaped);
    else
        str += escaped;
}

namespace InnertubeObjects
{
    InnertubeString::InnertubeString(const QString& text)
        : accessibilityLabel(text), text(text)
    {
        runs.append(InnertubeRun(text));
    }

    InnertubeString::InnertubeString(const QJsonValue& textVal)
        : accessibilityLabel(textVal["accessibility"]["accessibilityData"]["label"].toString())
    {
        bool hasSimpleText{};
        if (QString simpleText = textVal["simpleText"].toString(); !simpleText.isEmpty())
        {
            text = simpleText;
            hasSimpleText = true;
        }

        const QJsonArray runsJson = textVal["runs"].toArray();
        for (const QJsonValue& v : runsJson)
        {
            const QString runText = v["text"].toString();
            runs.append(InnertubeRun(runText, v["navigationEndpoint"], v["emoji"]));
            if (!hasSimpleText)
                text += runText;
        }
    }

    QString InnertubeString::toRichText(bool useLinkText) const
    {
        QString out;
        out.reserve(text.size() * 2);

        for (const InnertubeRun& run : runs)
        {
            if (run.emoji.isObject())
                insertEmoji(out, run.emoji);
            else if (run.navigationEndpoint.isObject())
                insertNavigationEndpoint(out, run.navigationEndpoint, run.text, useLinkText);
            else
                insertTextFormatted(out, run);
        }

        return out;
    }
}
