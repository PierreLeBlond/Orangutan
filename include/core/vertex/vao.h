#ifndef VAO_H
#define VAO_H

#include <iostream>
#include <vector>

#include "core/buffer/bufferhandle.h"
#include "core/vertex/vertexarrayhandle.h"
#include "util/util.h"

enum O_Type { O_FLOAT = 0, O_INT = 1 };

enum O_Bool { O_FALSE = 0, O_TRUE = 1 };

enum O_Buffer_Type { O_ARRAY_BUFFER = 0, O_ELEMENT_ARRAY_BUFFER = 1 };

class Vao {
 public:
  void bind() const;
  void unbind() const;

  void bindIndexBuffer() const;
  void fillIndexBuffer(size_t size, const void* data);
  void unbindIndexBuffer() const;

  void setNumberOfElements(int nbElements);

  unsigned int addBuffer();
  void removeBuffer(unsigned int id);

  void bindBuffer(unsigned int id) const;
  void fillBuffer(unsigned int id, size_t size, const void* data);
  void attribBuffer(unsigned int id, int attributeLocation, int size, int type);
  void unbindBuffer() const;

  void drawElements() const;

 private:
  VertexArrayHandle _vaoHandle;
  std::vector<BufferHandle> _bufferHandles;
  BufferHandle _indexBufferHandle;

  int _nbElements;
};

#endif  // VAO_H
