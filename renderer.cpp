#include "renderer.hpp"

#include "GL/glew.h"
#include "GLErrorUtils.hpp"

void Renderer::draw(unsigned int type, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
  
  shader.bind();
  va.bind();
  ib.bind();

  GLcall(glDrawElements(type, ib.getCount(), GL_UNSIGNED_INT, nullptr));

}   

void Renderer::clear() const {
  GLcall(glClear(GL_COLOR_BUFFER_BIT));
}