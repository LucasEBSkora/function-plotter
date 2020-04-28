#include "VertexBuffer.hpp"

#include "GLErrorUtils.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {

  GLcall(glGenBuffers(1, &m_renderer_ID)); //cria um buffer novo, com a id armazena na variável buffer
  GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID)); //seleciona o buffer usado
  GLcall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));  //adiciona os dados no buffer criado


}

VertexBuffer::~VertexBuffer() {
  GLcall(glDeleteBuffers(1, &m_renderer_ID));
}

void VertexBuffer::bind() const {
  GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID)); //seleciona o buffer usado
}

void VertexBuffer::unbind() const {
  GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0)); //seleciona o buffer usado
}