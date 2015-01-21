#include "renderer.h"
#include <GL/glew.h>
#include <cstdio>
#include <iostream>
#include <logger.h>
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
      char *infoLog = (char*) malloc(sizeof(char) * infoLen);
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
    ERROR()<< glewGetErrorString(err);
    return;
  }
  char vShaderStr[] = "#version 300 es \n"
      "layout(location = 0) in vec4 vPosition; \n"
      "void main() \n"
      "{ \n"
      " gl_Position = vPosition; \n"
      "} \n";
  char fShaderStr[] = "#version 300 es \n"
      "precision mediump float; \n"
      "out vec4 fragColor; \n"
      "void main() \n"
      "{ \n"
      " fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 ); \n"
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
  // Store the program object
  printf("Program object %d\n", programObject);
//    userData->programObject = programObject;
  glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
//    return TRUE;
}

void Renderer::cleanup() {

}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

Renderer::~Renderer() {

}
