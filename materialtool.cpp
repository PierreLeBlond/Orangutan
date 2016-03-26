#include "materialtool.h"

ObjectTools::ObjectTools(QWidget *parent) :
    QWidget(parent), _toolLayout(this),
    _shaderGroup("Shaders", 0), _shaderLayout(0), _shaderList(0),
    _meshGroup("Meshs", 0), _meshLayout(0), _meshList(0),
    _textureGroup("Textures", 0), _textureLayout(0), _textureList(0),
    _intensityGroup("Intensity coeficient", 0), _intensityLayout(0),
    _colorPicker(0), _colorButton("Set color", this), _KdSlider(0), _KaSlider(0), _KsSlider(0), _NsSlider(0),
    _refractionGroup("Refraction & reflexion", 0), _refractionLayout(0), _refractionRatioSlider(0), _reflexionPercentageSlider(0)
{   

    _shaderGroup.setLayout(&_shaderLayout);

    _shaderLayout.addWidget(&_shaderList, 0, 0, 1, 1);

    connect(&_shaderList, SIGNAL(activated(int)), this, SLOT(shaderHasChanged(int)));

    _toolLayout.addWidget(&_shaderGroup, 0, 0, 1, 1);

    _meshGroup.setLayout(&_meshLayout);

    _meshLayout.addWidget(&_meshList, 0, 0, 1, 1);

    connect(&_meshList, SIGNAL(activated(int)), this, SLOT(meshHasChanged(int)));

    _toolLayout.addWidget(&_meshGroup, 1, 0, 1, 1);

    _textureGroup.setLayout(&_textureLayout);

    _textureLayout.addWidget(&_textureList, 0, 0, 1, 1);

    connect(&_textureList, SIGNAL(activated(int)), this, SLOT(textureHasChanged(int)));

    _toolLayout.addWidget(&_textureGroup, 2, 0, 1, 1);

    _intensityGroup.setLayout(&_intensityLayout);

    _colorPicker.setCurrentColor(QColor::fromRgb(255, 255, 255));

    connect(&_colorButton, SIGNAL(clicked()), &_colorPicker, SLOT(open()));
    connect(&_colorPicker, SIGNAL(colorSelected(QColor)), this, SLOT(changeColor(QColor)));

    _KdSlider.setMinimum(0);
    _KdSlider.setMaximum(100);
    _KdSlider.setRatio(100);
    _KdSlider.setValue(0.5f);
    _KdSlider.setLabel("Diffuse coeficient :");

    _KaSlider.setMinimum(0);
    _KaSlider.setMaximum(100);
    _KaSlider.setRatio(100);
    _KaSlider.setValue(0.5f);
    _KaSlider.setLabel("Ambient coeficient :");

    _KsSlider.setMinimum(0);
    _KsSlider.setMaximum(100);
    _KsSlider.setRatio(100);
    _KsSlider.setValue(0.5f);
    _KsSlider.setLabel("Specular coeficient :");

    _NsSlider.setMinimum(0);
    _NsSlider.setMaximum(200);
    _NsSlider.setValue(0.5f);
    _NsSlider.setLabel("Shininess coeficient :");

    _intensityLayout.addWidget(&_colorButton, 0, 0, 1, 1);
    _intensityLayout.addWidget(&_KaSlider, 1, 0, 1, 1);
    _intensityLayout.addWidget(&_KdSlider, 2, 0, 1, 1);
    _intensityLayout.addWidget(&_KsSlider, 3, 0, 1, 1);
    _intensityLayout.addWidget(&_NsSlider, 4, 0, 1, 1);

    _intensityLayout.setVerticalSpacing(0);
    _intensityLayout.setHorizontalSpacing(0);
    _intensityLayout.setContentsMargins(0, 5, 0, 0);

    _toolLayout.addWidget(&_intensityGroup, 3, 0, 1, 1);

    _refractionGroup.setLayout(&_refractionLayout);

    _refractionRatioSlider.setMinimum(0);
    _refractionRatioSlider.setMaximum(100);
    _refractionRatioSlider.setDefaultValue(0);
    _refractionRatioSlider.setValue(0);
    _refractionRatioSlider.setLabel("indice de refraction");

    _reflexionPercentageSlider.setMinimum(0);
    _reflexionPercentageSlider.setMaximum(100);
    _reflexionPercentageSlider.setDefaultValue(100);
    _reflexionPercentageSlider.setValue(100);
    _reflexionPercentageSlider.setLabel("indice de reflexion");

    _refractionLayout.addWidget(&_refractionRatioSlider, 0, 0, 1, 1);
    _refractionLayout.addWidget(&_reflexionPercentageSlider, 1, 0, 1, 1);

    _refractionLayout.setVerticalSpacing(0);
    _refractionLayout.setHorizontalSpacing(0);
    _refractionLayout.setContentsMargins(0, 5, 0, 0);

    _toolLayout.addWidget(&_refractionGroup, 4, 0, 1, 1);
    _toolLayout.setSizeConstraint(QLayout::SetFixedSize);
    _toolLayout.setVerticalSpacing(0);
}

