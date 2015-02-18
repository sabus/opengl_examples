#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <glengine/shader.h>
namespace glengine {

class program {
 public:
  program(std::vector<glengine::shader>);
  bool isValid() const;
  void use();
  unsigned int getHandle() const;
  ~program();
  friend std::ostream& operator<<(std::ostream& os, const program& prog);

 private:
  unsigned int mProgramHandle;
  bool mIsValid;
};
}

#endif  // PROGRAM_H
