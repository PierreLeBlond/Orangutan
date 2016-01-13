#ifndef OPENGL_H
#define OPENGL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QOpenGLContext>


class OpenGLFunction : public QOpenGLFunctions_3_3_Core
{
public:
    static OpenGLFunction&                  Instance();
    static QOpenGLFunctions_3_3_Core&       functions();
    void                                    setFunctionsPointer(QOpenGLFunctions_3_3_Core* functionPointer);

private:
    OpenGLFunction&                         operator=(const OpenGLFunction&){}
                                            OpenGLFunction(const OpenGLFunction&){}

    static OpenGLFunction                   _instance;

    QOpenGLFunctions_3_3_Core&              getFunctionsPointer();

    QOpenGLFunctions_3_3_Core*              _functionPointer;

                                            OpenGLFunction();
                                            ~OpenGLFunction();
};

#endif // OPENGL_H