void ObjectTools::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage){
    _assetsStorage = assetsStorage;
}

void ObjectTools::updateShaderList(){
    _shaderList.clear();
    for(int i = 0;i < _assetsStorage->getNumberOfShaderStrategies();i++){
        _shaderList.addItem(QString::fromStdString(_assetsStorage->getShaderStrategies()[i]->getName()));
    }
}

void ObjectTools::updateMeshList(){
    _meshList.clear();
    for(int i = 0;i < _assetsStorage->getNumberOfMeshs();i++){
        _meshList.addItem(QString::fromStdString(_assetsStorage->getMeshs()[i]->getName()));
    }
}

void ObjectTools::updateTextureList(){
    _textureList.clear();
    for(int i = 0;i < _assetsStorage->getNumberOfTextures();i++){
        _textureList.addItem(QString::fromStdString(_assetsStorage->getTextures()[i]->getName()));
    }
}

void ObjectTools::shaderHasChanged(int index){
    _renderable->setShaderStrategy(_assetsStorage->getShaderStrategy(index));
    _renderable->fillInVBO();
    _renderable->createVertexArrayObject();
}

void ObjectTools::meshHasChanged(int index){
    _renderable->setMesh(_assetsStorage->getMesh(index));
    _renderable->fillInVBO();
    _renderable->createVertexArrayObject();
}

void ObjectTools::textureHasChanged(int index){
    _renderable->setColorMapId(_assetsStorage->getTexture(index)->getId());
}

void ObjectTools::setCurrentMaterial(std::shared_ptr<Materialable> material)
{
    if(_material != 0)
    {
    disconnect(&_colorPicker, SIGNAL(currentColorChanged(QColor)), this, SLOT(setColor(QColor)));
    disconnect(&_KaSlider, SIGNAL(valueChanged(float)), this, SLOT(setKa(float)));
    disconnect(&_KdSlider, SIGNAL(valueChanged(float)), this, SLOT(setKd(float)));
    disconnect(&_KsSlider, SIGNAL(valueChanged(float)), this, SLOT(setKs(float)));
    disconnect(&_NsSlider, SIGNAL(valueChanged(float)), this, SLOT(setNs(float)));

    disconnect(&_refractionRatioSlider, SIGNAL(valueChanged(float)), this, SLOT(setRefractionRatio(float)));
    disconnect(&_reflexionPercentageSlider, SIGNAL(valueChanged(float)), this, SLOT(setReflexionPercentage(float)));
    }

    _material = material;

    _colorPicker.setCurrentColor(_material->getColor());
    changeColor(_material->getColor());
    _KaSlider.setValue(_material->getKa().x);
    _KdSlider.setValue(_material->getKd().x);
    _KsSlider.setValue(_material->getKa().x);
    _NsSlider.setValue(_material->getNs());

    _refractionRatioSlider.setValue(_material->getRefractionRatio());
    _reflexionPercentageSlider.setValue(_material->getReflexionPercentage());

    connect(&_colorPicker, SIGNAL(currentColorChanged(QColor)), this, SLOT(setColor(QColor)));
    connect(&_KaSlider, SIGNAL(valueChanged(float)), this, SLOT(setKa(float)));
    connect(&_KdSlider, SIGNAL(valueChanged(float)), this, SLOT(setKd(float)));
    connect(&_KsSlider, SIGNAL(valueChanged(float)), this, SLOT(setKs(float)));
    connect(&_NsSlider, SIGNAL(valueChanged(float)), this, SLOT(setNs(float)));

    connect(&_refractionRatioSlider, SIGNAL(valueChanged(float)), this, SLOT(setRefractionRatio(float)));
    connect(&_reflexionPercentageSlider, SIGNAL(valueChanged(float)), this, SLOT(setReflexionPercentage(float)));
}

