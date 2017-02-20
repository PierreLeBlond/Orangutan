#include "core/vao.h"

#include "core/qt/context.h"

Vao::Vao()
{
     Context::functions().glGenVertexArrays(1, &_vao);
     Context::functions().glGenBuffers(1, &_indexBufferId);
}

Vao::~Vao()
{
    for(size_t i = 0; i < _bufferIds.size(); i++)
    {
         Context::functions().glDeleteBuffers(1, &_bufferIds[i]);
    }

    Context::functions().glDeleteBuffers(1, &_indexBufferId);
    Context::functions().glDeleteVertexArrays(1, &_vao);
}

void Vao::setNumberOfElements(int nbElements)
{
    _nbElements = nbElements;
}

unsigned int Vao::addBuffer()
{
    unsigned int id;
    Context::functions().glGenBuffers(1, &id);

    _bufferIds.push_back(id);
    return id;
}

void Vao::bind() const
{
     Context::functions().glBindVertexArray(_vao);
}

void Vao::unbind() const
{
     Context::functions().glBindVertexArray(0);
}

void Vao::bindIndexBuffer() const
{
     Context::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
}

void Vao::fillIndexBuffer(size_t size, const void* data)
{
    Context::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
    Context::functions().glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    Context::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vao::unbindIndexBuffer() const
{
     Context::functions().glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vao::drawElements() const
{
    Context::functions().glDrawElements(GL_TRIANGLES, _nbElements, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}

void Vao::fillBuffer(unsigned int bufferId, size_t size, const void* data)
{
    Context::functions().glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    Context::functions().glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    Context::functions().glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vao::attribBuffer(unsigned int bufferId, int attributeLocation, int size, int type)
{
    unsigned int t;
    switch(type)
    {
      case O_FLOAT:
        t = GL_FLOAT;
        break;
      case O_INT:
        t = GL_INT;
        break;
      default:
        t = GL_FLOAT;
        break;
    }

    Context::functions().glEnableVertexAttribArray(attributeLocation);
    Context::functions().glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    Context::functions().glVertexAttribPointer(attributeLocation, size, t, GL_FALSE, 0, BUFFER_OFFSET(0));
    Context::functions().glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vao::bindBuffer(unsigned int bufferId) const
{
    Context::functions().glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void Vao::unbindBuffer() const
{
    Context::functions().glBindBuffer(GL_ARRAY_BUFFER, 0);
}