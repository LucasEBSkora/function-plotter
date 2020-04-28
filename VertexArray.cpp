#include "VertexArray.hpp"

#include "GLErrorUtils.hpp"

VertexArray::VertexArray() {
  GLcall(glGenVertexArrays(1, &m_renderer_ID));
}

VertexArray::~VertexArray() {
  GLcall(glDeleteVertexArrays(1, &m_renderer_ID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
  bind();
  vb.bind();
  const auto& elements = layout.getElements();
  intptr_t offset = 0;

  for (unsigned int i = 0; i < elements.size(); ++i) {
  
    const auto& element = elements[i];
    GLcall(glEnableVertexAttribArray(i));
    GLcall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset));
    offset += element.count * VertexBufferElement::getSizeOfType(element.type);
  
  }

}

void VertexArray::bind() const {
  GLcall(glBindVertexArray(m_renderer_ID));
}

void VertexArray::unbind() const {
  GLcall(glBindVertexArray(0));
}
