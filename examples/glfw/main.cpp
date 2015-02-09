// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include <glengine/logger.h>
#include <log4cpp/PropertyConfigurator.hh>
#include <renderer.h>
GLFWwindow* window;


int main( void )
{
  std::string initFileName = "logger.properties";
  log4cpp::PropertyConfigurator::configure(initFileName);
  // Initialise GLFW
  if( !glfwInit() )
  {
    ERROR() << "Failed to initialize GLFW";
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
  if( window == NULL ){
    ERROR() << "Failed to open GLFW window.\n" ;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
//  if (glewInit() != GLEW_OK) {
//    ERROR() << "Failed to initialize GLEW";
//    return -1;
//  }

  Renderer* mRenderer = new Renderer();

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  mRenderer->resize(1024,768);

  // init engine

  do{
    mRenderer->render();
    // Clear the screen
//    glClear( GL_COLOR_BUFFER_BIT );
// draw
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
       glfwWindowShouldClose(window) == 0 );

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

