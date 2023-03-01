#ifndef QTHTTPLIB_H
#define QTHTTPLIB_H
#include "httplib.h"
#include <QFutureWatcher>
#include <QtConcurrent>

namespace qthttplib
{
    class Response
    {
    public:
        QByteArray body;
        httplib::Headers headers;
        QString location; // Redirect location
        QString reason;
        int status = -1;
        QString version;

        explicit Response(const httplib::Response& response)
            : body(QByteArray::fromStdString(response.body)),
              headers(response.headers),
              location(QString::fromStdString(response.location)),
              reason(QString::fromStdString(response.reason)),
              status(response.status),
              version(QString::fromStdString(response.version)),
              m_innerResponse(response) {}

        httplib::Response innerResponse() const { return m_innerResponse; }
    private:
        httplib::Response m_innerResponse;
    };

    class Client : public QObject, public httplib::Client
    {
        Q_OBJECT
    public:
        explicit Client(const QString& host) : httplib::Client(host.toStdString()) {}

        void get(const QString& path)
        {
            makeRequest(qOverload<const std::string&>(&httplib::Client::Get), this, path.toStdString());
        }

        void post(const QString& path, const QString& body, const QString& contentType)
        {
            makeRequest(
                qOverload<const std::string&, const std::string&, const std::string&>(&httplib::Client::Post),
                this, path.toStdString(), body.toStdString(), contentType.toStdString()
            );
        }

        qthttplib::Response getBlocking(const QString& path)
        {
            httplib::Result result = Get(path.toStdString());
            return qthttplib::Response(result.value());
        }

        qthttplib::Response postBlocking(const QString& path, const QString& body, const QString& contentType)
        {
            httplib::Result result = Post(path.toStdString(), body.toStdString(), contentType.toStdString());
            return qthttplib::Response(result.value());
        }
    private:
        template<class F, class... Args>
        void makeRequest(F&& f, Args&&... args)
        {
            QFutureWatcher<qthttplib::Response>* watcher = new QFutureWatcher<qthttplib::Response>;
            watcher->setFuture(QtConcurrent::run([=]() mutable -> qthttplib::Response {
                httplib::Result result = std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
                return qthttplib::Response(result.value());
            }));

            connect(watcher, &QFutureWatcher<qthttplib::Response>::finished, this, [this, watcher] {
                emit requestFinished(watcher->result());
            });
        }
    signals:
        void requestFinished(const qthttplib::Response& response);
    };
}

#endif // QTHTTPLIB_H
