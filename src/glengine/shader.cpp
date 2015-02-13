#include <glengine/shader.h>
#include <GL/glew.h>
#include <glengine/logger.h>

namespace glengine {
shader::shader(int vertexType, const std::string source)
    : mShaderSource(std::move(source)),
      mShaderType(vertexType),
      mIsValid(false) {
  assert((vertexType == GL_VERTEX_SHADER || vertexType == GL_FRAGMENT_SHADER));
  mShaderHandle = glCreateShader(mShaderType);
  INFO() << "Created shader " << vertexType << " on handle " << mShaderHandle;
  assert(mShaderHandle);
  const char* cSource = mShaderSource.c_str();
  glShaderSource(mShaderHandle, 1, &cSource, NULL);
  glCompileShader(mShaderHandle);
  GLint compiled = 0;
  glGetShaderiv(mShaderHandle, GL_COMPILE_STATUS, &compiled);
  INFO() << "Shader compiled " << compiled;
  if (!compiled) {
    GLint infoLen = 0;
    glGetShaderiv(mShaderHandle, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
      char* infoLog = (char*)std::malloc(sizeof(char) * infoLen);
      glGetShaderInfoLog(mShaderHandle, infoLen, NULL, infoLog);
      ERROR() << "Error compiling shader:\n" << infoLog;
      std::free(infoLog);
    } else
      ERROR() << "Error compiling shader";
    glDeleteShader(mShaderHandle);
  }
  mIsValid = compiled ? true : false;
  INFO() << *this;
}

bool shader::isValid() const { return mIsValid; }

unsigned int shader::getHandle() const { return mShaderHandle; }

shader::~shader() {
  if (mIsValid) glDeleteShader(mShaderHandle);
}
std::ostream& operator<<(std::ostream& os, const shader& shad) {
  return os << "Shader[" << shad.getHandle() << " , "
            << ((shad.mShaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT")
            << "]: Valid: " << shad.mIsValid;
}
}
