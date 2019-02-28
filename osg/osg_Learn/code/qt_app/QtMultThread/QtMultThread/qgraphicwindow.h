#ifndef QGRAPHICWINDOW_H
#define QGRAPHICWINDOW_H

#include <QObject>
#include <QtOpenGL/QGLWidget>
#include <QEvent>
#include <QQueue>
#include <QSet>
#include <QMutex>



#include <osgViewer/GraphicsWindow>


class QGraphicWindow : public QObject, public osgViewer::GraphicsWindow
{
public:
    QGraphicWindow( osg::GraphicsContext::Traits* traits, QWidget* parent = NULL, const QGLWidget* shareWidget = NULL, Qt::WindowFlags f = 0);

    QGraphicWindow(GLWidget* widget);

    virtual ~QGraphicWindow();

    inline GLWidget* getGLWidget() {return _widget;}
    inline const GLWidget* getGLWidget() { return _widget;}

    /// deprecated
    inline GLWidget* getGraphWidget() { return _widget; }
    /// deprecated
    inline const GLWidget* getGraphWidget() const { return _widget; }

    struct WindowData :public osg::Referenced
    {

    };

};

#endif // QGRAPHICWINDOW_H
