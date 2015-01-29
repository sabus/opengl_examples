#include <GL/glew.h>
#include <cstdlib>
#include <iostream>
#include <glengine/renderer.h>
#include <glengine/logger.h>
#include <vector>
#include <string>
std::string checkGlError(const char* funcName) {
    GLenum error = glGetError();
        std::string msg = funcName;
    if (error != GL_NO_ERROR) {
    msg.append(" ");
    msg.append(reinterpret_cast<const char*>(gluErrorString(error)));
    }
    return msg;
}

GLuint LoadShader(GLenum type, const char *shaderSrc) {
  GLuint shader;
  GLint compiled;
  // Create the shader object
  shader = glCreateShader(type);
  if (shader == 0) {
    return 0;
  }
  // Load the shader source
  glShaderSource(shader, 1, &shaderSrc, NULL);
  // Compile the shader
  glCompileShader(shader);
  // Check the compile status
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
      char *infoLog = (char*) std::malloc(sizeof(char) * infoLen);
      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
      printf("Error compiling shader:\n%s\n", infoLog);
      free(infoLog);
    }
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

Renderer::Renderer() {
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    ERROR()<< "Initialising GLEW failed with the following error: " << glewGetErrorString(err);
    std::exit(-1);
  }
  char vShaderStr[] = "#version 130\n"
      "vec4 vPosition; \n"
      "void main() \n"
      "{ \n"
      " gl_Position = vPosition; \n"
      "} \n";
  char fShaderStr[] = "#version 130\n"
//      "precision mediump float; \n"
      "out vec4 fragColor; \n"
      "void main() \n"
      "{ \n"
      " fragColor = vec4 ( 0.0, 0.0, 0.0, 1.0 ); \n"
      "} \n";
  GLuint vertexShader;
  GLuint fragmentShader;
  GLuint programObject;
  GLint linked;
  // Load the vertex/fragment shaders
  vertexShader = LoadShader( GL_VERTEX_SHADER, vShaderStr);
  fragmentShader = LoadShader( GL_FRAGMENT_SHADER, fShaderStr);
  // Create the program object
  programObject = glCreateProgram();
  if (programObject == 0) {
    ERROR()<< "Cannot create program object\n";
//        return 0;
  }
  glAttachShader(programObject, vertexShader);
  glAttachShader(programObject, fragmentShader);
  // Link the program
  glLinkProgram(programObject);
  // Check the link status
  glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
  if (!linked) {
    GLint infoLen = 0;
    glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen > 1) {
      char *infoLog = (char*) malloc(sizeof(char) * infoLen);
      glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
      ERROR()<< "Error linking program:\n" << infoLog;
      free(infoLog);
    }
    glDeleteProgram(programObject);
//    return FALSE;
  }
  mProgram = programObject;
  glGenBuffers(1, &mBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  INFO()<<checkGlError("BindBuffer");
  GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f
                        };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

  // Store the program object
  INFO() << "Program object " << programObject;
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  GLint numActiveAttribs = 0;
  glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
  GLint maxAttribNameLength = 0;
  glGetProgramiv(mProgram,GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttribNameLength);
  INFO() << "Attribute length: " << numActiveAttribs;
  std::vector<GLchar> nameData(maxAttribNameLength);
  for(int attrib = 0; attrib < numActiveAttribs; ++attrib)
  {
      GLint arraySize = 0;
      GLenum type = 0;
      GLsizei actualLength = 0;
      glGetActiveAttrib(mProgram, attrib, nameData.size(), &actualLength, &arraySize, &type, &nameData[0]);
      std::string name((char*)&nameData[0], actualLength - 1);
      INFO() << "Attribute: " << name;
  }
  //    return TRUE;
}

void Renderer::cleanup() {

}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     (void*)0            // array buffer offset
  );
  // Use the program object
  INFO() << "Is program: " <<(int)glIsProgram(mProgram);
  glUseProgram ( mProgram );
  INFO() << glGetError();

  glDrawArrays ( GL_TRIANGLES, 0, 3 );
  glDisableVertexAttribArray(0);
  INFO() << "DRAW ERROR: "<< checkGlError("glDrawArrays");
}

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

Renderer::~Renderer() {

}
