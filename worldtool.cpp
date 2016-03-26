#include "worldtool.h"

WorldTool::WorldTool(QWidget *parent) :
    QWidget(parent), _toolLayout(this),
    _edgeFilterGroup("Edge Filter", 0), _edgeFilterLayout(0), _edgeFilterButton(0), _edgeFilterThresholdSlider(0),
    _verticalGaussBlurFilterGroup("Vertical Gauss Blur Filter", 0), _verticalGaussBlurFilterFilterLayout(0), _verticalGaussBlurFilterFilterButton(0),
    _horizontalGaussBlurFilterGroup("Horizontal Gauss Blur Filter", 0), _horizontalGaussBlurFilterFilterLayout(0), _horizontalGaussBlurFilterFilterButton(0),
    _skyboxGroup("Skybox", 0), _skyboxLayout(0), _skyboxList(0),
    _signalMapper(this)
{
    _edgeFilterGroup.setLayout(&_edgeFilterLayout);

    _edgeFilterThresholdSlider.setMinimum(0);
    _edgeFilterThresholdSlider.setMaximum(100);
    _edgeFilterThresholdSlider.setRatio(100);
    _edgeFilterThresholdSlider.setValue(0.5f);
    _edgeFilterThresholdSlider.setLabel("edge filter threshold");

    _edgeFilterLayout.addWidget(&_edgeFilterButton, 0, 0, 1, 1);
    _edgeFilterLayout.addWidget(&_edgeFilterThresholdSlider, 1, 0, 1, 1);

    connect(&_edgeFilterButton, SIGNAL(clicked()), &_signalMapper, SLOT(map()));
    _signalMapper.setMapping(&_edgeFilterButton, 0);
    connect(&_edgeFilterThresholdSlider, SIGNAL(valueChanged(float)), this, SLOT(edgeFilterThresholdHasChanged(float)));

    _toolLayout.addWidget(&_edgeFilterGroup, 0, 0, 1, 1);


    _verticalGaussBlurFilterGroup.setLayout(&_verticalGaussBlurFilterFilterLayout);

    _verticalGaussBlurFilterFilterLayout.addWidget(&_verticalGaussBlurFilterFilterButton, 0, 0, 1, 1);

    connect(&_verticalGaussBlurFilterFilterButton, SIGNAL(clicked()), &_signalMapper, SLOT(map()));
    _signalMapper.setMapping(&_verticalGaussBlurFilterFilterButton, 1);

    _toolLayout.addWidget(&_verticalGaussBlurFilterGroup, 1, 0, 1, 1);


    _horizontalGaussBlurFilterGroup.setLayout(&_horizontalGaussBlurFilterFilterLayout);

    _horizontalGaussBlurFilterFilterLayout.addWidget(&_horizontalGaussBlurFilterFilterButton, 0, 0, 1, 1);

    connect(&_horizontalGaussBlurFilterFilterButton, SIGNAL(clicked()), &_signalMapper, SLOT(map()));
    _signalMapper.setMapping(&_horizontalGaussBlurFilterFilterButton, 2);

    _toolLayout.addWidget(&_horizontalGaussBlurFilterGroup, 2, 0, 1, 1);

    connect(&_signalMapper, SIGNAL(mapped(int)), this, SLOT(enableScreenSpaceShader(int)));

    _skyboxGroup.setLayout(&_skyboxLayout);

    _skyboxLayout.addWidget(&_skyboxList, 0, 0, 1, 1);

    connect(&_skyboxList, SIGNAL(activated(int)), this, SLOT(skyboxHasChanged(int)));

    _toolLayout.addWidget(&_skyboxGroup, 3, 0, 1, 1);

    _toolLayout.setSizeConstraint(QLayout::SetFixedSize);

}

void WorldTool::setRenderingWindow(RenderingWindow* renderingWindow){
    _renderingWindow = renderingWindow;
}

void WorldTool::setScene(std::shared_ptr<Scene> scene){
    _scene = scene;
}

void WorldTool::enableScreenSpaceShader(int index){
    _renderingWindow->enableScreenSpaceShader(index);
}

void WorldTool::setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage){
    _assetsStorage = assetsStorage;
}

void WorldTool::updateSkyboxList(){
    _skyboxList.clear();
    for(int i = 0;i < _assetsStorage->getNumberOfCubeMapTextures();i++){
        _skyboxList.addItem(QString::fromStdString(_assetsStorage->getCubeMapTextures()[i]->getName()));
    }
}

void WorldTool::skyboxHasChanged(int index){
    _scene->setSkybox(_assetsStorage->getCubeMapTexture(index)->getId());
}

void WorldTool::edgeFilterThresholdHasChanged(float threshold){
    _scene->getScreenSpaceRenderable()->setEdgeFilterThreshold(threshold);
}

