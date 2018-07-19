#include "swebengineview.h"

SWebEngineView::SWebEngineView(QWidget *parent):QWebEngineView(parent)
{

}


void SWebEngineView::addUrl(QUrl &url)
{
    m_urlList << url;
}

QWebEngineView* SWebEngineView::createWindow(QWebEnginePage::WebWindowType type)
{

   // Q_UUSED(type);
    m_urlList << this->url();
    return this;
}
