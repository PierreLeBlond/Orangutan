#ifndef MATERIALTOOL_H
#define MATERIALTOOL_H

#include "renderable.h"
#include "assetsstorage.h"
#include "customsliderwidget.h"
#include "material.h"

#include <QGroupBox>
#include <QComboBox>
#include <QGridLayout>
#include <QColorDialog>


class ObjectTools : public QWidget, public Materialable
{
    Q_OBJECT
public:
                                    ObjectTools(QWidget *parent = 0);

    void                            updateShaderList();
    void                            updateMeshList();
    void                            updateTextureList();

    void                            setAssetsStorage(std::shared_ptr<AssetsStorage> assetsStorage);

public slots:

    virtual const ShaderStrategy*   getShaderStrategy() const;
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

    virtual void                    setShaderStrategy(const ShaderStrategy* shaderStrategy);

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
    void                            setCurrentRenderable(std::shared_ptr<Renderer> renderable);
    void                            changeColor(QColor);

    void                            shaderHasChanged(int index);
    void                            meshHasChanged(int index);
    void                            textureHasChanged(int index);

private:
    std::shared_ptr<Materialable>   _material;

    std::shared_ptr<Renderer>     _renderable;

    std::shared_ptr<AssetsStorage>  _assetsStorage;

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

    QGridLayout                     _toolLayout;
};

#endif // MATERIALTOOL_H
