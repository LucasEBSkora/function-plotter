#include "VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout() : m_Stride{0} {

}

template<typename T>
void VertexBufferLayout::Push(unsigned int count) {
  assert(false);
}

template<>
void VertexBufferLayout::Push<float>(unsigned int  count) {
  m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_Stride += count*VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int  count) {
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += count*VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int  count) {
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += count*VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}