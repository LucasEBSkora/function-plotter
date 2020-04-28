#ifndef __VERTEXARRAY_HPP__
#define __VERTEXARRAY_HPP__

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
  private:
    unsigned int m_renderer_ID;
  public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;
};

#endif