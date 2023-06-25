#ifndef INNERTUBEEXCEPTION_H
#define INNERTUBEEXCEPTION_H
#include <QException>

class InnertubeException : public QException
{
public:
    enum class Severity { Normal, Minor };
    explicit InnertubeException(const QString& message, Severity severity = Severity::Normal) : _message(message), _severity(severity) {}
    QString message() const { return _message; }
    Severity severity() const { return _severity; }
private:
    QString _message;
    Severity _severity;
};

#endif // INNERTUBEEXCEPTION_H
