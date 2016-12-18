#ifndef MATERIALTOOL_H
#define MATERIALTOOL_H

#include <memory>

#include "app/qt/customsliderwidget.h"

#include "object/renderableobject.h"
#include "object/material.h"

#include "shader/shaderstrategy.h"

#include "scene/assetsstorage.h"

#include <QGroupBox>
#include <QComboBox>
#include <QGridLayout>
#include <QColorDialog>


class MaterialTools : public QWidget, public Materialable
{
    Q_OBJECT
public:
                                    MaterialTools(QWidget *parent = 0);

    void                            updateShaderList();
    void                            updateMeshList();
    void                            updateTextureList();

    void                            setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

public slots:

    virtual std::shared_ptr<const ShaderStrategy>   getShaderStrategy() const;
    virtual GLuint                  getColorMapId() const;
    virtual GLuint                  getCubeMapId() const;
    virtual GLuint                  getRenderMapId() const;

    virtual QColor                  getColor() const;
    virtual glm::vec3               getKd() const;
    virtual glm::vec3               getKa() const;
    virtual glm::vec3               getKs() const;
    virtual GLfloat                 getTr() const;
    virtual GLfloat                 getNs() const;
    virtual GLfloat                 getRefractionRatio() const;
    virtual GLfloat                 getReflexionPercentage() const;
    virtual GLfloat                 getEdgeFilterThreshold() const;

    virtual void                    setShaderStrategy(std::shared_ptr<const ShaderStrategy> shaderStrategy);

    virtual void                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr);

    virtual void                    setColorMapId(GLuint id);
    virtual void                    setCubeMapId(GLuint id);
    virtual void                    setRenderMapId(GLuint id);

    virtual void                    setColor(QColor color);
    virtual void                    setKd(float Kd);
    virtual void                    setKa(float Ka);
    virtual void                    setKs(float Ks);
    virtual void                    setNs(float Ns);
    virtual void                    setRefractionRatio(float ratio);
    virtual void                    setReflexionPercentage(float percentage);
    virtual void                    setEdgeFilterThreshold(float threshold);


    void                            setCurrentMaterial(std::shared_ptr<Materialable> material);
    void                            setCurrentRenderable(std::shared_ptr<RenderableObject> renderable);
    void                            changeColor(QColor);

    void                            shaderHasChanged(int index);
    void                            meshHasChanged(int index);
    void                            textureHasChanged(int index);

private:
    std::shared_ptr<Materialable>   _material;

    std::shared_ptr<RenderableObject> _renderable;

    std::shared_ptr<AssetsStorage>  _assetsStorage;

    QGridLayout                     _toolLayout;

    QGroupBox                       _meshGroup;
    QGridLayout                     _meshLayout;
    QComboBox                       _meshList;

    QGroupBox                       _shaderGroup;
    QGridLayout                     _shaderLayout;
    QComboBox                       _shaderList;

    QGroupBox                       _textureGroup;
    QGridLayout                     _textureLayout;
    QComboBox                       _textureList;

    QGroupBox                       _intensityGroup;
    QGridLayout                     _intensityLayout;
    QPushButton                     _colorButton;
    QColorDialog                    _colorPicker;
    CustomSliderWidget              _KdSlider;
    CustomSliderWidget              _KaSlider;
    CustomSliderWidget              _KsSlider;
    CustomSliderWidget              _NsSlider;

    QGroupBox                       _refractionGroup;
    QGridLayout                     _refractionLayout;
    CustomSliderWidget              _refractionRatioSlider;
    CustomSliderWidget              _reflexionPercentageSlider;
};

#endif // MATERIALTOOL_H
