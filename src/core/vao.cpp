#include "core/vao.h"

Vao::Vao()
{
     OpenGLFunction::functions().glGenVertexArrays(1, &_vao);
     OpenGLFunction::functions().glGenBuffers(1, &_indexBufferId);
}

Vao::~Vao()
{
    for(size_t i = 0; i < _bufferIds.size(); i++)
    {
         OpenGLFunction::functions().glDeleteBuffers(1, &_bufferIds[i]);
    }

    OpenGLFunction::functions().glDeleteBuffers(1, &_indexBufferId);
    OpenGLFunction::functions().glDeleteVertexArrays(1, &_vao);
}

void Vao::setNumberOfElements(int nbElements)
{
    _nbElements = nbElements;
}

unsigned int Vao::addBuffer()
{
    unsigned int id;
    OpenGLFunction::functions().glGenBuffers(1, &id);

    _bufferIds.push_back(id);
    return id;
}

void Vao::bind() const
{
     OpenGLFunction::functions().glBindVertexArray(_vao);
}

void Vao::unbind() const
{
     OpenGLFunction::functions().glBindVertexArray(0);
}

void Vao::bindIndexBuffer() const
{
     OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
}

void Vao::fillIndexBuffer(size_t size, const void* data)
{
    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
    OpenGLFunction::functions().glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vao::unbindIndexBuffer() const
{
     OpenGLFunction::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vao::drawElements() const
{
    OpenGLFunction::functions().glDrawElements(GL_TRIANGLES, _nbElements, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}

void Vao::fillBuffer(unsigned int bufferId, size_t size, const void* data)
{
    OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    OpenGLFunction::functions().glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vao::attribBuffer(unsigned int bufferId, int attributeLocation, int size, int type)
{
    OpenGLFunction::functions().glEnableVertexAttribArray(attributeLocation);
    OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    OpenGLFunction::functions().glVertexAttribPointer(attributeLocation, size, type, GL_FALSE, 0, BUFFER_OFFSET(0));
    OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vao::bindBuffer(unsigned int bufferId) const
{
    OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void Vao::unbindBuffer() const
{
    OpenGLFunction::functions().glBindBuffer(GL_ARRAY_BUFFER, 0);
}
