#ifndef WINDOWTITLEBAR_H
#define WINDOWTITLEBAR_H

#include <QWidget>
#include <QMenuBar>
#include <QMouseEvent>

class WindowTitleBar : public QMenuBar
{
    Q_OBJECT
public:
                                WindowTitleBar(QWidget *parent = 0);

protected:

    void                        mousePressEvent  (QMouseEvent *event);
    void                        mouseReleaseEvent(QMouseEvent *event);
    void                        mouseMoveEvent   (QMouseEvent *event);

signals:

public slots:

private:
    QPoint                      _diff;
    bool                        _isPressed;
};

#endif // WINDOWTITLEBAR_H
