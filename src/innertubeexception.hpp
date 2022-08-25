#ifndef INNERTUBEEXCEPTION_HPP
#define INNERTUBEEXCEPTION_HPP
#include <QException>

class InnertubeException : public QException
{
    QString msg;
public:
    InnertubeException(const QString& message) : msg(message) {}
    void raise() const override { throw *this; }
    InnertubeException* clone() const override { return new InnertubeException(*this); }
    QString message() const { return msg; }
};

#endif // INNERTUBEEXCEPTION_HPP
