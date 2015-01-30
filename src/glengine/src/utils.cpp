#include <glengine/utils.h>
#include <GL/glew.h>

namespace glengine {
    std::string checkOpenGLErrors(const char *function) {
        GLenum error = glGetError();
        std::string msg = function;
        if (error != GL_NO_ERROR) {
            msg.append(" ");
            msg.append(reinterpret_cast<const char*>(gluErrorString(error)));
        }
        return msg;
    }

}
