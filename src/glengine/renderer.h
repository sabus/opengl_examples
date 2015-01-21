#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include <memory>
class Renderer {
 public:
  Renderer();
  virtual ~Renderer();
  virtual void render();
  virtual void cleanup();
  virtual void resize(int width, int height);
 private:
};

#endif // RENDERER_H
