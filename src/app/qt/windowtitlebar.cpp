#include "app/qt/windowtitlebar.h"

#include <QToolBar>

WindowTitleBar::WindowTitleBar(QWidget *parent) : QMenuBar(parent), _isPressed(false)
{
    setFixedHeight(33);
}

void WindowTitleBar::mousePressEvent(QMouseEvent *event)
{
  _diff = event->pos();
  _isPressed = true;

  //setCursor(QCursor(Qt::SizeAllCursor));
}

void WindowTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
  Q_UNUSED(event);
    _isPressed = false;

  //setCursor(QCursor(Qt::ArrowCursor));
}

void WindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
  QPoint p = event->globalPos();
    if(_isPressed)
        window()->move(p - _diff);
}
