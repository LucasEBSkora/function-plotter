#include <assert.h>

#include <GL/glew.h>

#define GLcall(x) GLClearError();\
  x;\
  assert(glLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool glLogCall(const char* function, const char* file, int line);
