#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <cassert>
#include <ostream>
namespace glengine {
class shader
{
public:
    shader(int vertexType,const std::string source);
    ~shader();
    bool isValid() const;
    unsigned int getHandle() const;
    friend std::ostream& operator <<(std::ostream& os,const shader& shad);
private:
    const std::string mShaderSource;
    unsigned int mShaderType;
    unsigned int mShaderHandle;
    bool mIsValid;
};

}
#endif // SHADER_H
