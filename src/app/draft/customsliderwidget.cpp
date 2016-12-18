#include "app/qt/customsliderwidget.h"

CustomSliderWidget::CustomSliderWidget(QWidget *parent) : QWidget(parent), _defaultValue(0), _ratio(1)
{
    _layout = new QGridLayout(this);

    _label = new QLabel(this);
    _valueLabel = new QLabel(this);
    _valueLabel->setText(QString::number(_defaultValue));
    _slider = new QSlider(Qt::Horizontal, this);
    _defaultButton = new QPushButton(QIcon("images/refresh.png"), "", this);

    _defaultButton->setObjectName("customSlider");
    _valueLabel->setObjectName("customSlider");

    _slider->setValue(_defaultValue);

    _layout->setHorizontalSpacing(0);
    _layout->setVerticalSpacing(0);
    _layout->setContentsMargins(0, 5, 0, 0);

    _layout->addWidget(_label, 0, 0, 1, 4);
    _layout->addWidget(_slider, 1, 0, 1, 2);
    _layout->addWidget(_valueLabel, 1, 2, 1, 1);
    _layout->addWidget(_defaultButton, 1, 3, 1, 1);

    connect(_defaultButton, SIGNAL(clicked()), this, SLOT(resetValue()));
    connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));

    setContentsMargins(0, 0, 0, 0);
}

CustomSliderWidget::~CustomSliderWidget()
{

}

void CustomSliderWidget::setDefaultValue(int value)
{
    _defaultValue = value;
}

void CustomSliderWidget::setMinimum(int value)
{
    _slider->setMinimum(value);
}

void CustomSliderWidget::setMaximum(int value)
{
    _slider->setMaximum(value);
}

void CustomSliderWidget::setLabel(QString value)
{
    _label->setText(value);
}

void CustomSliderWidget::resetValue()
{
    setValue(_defaultValue);
}

void CustomSliderWidget::setValue(float value)
{
    _slider->setValue(value*_ratio);
    _valueLabel->setText(QString::number(value));
}

void CustomSliderWidget::changeValue(int value)
{
    emit valueChanged(((float)value)/((float)_ratio));
    _valueLabel->setText(QString::number(((float)value)/((float)_ratio)));
}

int CustomSliderWidget::value()
{
    return ((float)_slider->value())/((float)_ratio);
}

void CustomSliderWidget::setRatio(int ratio)
{
    _ratio = ratio;
}
