#ifndef CUSTOMSLIDERWIDGET_H
#define CUSTOMSLIDERWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>

class CustomSliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomSliderWidget(QWidget *parent = 0);
    ~CustomSliderWidget();

    void setDefaultValue(int value);
    void setMinimum(int value);
    void setMaximum(int value);
    void setLabel(QString label);
    void setRatio(int ratio);

    int value();


signals:
    void valueChanged(float);

public slots:
    void resetValue();
    void setValue(float value);
    void changeValue(int value);

private:
    QGridLayout *_layout;
    QLabel* _label;
    QSlider* _slider;
    QLabel* _valueLabel;
    QPushButton* _defaultButton;
    int _defaultValue;
    int _ratio;
};

#endif // CUSTOMSLIDERWIDGET_H
