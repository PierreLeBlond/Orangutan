#ifndef VAO_H
#define VAO_H

#include "core/opengl.h"

#include "util/util.h"

enum O_Type {
    O_FLOAT = GL_FLOAT,
    O_INT = GL_INT
};

enum O_Bool {
    O_FALSE = GL_FALSE,
    O_TRUE = GL_TRUE
};

enum O_Buffer_Type {
    O_ARRAY_BUFFER  = GL_ARRAY_BUFFER,
    O_ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER
};

class Vao
{
    public :

                                        Vao();
                                        ~Vao();
    unsigned int                        addBuffer();
    void                                bind() const;
    void                                unbind() const;

    void                                bindIndexBuffer() const;
    void                                fillIndexBuffer(size_t size, const void* data);
    void                                unbindIndexBuffer() const;

    void                                setNumberOfElements(int nbElements);

    void                                bindBuffer(unsigned int bufferId) const;
    void                                fillBuffer(unsigned int bufferId, size_t size, const void* data);
    void                                attribBuffer(unsigned int bufferId, int attributeLocation, int size, int type);
    void                                unbindBuffer() const;

    void                                drawElements() const;

    private :

    unsigned int                        _vao;
    std::vector<unsigned int>           _bufferIds;
    unsigned int                        _indexBufferId;

    int                                 _nbElements;
};

#endif // VAO_H
