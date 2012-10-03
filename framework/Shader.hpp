#include "framework.h"
#include <vector>
GLuint CreateShader(GLenum shader_type, const char *shader_string);
GLuint CreateProgram(const std::vector<GLuint> &shaderList);
