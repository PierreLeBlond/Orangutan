#ifndef VAO_H
#define VAO_H

#include <iostream>
#include <vector>

#include "util/util.h"

enum O_Type {
    O_FLOAT = 0,
    O_INT = 1
};

enum O_Bool {
    O_FALSE = 0,
    O_TRUE = 1
};

enum O_Buffer_Type {
    O_ARRAY_BUFFER  = 0,
    O_ELEMENT_ARRAY_BUFFER = 1
};

class Vao
{
    public :

                                        Vao();
                                        ~Vao();
    unsigned int                        addBuffer();
    void                                deleteBuffer(unsigned int id);
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
