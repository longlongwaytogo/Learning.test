#ifndef SWEBENGINEVIEW_H
#define SWEBENGINEVIEW_H

#include <QWebEngineView>
#include <QList>

class SWebEngineView : public QWebEngineView
{
    Q_OBJECT
public:
    SWebEngineView(QWidget *parent = NULL);

    void addUrl(QUrl& ulr);
    QList<QUrl>& getUrlList() { return m_urlList;}
protected:
    /*
     * @brief createWindow
     * @param type
     * @return
     */
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);

private:
    QList<QUrl> m_urlList;

};

#endif // SWEBENGINEVIEW_H
