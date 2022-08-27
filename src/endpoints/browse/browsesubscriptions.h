#ifndef BROWSESUBSCRIPTIONS_H
#define BROWSESUBSCRIPTIONS_H
#include <endpoints/base/basebrowseendpoint.h>
#include <QFile>

namespace InnertubeEndpoints
{
    class BrowseSubscriptions : public BaseBrowseEndpoint
    {
        friend class ::InnerTube;
    public:
        QVector<InnertubeObjects::Video> videos;
    private:
        explicit BrowseSubscriptions(InnertubeContext* context, CurlEasy* easy, InnertubeAuthStore* authStore) : BaseBrowseEndpoint("FEsubscriptions", context, easy, authStore)
        {
            QFile file("data.json");
            file.open(QFile::WriteOnly | QFile::Text);
            QTextStream in(&file);
            in << QJsonDocument::fromJson(data).toJson();
            file.close();
        }
    };
}

#endif // BROWSESUBSCRIPTIONS_H
