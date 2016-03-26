#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), _titleBar(this), _statusBar(this), _layout(0), _centralWidget(0),
    _objectDockWidget("object", 0), _materialTool(0),
    _worldDockWidget("world", 0), _worldTool(0)
{
    std::cout << QDir::current().absolutePath().toStdString() << std::endl;
    QDir::setCurrent("../Orangutan");

    //setCentralWidget(&_centralWidget);
    setGeometry(0, 0, 800, 400);

    //_centralWidget.setLayout(&_layout);

    setMenuBar(&_titleBar);
    setStatusBar(&_statusBar);

    /*Definition d'un context global de rendu, qui sera appliqué par defaut
     * pour chaque invocation d'un context spécifique */
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    _renderingWindow = new RenderingWindow(this, 400, 400);
    _renderingWindow->setGeometry(0, 0, 400, 400);

    //_layout.addWidget(_renderingWindow, 0, 0, 1, 1);
    _renderingWindow->setFocusPolicy(Qt::ClickFocus);

    setCentralWidget(_renderingWindow);


    //Le context OpenGL necessite l'affichage du widget pour être créé,
    //un appel à InitializeGl est fait automatiquement, ainsi qu'à ResizeGL et PaintGL
    show();

    _objectDockWidget.setWidget(&_materialTool);
    _objectDockWidget.setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, &_objectDockWidget);

    _worldDockWidget.setWidget(&_worldTool);
    _worldDockWidget.setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, &_worldDockWidget);

    _assetsStorage = std::make_shared<AssetsStorage>();
    _assetsFactory = std::make_shared<AssetsFactory>(_assetsStorage);

    _assetsFactory->importShader("shader/phong.vert", "shader/phong.frag");
    _assetsFactory->createNewShaderStrategy(GOURAUD, 0, "phong");
    _assetsFactory->importShader("shader/skybox.vert", "shader/skybox.frag");
    _assetsFactory->createNewShaderStrategy(SKYBOX, 1, "skybox");
    _assetsFactory->importShader("shader/environmentmap.vert", "shader/environmentmap.frag");
    _assetsFactory->createNewShaderStrategy(ENVIRONMENTMAP, 2, "environmentmap");
    _assetsFactory->importShader("shader/shader.vert", "shader/shader.frag");
    _assetsFactory->createNewShaderStrategy(GOURAUD, 3, "gouraud");
    _assetsFactory->importShader("shader/toon.vert", "shader/toon.frag");
    _assetsFactory->createNewShaderStrategy(TOON, 4, "toon");
    _assetsFactory->importShader("edgefilter.vert", "edgefilter.frag");
    _assetsFactory->createNewScreenSpaceShaderStrategy(EDGEFILTER, 5, "edgeFilter");
    _assetsFactory->importShader("edgefilter.vert", "verticalgaussianblurfilter.frag");
    _assetsFactory->createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER, 6, "verticalGaussianBlur");
    _assetsFactory->importShader("edgefilter.vert", "horizontalgaussianblurfilter.frag");
    _assetsFactory->createNewScreenSpaceShaderStrategy(GAUSSIANBLURFILTER, 7, "horizontalGaussianBlur");

    _assetsFactory->importTexture("images/dice.jpg", "dice");
    _assetsFactory->importTexture("images/Minion.png", "minion");
    _assetsFactory->importCubeMapTexture("images/space_", "space");
    _assetsFactory->importCubeMapTexture("images/sky_", "sky");

    _assetsFactory->importMeshs("Meshs/minion.obj");

    _materialTool.setAssetsStorage(_assetsStorage);
    _materialTool.updateShaderList();
    _materialTool.updateMeshList();
    _materialTool.updateTextureList();

    _worldTool.setAssetsStorage(_assetsStorage);
    _worldTool.updateSkyboxList();

    _scene = std::make_shared<Scene>(_assetsStorage);
    _scene->setIsReady(true);

    _renderingWindow->setScene(_scene);
    _renderingWindow->setAssetsStorage(_assetsStorage);
    _renderingWindow->init();
    _renderingWindow->start();

    _materialTool.setCurrentRenderable(_scene->getCurrentRenderable());
    _worldTool.setScene(_scene);
    _worldTool.setRenderingWindow(_renderingWindow);


}

MainWindow::~MainWindow()
{
    //Let the smart pointer delete all assets before the OpenGL context is destroyed
    _scene = NULL;
    _assetsFactory = NULL;
    _assetsStorage = NULL;


    delete _renderingWindow;
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

void MainWindow::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    centerOnScreen();
}

void MainWindow::centerOnScreen(){
    QDesktopWidget screen;

    QRect screenGeom = screen.screenGeometry(this);

      int screenCenterX = screenGeom.center().x();
      int screenCenterY = screenGeom.center().y();

      move(screenCenterX - width () / 2,
           screenCenterY - height() / 2);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

  QBrush background(QColor(23, 23, 34));

  painter.setBrush(background);
  painter.setPen  (Qt::NoPen ); // No stroke

  painter.drawRect(0, 0, width(), height());
}


