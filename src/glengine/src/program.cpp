#include <glengine/program.h>
#include <GL/glew.h>
#include <glengine/logger.h>

namespace glengine {
    program::program(std::vector<shader> shaders):mIsValid(false)
    {
        mProgramHandle = glCreateProgram();
        assert(mProgramHandle);
        for(shader s : shaders) {
            if(s.isValid()) {
                INFO() << "Attaching shader handle: " << s.getHandle();
                glAttachShader(mProgramHandle,s.getHandle());
            } else
                WARNING() << "Shader handle: " << s.getHandle() << " is invalid. Attaching dropped.";
        }
        GLint linked;
        glLinkProgram(mProgramHandle);
        glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &linked);
        INFO() << "Program link status: " << linked;
        if(!linked) {
            GLint infoLen = 0;
            glGetProgramiv(mProgramHandle, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 1) {
              char *infoLog = (char*) std::malloc(sizeof(char) * infoLen);
              glGetProgramInfoLog(mProgramHandle, infoLen, NULL, infoLog);
              ERROR()<< "Error linking program:\n" << infoLog;
              std::free(infoLog);
            }
            glDeleteProgram(mProgramHandle);
        }
        mIsValid = linked ? true : false;
        INFO() << *this;
    }

    program::~program() {
        if(mIsValid)
            glDeleteProgram(mProgramHandle);
    }

    bool program::isValid() const{
        return mIsValid;
    }

    std::ostream& operator <<(std::ostream& os,const program& prog) {
        return os << "Program[" << prog.mProgramHandle <<"]: Valid: " << prog.isValid();
    }
}

