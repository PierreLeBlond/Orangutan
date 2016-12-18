#ifndef WORLDTOOL_H
#define WORLDTOOL_H

#include "scene/assetsstorage.h"
#include "scene/scene.h"

#include "app/qt/canvas.h"
#include "app/qt/customsliderwidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QRadioButton>
#include <QSignalMapper>


class WorldTool : public QWidget
{
    Q_OBJECT
public:
                                    WorldTool(QWidget *parent = 0);

    void                            setRenderingWindow(RenderingWindow* renderingWindow);
    void                            setScene(std::shared_ptr<Scene> scene);

    void                            setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

    void                            updateSkyboxList();

public slots:

    void                            skyboxHasChanged(int index);
    void                            edgeFilterThresholdHasChanged(float treshold);

    void                            enableScreenSpaceShader(int index);

private:

    std::shared_ptr<Scene>          _scene;
    std::shared_ptr<AssetsStorage>  _assetsStorage;

    QGridLayout                     _toolLayout;

    RenderingWindow*                _renderingWindow;

    QGroupBox                       _edgeFilterGroup;
    QGridLayout                     _edgeFilterLayout;
    QRadioButton                    _edgeFilterButton;
    CustomSliderWidget              _edgeFilterThresholdSlider;

    QGroupBox                       _verticalGaussBlurFilterGroup;
    QGridLayout                     _verticalGaussBlurFilterFilterLayout;
    QRadioButton                    _verticalGaussBlurFilterFilterButton;

    QGroupBox                       _horizontalGaussBlurFilterGroup;
    QGridLayout                     _horizontalGaussBlurFilterFilterLayout;
    QRadioButton                    _horizontalGaussBlurFilterFilterButton;

    QGroupBox                       _skyboxGroup;
    QGridLayout                     _skyboxLayout;
    QComboBox                       _skyboxList;

    QSignalMapper                   _signalMapper;

};

#endif // WORLDTOOL_H
