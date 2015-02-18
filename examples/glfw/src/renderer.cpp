#include <cstdlib>
#include <iostream>
#include <renderer.h>
#include <glengine/logger.h>
#include <vector>
#include <string>
#include <glengine/shader.h>
#include <glengine/program.h>
#include <glengine/utils.h>
#include <GL/glew.h>
#include <fstream>

Renderer::Renderer():mIsDirty(true) {
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    ERROR() << "Initialising GLEW failed with the following error: "
            << glewGetErrorString(err);
    std::exit(-1);
  }
  if (!GLEW_VERSION_3_3) {
    ERROR() << "OpenGL 3.3 context is not available";
    std::exit(-1);
  }
  DEBUG() << glengine::checkOpenGLErrors("Renderer");
  DEBUG() << "Driver Version String: "
          << reinterpret_cast<const char*>(glGetString(GL_VERSION));
  DEBUG() << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
  DEBUG() << "Renderer: " << glGetString(GL_RENDERER);
  std::ifstream vertexFile("assets/vertex.glsl");
  std::string vertexShaderString;
  if(vertexFile.is_open()) {
	  vertexShaderString.append(std::istreambuf_iterator<char>(vertexFile),std::istreambuf_iterator<char>());
	  vertexFile.close();
	  INFO() << "Vertex shader: \n" << vertexShaderString;
  }
  std::ifstream fragmentFile("assets/fragment.glsl");
  std::string fragmentShaderString;
  if(fragmentFile.is_open()) {
	  fragmentShaderString.append(std::istreambuf_iterator<char>(fragmentFile),std::istreambuf_iterator<char>());
	  fragmentFile.close();
	  INFO() << "Fragment shader: \n" << fragmentShaderString;
  }
  glengine::shader vertexShader(GL_VERTEX_SHADER, vertexShaderString);
  glengine::shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderString);
  mProgram = new glengine::program({vertexShader, fragmentShader});

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  glGenBuffers(1, &mBuffer);
  INFO() << glengine::checkOpenGLErrors("glGenBuffers");
  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  INFO() << glengine::checkOpenGLErrors("glBindBuffer");

  static const GLfloat vVertices[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
  INFO() << glengine::checkOpenGLErrors("glBufferData");

  //  // Store the program object
  //  INFO() << "Program object " << programObject;
  glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
  int i = glGetAttribLocation(mProgram->getHandle(), "vPosition");
  INFO() << "Attrib location: " << i;
}

void Renderer::cleanup() {}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  mProgram->use();
  INFO() << glengine::checkOpenGLErrors("glUseProgram");
  glEnableVertexAttribArray(0);
  INFO() << glengine::checkOpenGLErrors("glEnableVertexAttribArray");
  glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
  INFO() << glengine::checkOpenGLErrors("glBindBuffer");
  glVertexAttribPointer(0,  // attribute 0. No particular reason for 0, but must
                            // match the layout in the shader.
                        3,  // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void*)0   // array buffer offset
                        );
  INFO() << glengine::checkOpenGLErrors("glVertexAttribPointer");

  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
  //  INFO() << "DRAW ERROR: "<< glengine::checkOpenGLErrors("glDrawArrays");
}

void Renderer::resize(int width, int height) {
  glViewport(0, 0, width, height);
}

Renderer::~Renderer() {}

bool Renderer::isDirty() {
	return mIsDirty;
}
