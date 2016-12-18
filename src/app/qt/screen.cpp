#include "app/qt/screen.h"
#include "core/debug.h"

Screen::Screen(QWidget *parent) :
    QMainWindow(parent), _titleBar(this), _statusBar(this), _layout(0), _centralWidget(0)
{
    std::cout << "App started in " <<
        QDir::current().absolutePath().toStdString() << std::endl;

    //setCentralWidget(&_centralWidget);
    setGeometry(0, 0, 800, 400);

    //_centralWidget.setLayout(&_layout);

    setMenuBar(&_titleBar);
    setStatusBar(&_statusBar);

    /*Definition d'un context global de rendu, qui sera appliqué par defaut
     * pour chaque invocation d'un context spécifique */
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(4);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    _canvas = new Canvas(this, 400, 400);
    _canvas->setGeometry(0, 0, 400, 400);

    //_layout.addWidget(_renderingWindow, 0, 0, 1, 1);
    _canvas->setFocusPolicy(Qt::ClickFocus);

    setCentralWidget(_canvas);


    //Le context OpenGL necessite l'affichage du widget pour être créé,
    //un appel à InitializeGl est fait automatiquement, ainsi qu'à ResizeGL et PaintGL
    show();

    /*_materialTool.setCurrentRenderable(_scene->getCurrentRenderable());
    _worldTool.setScene(_scene);
    _worldTool.setRenderingWindow(_renderingWindow);*/
}

Screen::~Screen()
{
    delete _canvas;
}

void Screen::init()
{
    Screenable::init();

    _canvas->setScene(_scene);

    std::function<void()> drawCall = [&](){
        if(_scene->isReady())
            _scene->draw();
    };

    _canvas->setDrawCall(drawCall);

    _canvas->setAssetsStorage(_assetsStorage);
    _canvas->init();
    _canvas->start();

}

void Screen::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
    case Qt::Key_Escape:
        close();
        break;
    default:
        _canvas->keyPressEvent(keyEvent);
    break;
    }
}

void Screen::showEvent(QShowEvent *event){
    Q_UNUSED(event);

    centerOnScreen();
}

void Screen::centerOnScreen(){
    QDesktopWidget screen;

    QRect screenGeom = screen.screenGeometry(this);

    int screenCenterX = screenGeom.center().x();
    int screenCenterY = screenGeom.center().y();

    move(screenCenterX - width () / 2,
           screenCenterY - height() / 2);
}

void Screen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QBrush background(QColor(23, 23, 34));

    painter.setBrush(background);
    painter.setPen  (Qt::NoPen ); // No stroke

    painter.drawRect(0, 0, width(), height());
}
