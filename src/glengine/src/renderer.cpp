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
//  if(!GLEW_VERSION_3_3) {
//      ERROR() << "OpenGL 3.3 context is not available";
//      std::exit(-1);
//  }
  DEBUG()<< "Driver Version String: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  DEBUG()<< "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
  DEBUG()<< "Renderer: " << glGetString(GL_RENDERER);
  char vShaderStr[] = "#version 140\n"
      "vec4 vPosition; \n"
      "void main() \n"
      "{ \n"
      " gl_Position = vPosition; \n"
      "} \n";
  char fShaderStr[] = "#version 330\n"
//      "precision mediump float; \n"
      "out vec4 fragColor; \n"
      "void main() \n"
      "{ \n"
      " fragColor = vec4 ( 0.0, 0.0, 0.0, 1.0 ); \n"
      "} \n";
  glengine::shader vertexShader(GL_VERTEX_SHADER,vShaderStr);
  glengine::shader fragmentShader(GL_FRAGMENT_SHADER,fShaderStr);
  glengine::program programObject({vertexShader,fragmentShader});
  INFO() << programObject;
//  glGenBuffers(1, &mBuffer);
//  INFO()<<glengine::checkOpenGLErrors("glGenBuffers");
//  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
//  INFO()<<glengine::checkOpenGLErrors("glBindBuffer");
//  GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f,
//                           -0.5f, -0.5f, 0.0f,
//                           0.5f, -0.5f, 0.0f
//                        };
//  glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

//  // Store the program object
//  INFO() << "Program object " << programObject;
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//  GLint numActiveAttribs = 0;
//  glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
//  GLint maxAttribNameLength = 0;
//  glGetProgramiv(mProgram,GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttribNameLength);
//  INFO() << "Attribute length: " << numActiveAttribs;
//  std::vector<GLchar> nameData(maxAttribNameLength);
//  for(int attrib = 0; attrib < numActiveAttribs; ++attrib)
//  {
//      GLint arraySize = 0;
//      GLenum type = 0;
//      GLsizei actualLength = 0;
//      glGetActiveAttrib(mProgram, attrib, nameData.size(), &actualLength, &arraySize, &type, &nameData[0]);
//      std::string name((char*)&nameData[0], actualLength - 1);
//      INFO() << "Attribute: " << name;
//  }
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
  INFO() << "DRAW ERROR: "<< glengine::checkOpenGLErrors("glDrawArrays");
}

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

Renderer::~Renderer() {

}
