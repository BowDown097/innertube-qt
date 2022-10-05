#ifndef INNERTUBEEXCEPTION_HPP
#define INNERTUBEEXCEPTION_HPP
#include <QException>

class InnertubeException : public QException
{
public:
    enum Severity { Normal, Minor };
    InnertubeException(const QString& message, Severity severity = Severity::Normal) : _message(message), _severity(severity) {}
    void raise() const override { throw *this; }
    InnertubeException* clone() const override { return new InnertubeException(*this); }
    QString message() const { return _message; }
    Severity severity() const { return _severity; }
private:
    QString _message;
    Severity _severity;
};

#endif // INNERTUBEEXCEPTION_HPP
