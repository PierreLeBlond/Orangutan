#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "assetsfactory.h"
#include "assetsstorage.h"
#include "scene.h"
#include "renderingwindow.h"
#include "util.h"


#include "windowtitlebar.h"
#include "materialtool.h"
#include "worldtool.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *keyEvent);

protected:
    void showEvent(QShowEvent *event);
    void paintEvent(QPaintEvent *event);

private:

    std::shared_ptr<AssetsFactory>          _assetsFactory;
    std::shared_ptr<AssetsStorage>          _assetsStorage;
    std::shared_ptr<Scene>                  _scene;

    RenderingWindow*                        _renderingWindow;

    WindowTitleBar                          _titleBar;
    QMenuBar                                _menuBar;
    QStatusBar                              _statusBar;

    QGridLayout                             _layout;
    QWidget                                 _centralWidget;

    QDockWidget                             _objectDockWidget;
    QDockWidget                             _worldDockWidget;

    ObjectTools                             _materialTool;
    WorldTool                               _worldTool;

    void                                    centerOnScreen();


};

#endif // MAINWINDOW_H
