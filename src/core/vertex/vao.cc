#include "core/vertex/vao.h"
#include "core/debug.h"

#include <algorithm>
#include <iostream>

namespace orangutan {

void Vao::bind() const {
  GL_CHECK_ERROR(glBindVertexArray(_vaoHandle.getId()));
}

void Vao::unbind() const { GL_CHECK_ERROR(glBindVertexArray(0)); }

void Vao::bindIndexBuffer() const {
  GL_CHECK_ERROR(
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandle.getId()));
}

void Vao::fillIndexBuffer(size_t size, const void *data) {
  GL_CHECK_ERROR(
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferHandle.getId()));
  GL_CHECK_ERROR(
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  GL_CHECK_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Vao::unbindIndexBuffer() const {
  GL_CHECK_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Vao::setNumberOfElements(int nbElements) { _nbElements = nbElements; }

unsigned int Vao::addBuffer() {
  BufferHandle handle;
  _bufferHandles.push_back(std::move(handle));
  return _bufferHandles.size() - 1;
}

void Vao::removeBuffer(unsigned int id) {
  _bufferHandles.erase(_bufferHandles.begin() + id);
}

void Vao::bindBuffer(unsigned int id) const {
  GL_CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, _bufferHandles.at(id).getId()));
}

void Vao::fillBuffer(unsigned int id, size_t size, const void *data) {
  bindBuffer(id);
  GL_CHECK_ERROR(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
  unbindBuffer();
}

void Vao::attribBuffer(unsigned int id, int attributeLocation, int size,
                       int type) {
  bind();
  unsigned int t;
  switch (type) {
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
  GL_CHECK_ERROR(glEnableVertexAttribArray(attributeLocation));
  bindBuffer(id);
  glVertexAttribPointer(attributeLocation, size, t, GL_FALSE, 0,
                        BUFFER_OFFSET(0));
  unbindBuffer();
  unbind();
}

void Vao::unbindBuffer() const {
  GL_CHECK_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Vao::drawElements() const {
  bind();
  GL_CHECK_ERROR(glDrawElements(GL_TRIANGLES, _nbElements, GL_UNSIGNED_INT,
                                BUFFER_OFFSET(0)));
  unbind();
}

} // namespace orangutan
