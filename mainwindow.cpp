#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::cout << QDir::current().absolutePath().toStdString() << std::endl;
    QDir::setCurrent("..");


    /*Definition d'un context global de rendu, qui sera appliqué par defaut
     * pour chaque invocation d'un context spécifique */
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    _renderingWindow = new RenderingWindow(this, 600, 400);

    this->setCentralWidget(_renderingWindow);
    //Le context OpenGL necessite l'affichage du widget pour être créé,
    //un appel à InitializeGl est fait automatiquement, ainsi qu'à ResizeGL et PaintGL
    show();



    _assetsStorage = std::make_shared<AssetsStorage>();
    _assetsFactory = std::make_shared<AssetsFactory>(_assetsStorage);

    _assetsFactory->importShader("shader/phong.vert", "shader/phong.frag");
    _assetsFactory->createNewShaderStrategy(GOURAUD, 0, "gouraud");
    _assetsFactory->importShader("shader/skybox.vert", "shader/skybox.frag");
    _assetsFactory->createNewShaderStrategy(SKYBOX, 1, "skybox");

    _scene = std::make_shared<Scene>(_assetsStorage);
    _scene->setIsReady(true);


    _renderingWindow->setScene(_scene);
    _renderingWindow->init();
    _renderingWindow->start();

}

MainWindow::~MainWindow()
{
    //Let the smart pointer delete all assets before the OpenGL context is destroyed
    _scene = NULL;
    _assetsFactory = NULL;
    _assetsStorage = NULL;


    delete _renderingWindow;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Escape:
        close();
        break;
    default:
        _renderingWindow->keyPressEvent(keyEvent);
    break;
    }
}
