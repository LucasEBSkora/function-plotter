#include "GLErrorUtils.hpp"

#include <iostream>

void GLClearError() {
  while (glGetError() != GL_NO_ERROR) {

  }
}

bool glLogCall(const char* function, const char* file, int line) {
  
  while(GLenum error = glGetError()) {
    std::cout << "Erro " << error << " na função " << function << ' ' << file << ':' << line << std::endl;
    return false;
  }
  return true;
}