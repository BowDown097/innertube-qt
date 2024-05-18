#pragma once
#include <QException>
#include <wobjectdefs.h>

class InnertubeException : public QException
{
public:
    enum class Severity { Normal, Minor };
    explicit InnertubeException(const QString& message, Severity severity = Severity::Normal)
        : m_message(message), m_severity(severity) {}
    QString message() const { return m_message; }
    Severity severity() const { return m_severity; }
private:
    QString m_message;
    Severity m_severity;
};

W_REGISTER_ARGTYPE(InnertubeException)
