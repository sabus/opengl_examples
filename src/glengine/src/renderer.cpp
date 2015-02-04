#include <cstdlib>
#include <iostream>
#include <glengine/renderer.h>
#include <glengine/logger.h>
#include <vector>
#include <string>
#include <glengine/shader.h>
#include <glengine/program.h>
#include <glengine/utils.h>
#include <GL/glew.h>

Renderer::Renderer() {
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    ERROR()<< "Initialising GLEW failed with the following error: " << glewGetErrorString(err);
    std::exit(-1);
  }
  if(!GLEW_VERSION_3_3) {
      ERROR() << "OpenGL 3.3 context is not available";
      std::exit(-1);
  }
  DEBUG() << glengine::checkOpenGLErrors("Renderer");
  DEBUG()<< "Driver Version String: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  DEBUG()<< "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
  DEBUG()<< "Renderer: " << glGetString(GL_RENDERER);
  char vShaderStr[] = "#version 330\n"
      "layout(location = 0) in vec5 vPosition; \n"
      "void main() \n"
      "{ \n"
      " gl_Position.xyz = vPosition; \n"
      "gl_Position.w = 1.0;\n"
      "} \n";
  char fShaderStr[] = "#version 330\n"
      "precision mediump float; \n"
      "out vec3 fragColor; \n"
      "void main() \n"
      "{ \n"
      " fragColor = vec3 ( 0.0, 1.0, 0.0 ); \n"
      "} \n";
  glengine::shader vertexShader(GL_VERTEX_SHADER,vShaderStr);
  glengine::shader fragmentShader(GL_FRAGMENT_SHADER,fShaderStr);
  mProgram = new glengine::program({vertexShader,fragmentShader});

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  glGenBuffers(1, &mBuffer);
  INFO()<<glengine::checkOpenGLErrors("glGenBuffers");
  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  INFO()<<glengine::checkOpenGLErrors("glBindBuffer");

  static const GLfloat vVertices[] = {
      -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
  INFO()<<glengine::checkOpenGLErrors("glBufferData");

//  // Store the program object
//  INFO() << "Program object " << programObject;
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
  int i = glGetAttribLocation(mProgram->getHandle(),"vPosition");
  INFO() << "Attrib location: " << i;
}

void Renderer::cleanup() {

}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(mProgram->getHandle());
  INFO() << glengine::checkOpenGLErrors("glUseProgram");
  glEnableVertexAttribArray(0);
  INFO() << glengine::checkOpenGLErrors("glEnableVertexAttribArray");
  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  INFO() << glengine::checkOpenGLErrors("glBindBuffer");
  glVertexAttribPointer(
     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
     3,                  // size
     GL_FLOAT,           // type
     GL_FALSE,           // normalized?
     0,                  // stride
     (void*)0            // array buffer offset
  );
  INFO() << glengine::checkOpenGLErrors("glVertexAttribPointer");

  glDrawArrays ( GL_TRIANGLES, 0, 3 );
  glDisableVertexAttribArray(0);
//  INFO() << "DRAW ERROR: "<< glengine::checkOpenGLErrors("glDrawArrays");
}

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

Renderer::~Renderer() {

}
