#include "innertubeplaybackcontext.h"

QJsonObject InnertubePlaybackContext::toJson() const
{
    if (!isContent)
    {
        return {
            { "lactMilliseconds", lactMilliseconds },
            { "vis", vis }
        };
    }
    else
    {
        return {
            { "contentPlaybackContext", QJsonObject {
                { "autoCaptionsDefaultOn", autoCaptionsDefaultOn },
                { "autonavState", autonavState },
                { "currentUrl", currentUrl },
                { "html5Preference", html5Preference },
                { "lactMilliseconds", lactMilliseconds },
                { "referer", referer },
                { "splay", splay },
                { "vis", vis }
            } }
        };
    }
}
