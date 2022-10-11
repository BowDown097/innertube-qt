#ifndef INNERTUBEEXCEPTION_HPP
#define INNERTUBEEXCEPTION_HPP
#include <QException>

class InnertubeException : public QException
{
public:
    enum Severity { Normal, Minor };
    explicit InnertubeException(const QString& message, Severity severity = Severity::Normal) : _message(message), _severity(severity) {}
    QString message() const { return _message; }
    Severity severity() const { return _severity; }
private:
    QString _message;
    Severity _severity;
};

#endif // INNERTUBEEXCEPTION_HPP
