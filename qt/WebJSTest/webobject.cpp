#include "webobject.h"
#include <QDebug>


WebObject::WebObject(QObject *parent) : QObject(parent),
    m_name("jim"),
    m_age(22)
{
}

void WebObject::setName(const QString &name)
{
    if(m_name == name) return;
    m_name = name;
    emit sig_nameChanged(m_name);
}

void WebObject::setAge(int age)
{
    if(m_age == age) return;
    m_age = age;
    emit sig_ageChanged(m_age);
}

void WebObject::slot_debug(const QString &msg)
{
    qDebug() << "Web Debug:" << msg;

}



