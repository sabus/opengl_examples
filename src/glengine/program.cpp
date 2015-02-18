#include <glengine/program.h>
#include <GL/glew.h>
#include <sstream>
#include <glengine/logger.h>

namespace glengine {
program::program(std::vector<shader> shaders) : mIsValid(false) {
  mProgramHandle = glCreateProgram();
  assert(mProgramHandle);
  for (shader s : shaders) {
    if (s.isValid()) {
      INFO() << "Attaching shader handle: " << s.getHandle();
      glAttachShader(mProgramHandle, s.getHandle());
    } else
      WARNING() << "Shader handle: " << s.getHandle()
                << " is invalid. Attaching dropped.";
  }
  GLint linked;
  glLinkProgram(mProgramHandle);
  glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &linked);
  INFO() << "Program link status: " << linked;
  if (!linked) {
    GLint infoLen = 0;
    glGetProgramiv(mProgramHandle, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
      char* infoLog = (char*)std::malloc(sizeof(char) * infoLen);
      glGetProgramInfoLog(mProgramHandle, infoLen, NULL, infoLog);
      ERROR() << "Error linking program:\n" << infoLog;
      std::free(infoLog);
    }
    glDeleteProgram(mProgramHandle);
  }
  mIsValid = linked ? true : false;
  INFO() << *this;
}

program::~program() {
  if (mIsValid) glDeleteProgram(mProgramHandle);
}

bool program::isValid() const { return mIsValid; }

unsigned int program::getHandle() const { return mProgramHandle; }

std::ostream& operator<<(std::ostream& os, const program& prog) {
  std::stringstream ss;
  ss << "Program[" << prog.mProgramHandle << "]: Valid: " << prog.isValid();
  GLint numActiveAttribs = 0;
  GLint numActiveUniforms = 0;
  glGetProgramInterfaceiv(prog.mProgramHandle, GL_PROGRAM_INPUT,
                          GL_ACTIVE_RESOURCES, &numActiveAttribs);
  glGetProgramInterfaceiv(prog.mProgramHandle, GL_UNIFORM, GL_ACTIVE_RESOURCES,
                          &numActiveAttribs);
  std::vector<GLchar> nameData(256);
  std::vector<GLenum> properties;
  properties.push_back(GL_NAME_LENGTH);
  properties.push_back(GL_TYPE);
  properties.push_back(GL_ARRAY_SIZE);
  properties.push_back(GL_LOCATION);
  std::vector<GLint> values(properties.size());
  ss << "Program Attributes:\n";
  for (int attrib = 0; attrib < numActiveAttribs; ++attrib) {
    glGetProgramResourceiv(prog.mProgramHandle, GL_PROGRAM_INPUT, attrib,
                           properties.size(), &properties[0], values.size(),
                           NULL, &values[0]);

    nameData.resize(properties[0]);  // The length of the name.
    glGetProgramResourceName(prog.mProgramHandle, GL_PROGRAM_INPUT, attrib,
                             nameData.size(), NULL, &nameData[0]);
    std::string name((char*)&nameData[0], nameData.size() - 1);
    ss << name << " : " << properties[1] << " , " << properties[2] << " , location = " << properties[3] << "\n";
  }
  ss << "Program Uniforms:\n";
  for (int uniform = 0; uniform < numActiveUniforms; ++uniform) {
    glGetProgramResourceiv(prog.mProgramHandle, GL_UNIFORM, uniform,
                           properties.size(), &properties[0], values.size(),
                           NULL, &values[0]);

    nameData.resize(properties[0]);  // The length of the name.
    glGetProgramResourceName(prog.mProgramHandle, GL_UNIFORM, uniform,
                             nameData.size(), NULL, &nameData[0]);
    std::string name((char*)&nameData[0], nameData.size() - 1);
    ss << name << " : " << properties[1] << " , " << properties[2] << " , location = " << properties[3] << "\n";
  }
  return os << ss;
}
}

