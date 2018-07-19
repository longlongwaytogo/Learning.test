#ifndef WEBOBJECT_H
#define WEBOBJECT_H

#include <QObject>

class WebObject : public QObject
{
    Q_OBJECT
public:
    explicit WebObject(QObject *parent = 0);

    // js property
    Q_PROPERTY(QString name MEMBER m_name NOTIFY sig_nameChanged)
    Q_PROPERTY(int age MEMBER m_age NOTIFY sig_ageChanged)


    void setName(const QString& name);
    void setAge(int age);
signals:

    void sig_nameChanged(const QString& name);
    void sig_ageChanged(int age);

public slots:
    void slot_debug(const QString& msg);

private:
    QString m_name;
    int     m_age;

};

#endif // WEBOBJECT_H
