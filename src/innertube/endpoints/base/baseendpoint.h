#ifndef BASEENDPOINT_H
#define BASEENDPOINT_H
#include "CurlEasy.h"
#include "innertube/itc-objects/innertubeauthstore.h"

class InnerTube;
namespace InnertubeEndpoints
{
    class BaseEndpoint
    {
    protected:
        void get(const QString& endpoint, InnertubeContext* context, InnertubeAuthStore* authStore, CurlEasy* easy,
                 const QJsonObject& body, QByteArray& data);
    private:
        void getData(CurlEasy* easy, const QJsonObject& body, QByteArray& data);
        QString keyFor(const QString& client) const;
        void setNeededHeaders(CurlEasy* easy, InnertubeContext* context, InnertubeAuthStore* authStore);

        // courtesy of https://github.com/zerodytrash/YouTube-Internal-Clients
        static inline QHash<QString, QString> CLIENT_KEYS = {
            { "WEB", "AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8" },
            { "WEB_KIDS", "AIzaSyBbZV_fZ3an51sF-mvs5w37OqqbsTOzwtU" },
            { "WEB_MUSIC", "AIzaSyC9XL3ZjWddXya6X74dJoCTL-WEYFDNX30" },
            { "WEB_CREATOR", "AIzaSyBUPetSUmoZL-OhlxA7wSac5XinrygCqMo" },
            { "ANDROID", "AIzaSyA8eiZmM1FaDVjRy-df2KTyQ_vz_yYM39w" },
            { "ANDROID_MUSIC", "AIzaSyAOghZGza2MQSZkY_zfZ370N-PUdXEo8AI" },
            { "ANDROID_EMBEDDED_PLAYER", "AIzaSyCjc_pVEDi4qsv5MtC2dMXzpIaDoRFLsxw" },
            { "ANDROID_CREATOR", "AIzaSyD_qjV8zaaUMehtLkrKFgVeSX_Iqbtyws8" },
            { "IOS", "AIzaSyB-63vPrdThhKuerbB2N_l7Kwwcxj6yUAc" },
            { "IOS_MUSIC", "AIzaSyBAETezhkwP0ZWA02RsqT1zu78Fpt0bC_s" }
        };
    };
}

#endif // BASEENDPOINT_H
