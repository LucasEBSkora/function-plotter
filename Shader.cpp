#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GLErrorUtils.hpp"


Shader::Shader(const std::string& filename) 
  : m_filePath{filename},
  m_Renderer_ID{0} {
   ShaderProgramSource source = ParseShader();

  m_Renderer_ID = createShader(source.vertexSource, source.fragmentSource);

}

Shader::~Shader() {
  GLcall(glDeleteProgram(m_Renderer_ID));
}

void Shader::bind() const {
  GLcall(glUseProgram(m_Renderer_ID));
}

void Shader::unbind() const {
  GLcall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, int v) {
  
  GLcall(glUniform1i(getUniformLocation(name), v));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
  
  GLcall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniforMat4f(const std::string& name, const glm::mat4& matrix) {
  
  GLcall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

struct Shader::ShaderProgramSource Shader::ParseShader() {
  std::ifstream stream(m_filePath);

  std::string line;
  std::stringstream ss[2];

  enum class ShaderType {
    NONE = -1, 
    VERTEX = 0,
    FRAGMENT = 1
  };

  ShaderType type = ShaderType::NONE;
  
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;

      } else if ((line.find("fragment") != std::string::npos)) {
        type = ShaderType::FRAGMENT;
      } 

    } else {

        ss[(int)type] << line << '\n';

      }
  }

  return {ss[0].str(), ss[1].str()};

} 


unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
  
  GLcall(unsigned int id = glCreateShader(type));
  const char* src = source.c_str();
  GLcall(glShaderSource(id, 1, &src, nullptr));
  GLcall(glCompileShader(id));
  
  int result;
  GLcall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); //integer, vector (pointer)

  if (result == GL_FALSE) {
    int length;
    GLcall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char* message = new char[length];
    GLcall(glGetShaderInfoLog(id, length, &length, message));
    std::cout << "failed to compile shader" << std::endl;
    std::cout << message << std::endl;
    GLcall(glDeleteShader(id));
    return 0;

  } else {
    std::cout << "compiled shader succesfully!" << std::endl;
  }

  return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
  
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLcall(glAttachShader(program, vs));
  GLcall(glAttachShader(program, fs));
  GLcall(glLinkProgram(program));
  GLcall(glValidateProgram(program));

  GLcall(glDeleteShader(vs));
  GLcall(glDeleteShader(fs));

  return program;
  
}


int Shader::getUniformLocation(const std::string& name) {

  if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
    return m_uniformLocationCache[name];

  GLcall(int location = glGetUniformLocation(m_Renderer_ID, name.c_str()));

  if (location == -1) 
    std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl; 
  else 
    m_uniformLocationCache[name] = location;
  
  return location;
}
