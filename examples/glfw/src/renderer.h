#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <glengine/program.h>
class Renderer {
 public:
  Renderer();
  virtual ~Renderer();
  virtual void render();
  virtual void cleanup();
  virtual void resize(int width, int height);

 private:
  glengine::program* mProgram;
  unsigned int mBuffer;
};

#endif  // RENDERER_H
