#include "IndexBuffer.hpp"

#include "GLErrorUtils.hpp"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : m_count{count} {

  assert(sizeof (unsigned int) == sizeof (GLuint));

  GLcall(glGenBuffers(1, &m_renderer_ID)); //cria um buffer novo, com a id armazena na variável buffer
  GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID)); //seleciona o buffer usado
  GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));  //adiciona os dados no buffer criado


}

IndexBuffer::~IndexBuffer() {
  GLcall(glDeleteBuffers(1, &m_renderer_ID));
}

void IndexBuffer::bind() const {
  GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID)); //seleciona o buffer usado
}

void IndexBuffer::unbind() const {
  GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); //seleciona o buffer usado
}