#include <QMainWindow>
#include <QDir>
#include <memory>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QPainter>
#include <QSizeGrip>
#include <QStatusBar>
#include <QGridLayout>
#include <QDockWidget>

#include "app/screenable.h"
#include "app/qt/canvas.h"
#include "app/qt/windowtitlebar.h"

class Screen : public Screenable, public QMainWindow
{
public:
                                                Screen(QWidget *parent = 0);
    virtual                                     ~Screen();

    virtual void                                init();

    void                                        keyPressEvent(QKeyEvent *keyEvent);
    void                                        centerOnScreen();

protected:
    void                                        showEvent(QShowEvent *event);
    void                                        paintEvent(QPaintEvent *event);

private:

    Canvas*                                     _canvas;

    WindowTitleBar                              _titleBar;
    QMenuBar                                    _menuBar;
    QStatusBar                                  _statusBar;

    QGridLayout                                 _layout;
    QWidget                                     _centralWidget;

    //QDockWidget                               _objectDockWidget;
    //QDockWidget                               _worldDockWidget;

    //ObjectTools                               _materialTool;
    //WorldTool                                 _worldTool;
};