void ObjectTools::setCurrentRenderable(std::shared_ptr<Renderer> renderable){
    _renderable = renderable;
    setCurrentMaterial(_renderable);
}

void ObjectTools::changeColor(QColor color){
    QPalette p;
    p.setColor(QPalette::Button, color);
    _colorButton.setPalette(p);
    _colorButton.setAutoFillBackground(true);
    _colorButton.setFlat(true);
}

const ShaderStrategy *ObjectTools::getShaderStrategy() const{
    return _material->getShaderStrategy();
}

GLuint ObjectTools::getColorMapId() const{
    return _material->getColorMapId();
}

GLuint ObjectTools::getCubeMapId() const{
    return _material->getCubeMapId();
}

GLuint ObjectTools::getRenderMapId() const{
    return _material->getRenderMapId();
}

QColor ObjectTools::getColor() const{
    return _material->getColor();
}

glm::vec3 ObjectTools::getKd() const{
    return _material->getKd();
}

glm::vec3 ObjectTools::getKa() const{
    return _material->getKa();
}

glm::vec3 ObjectTools::getKs() const{
    return _material->getKs();
}

GLfloat ObjectTools::getTr() const{
    return _material->getTr();
}

GLfloat ObjectTools::getNs() const{
    return _material->getNs();
}

GLfloat ObjectTools::getRefractionRatio() const{
    return _material->getRefractionRatio();
}

GLfloat ObjectTools::getReflexionPercentage() const{
    return _material->getReflexionPercentage();
}

GLfloat ObjectTools::getEdgeFilterThreshold() const{
    return _material->getEdgeFilterThreshold();
}

void ObjectTools::setShaderStrategy(const ShaderStrategy *shaderStrategy){
    _material->setShaderStrategy(shaderStrategy);
}

void ObjectTools::setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) {
    _material->setMtl(Kd, Ks, Ka, Ns, Tr);
}

void ObjectTools::setColorMapId(GLuint id){
    _material->setColorMapId(id);
}

void ObjectTools::setCubeMapId(GLuint id){
    _material->setCubeMapId(id);
}

void ObjectTools::setRenderMapId(GLuint id){
    _material->setRenderMapId(id);
}

void ObjectTools::setColor(QColor color){
    _material->setColor(color);
}

void ObjectTools::setKd(float Kd){
    _material->setKd(Kd);
}

void ObjectTools::setKa(float Ka){
    _material->setKa(Ka);
}

void ObjectTools::setKs(float Ks){
    _material->setKs(Ks);
}

void ObjectTools::setNs(float Ns){
    _material->setNs(Ns);
}

void ObjectTools::setRefractionRatio(float ratio){
    _material->setRefractionRatio(ratio);
}

void ObjectTools::setReflexionPercentage(float percentage){
    _material->setReflexionPercentage(percentage);
}

void ObjectTools::setEdgeFilterThreshold(float threshold){
    _material->setEdgeFilterThreshold(threshold);
}

