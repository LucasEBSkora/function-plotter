#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <GL/glew.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {
  public:
    void draw(unsigned int type, const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void clear() const;  

};


#endif