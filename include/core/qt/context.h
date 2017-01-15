#ifndef CONTEXT_H
#define CONTEXT_H

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLFunctions>
#include <QOpenGLContext>


class Context : public QOpenGLFunctions_4_5_Core
{
public:
    static Context&                         instance();
    static QOpenGLFunctions_4_5_Core&       functions();
    void                                    setFunctionsPointer(QOpenGLFunctions_4_5_Core* functionPointer);

private:
    Context&                                operator=(const Context&){return instance();}
                                            Context(const Context&){}

    static Context                          _instance;

    QOpenGLFunctions_4_5_Core&              getFunctionsPointer();

    QOpenGLFunctions_4_5_Core*              _functionPointer;

                                            Context();
                                            ~Context(){};
};

#endif // CONTEXT_H
