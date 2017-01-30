#include "core/vao.h"

#include <algorithm>

#include <nanogui/opengl.h>

Vao::Vao()
{
     glGenVertexArrays(1, &_vao);
     glGenBuffers(1, &_indexBufferId);
}

Vao::~Vao()
{
    for(size_t i = 0; i < _bufferIds.size(); i++)
    {
         glDeleteBuffers(1, &_bufferIds[i]);
    }

    glDeleteBuffers(1, &_indexBufferId);
    glDeleteVertexArrays(1, &_vao);
}

void Vao::setNumberOfElements(int nbElements)
{
    _nbElements = nbElements;
}

unsigned int Vao::addBuffer()
{
    unsigned int id;
    glGenBuffers(1, &id);

    _bufferIds.push_back(id);
    return id;
}

void Vao::deleteBuffer(unsigned int id)
{
    auto it = std::find(_bufferIds.begin(), _bufferIds.end(), id);
    if(it != _bufferIds.end())
    {
         glDeleteBuffers(1, &id);
         _bufferIds.erase(it);
    }
}

void Vao::bind() const
{
     glBindVertexArray(_vao);
}

void Vao::unbind() const
{
     glBindVertexArray(0);
}

void Vao::bindIndexBuffer() const
{
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
}

void Vao::fillIndexBuffer(size_t size, const void* data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vao::unbindIndexBuffer() const
{
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vao::drawElements() const
{
    glDrawElements(GL_TRIANGLES, _nbElements, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}

void Vao::fillBuffer(unsigned int bufferId, size_t size, const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    glEnableVertexAttribArray(attributeLocation);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glVertexAttribPointer(attributeLocation, size, t, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vao::bindBuffer(unsigned int bufferId) const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void Vao::unbindBuffer() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
