#ifndef MATERIALTOOL_H
#define MATERIALTOOL_H

#include "renderable.h"
#include "assetsStorage.h"
#include "customsliderwidget.h"
#include "material.h"

#include <QGroupBox>
#include <QComboBox>
#include <QGridLayout>
#include <QColorDialog>


class MaterialTools : public QWidget, public Materialable
{
    Q_OBJECT
public:
                                    MaterialTools(QWidget *parent = 0);

public slots:

    virtual const ShaderStrategy*   getShaderStrategy() const;
    virtual std::shared_ptr<const Texture>getColorMap() const;

    virtual GLuint                  getCubeMapId() const;

    virtual QColor                  getColor() const;
    virtual glm::vec3               getKd() const;
    virtual glm::vec3               getKa() const;
    virtual glm::vec3               getKs() const;
    virtual GLfloat                 getTr() const;
    virtual GLfloat                 getNs() const;
    virtual GLfloat                 getRefractionRatio() const;
    virtual GLfloat                 getReflexionPercentage() const;

    virtual void                    setShaderStrategy(const ShaderStrategy* shaderStrategy);

    virtual void                    setMtl(glm::vec3 Kd, glm::vec3 Ks, glm::vec3 Ka, float Ns, float Tr);

    virtual void                    setColorMap(std::shared_ptr<const Texture> texture);

    virtual void                    CreateCubeMap();

    virtual void                    setCubeMapId(GLuint id);

    virtual void                    setColor(QColor color);
    virtual void                    setKd(float Kd);
    virtual void                    setKa(float Ka);
    virtual void                    setKs(float Ks);
    virtual void                    setNs(float Ns);
    virtual void                    setRefractionRatio(float ratio);
    virtual void                    setReflexionPercentage(float percentage);


    void                            setCurrentMaterial(std::shared_ptr<Materialable> material);
    void                            changeColor(QColor);

private:
    std::shared_ptr<Materialable>   _material;

    std::shared_ptr<AssetsStorage>  _assetsStorage;

    QGroupBox                       _shaderGroup;
    QComboBox                       _shaderList;

    QGroupBox                       _textureGroup;
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
