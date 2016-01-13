#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <memory>
#include <QKeyEvent>

#include "assetsfactory.h"
#include "assetsstorage.h"
#include "scene.h"
#include "renderingwindow.h"
#include "util.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *keyEvent);

private:
    Ui::MainWindow *ui;

    std::shared_ptr<AssetsFactory>          _assetsFactory;
    std::shared_ptr<AssetsStorage>          _assetsStorage;
    std::shared_ptr<Scene>                  _scene;

    RenderingWindow*    _renderingWindow;

};

#endif // MAINWINDOW_H
