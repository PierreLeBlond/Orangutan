#include "app/qt/materialtool.h"

MaterialTools::MaterialTools(QWidget *parent) :
    QWidget(parent), _toolLayout(this),
    _meshGroup("Meshs", 0), _meshLayout(0), _meshList(0),
    _shaderGroup("Shaders", 0), _shaderLayout(0), _shaderList(0),
    _textureGroup("Textures", 0), _textureLayout(0), _textureList(0),
    _intensityGroup("Intensity coeficient", 0), _intensityLayout(0),
    _colorButton("Set color", this), _colorPicker(0), _KdSlider(0), _KaSlider(0), _KsSlider(0), _NsSlider(0),
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

void MaterialTools::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage){
    _assetsStorage = assetsStorage;
}

void MaterialTools::updateShaderList(){
    _shaderList.clear();
    for(int i = 0;i < _assetsStorage->getNumberOfShaderStrategies();i++){
        _shaderList.addItem(QString::fromStdString(_assetsStorage->getShaderStrategies()[i]->getName()));
    }
}

void MaterialTools::updateMeshList(){
    _meshList.clear();
    for(int i = 0;i < _assetsStorage->getNumberOfMeshs();i++){
        _meshList.addItem(QString::fromStdString(_assetsStorage->getMeshs()[i]->getName()));
    }
}

void MaterialTools::updateTextureList(){
    _textureList.clear();
    for(int i = 0;i < _assetsStorage->getNumberOfTextures();i++){
        _textureList.addItem(QString::fromStdString(_assetsStorage->getTextures()[i]->getName()));
    }
}

void MaterialTools::shaderHasChanged(int index){
    _renderable->setShaderStrategy(_assetsStorage->getShaderStrategy(index));
    _renderable->fillInVBO();
    _renderable->createVertexArrayObject();
}

void MaterialTools::meshHasChanged(int index){
    _renderable->setMesh(_assetsStorage->getMesh(index));
    _renderable->fillInVBO();
    _renderable->createVertexArrayObject();
}

void MaterialTools::textureHasChanged(int index){
    _renderable->setColorMapId(_assetsStorage->getTexture(index)->getId());
}

void MaterialTools::setCurrentMaterial(std::shared_ptr<Materialable> material)
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

void MaterialTools::setCurrentRenderable(std::shared_ptr<RenderableObject> renderable){
    _renderable = renderable;
    setCurrentMaterial(_renderable);
}

void MaterialTools::changeColor(QColor color){
    QPalette p;
    p.setColor(QPalette::Button, color);
    _colorButton.setPalette(p);
    _colorButton.setAutoFillBackground(true);
    _colorButton.setFlat(true);
}

std::shared_ptr<const ShaderStrategy> MaterialTools::getShaderStrategy() const{
    return _material->getShaderStrategy();
}

GLuint MaterialTools::getColorMapId() const{
    return _material->getColorMapId();
}

GLuint MaterialTools::getCubeMapId() const{
    return _material->getCubeMapId();
}

GLuint MaterialTools::getRenderMapId() const{
    return _material->getRenderMapId();
}

QColor MaterialTools::getColor() const{
    return _material->getColor();
}

glm::vec3 MaterialTools::getKd() const{
    return _material->getKd();
}

glm::vec3 MaterialTools::getKa() const{
    return _material->getKa();
}

glm::vec3 MaterialTools::getKs() const{
    return _material->getKs();
}

GLfloat MaterialTools::getTr() const{
    return _material->getTr();
}

GLfloat MaterialTools::getNs() const{
    return _material->getNs();
}

GLfloat MaterialTools::getRefractionRatio() const{
    return _material->getRefractionRatio();
}

GLfloat MaterialTools::getReflexionPercentage() const{
    return _material->getReflexionPercentage();
}

GLfloat MaterialTools::getEdgeFilterThreshold() const{
    return _material->getEdgeFilterThreshold();
}

void MaterialTools::setShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy){
    _material->setShaderStrategy(shaderStrategy);
}

void MaterialTools::setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr) {
    _material->setMtl(Kd, Ks, Ka, Ns, Tr);
}

void MaterialTools::setColorMapId(GLuint id){
    _material->setColorMapId(id);
}

void MaterialTools::setCubeMapId(GLuint id){
    _material->setCubeMapId(id);
}

void MaterialTools::setRenderMapId(GLuint id){
    _material->setRenderMapId(id);
}

void MaterialTools::setColor(QColor color){
    _material->setColor(color);
}

void MaterialTools::setKd(float Kd){
    _material->setKd(Kd);
}

void MaterialTools::setKa(float Ka){
    _material->setKa(Ka);
}

void MaterialTools::setKs(float Ks){
    _material->setKs(Ks);
}

void MaterialTools::setNs(float Ns){
    _material->setNs(Ns);
}

void MaterialTools::setRefractionRatio(float ratio){
    _material->setRefractionRatio(ratio);
}

void MaterialTools::setReflexionPercentage(float percentage){
    _material->setReflexionPercentage(percentage);
}

void MaterialTools::setEdgeFilterThreshold(float threshold){
    _material->setEdgeFilterThreshold(threshold);
}
