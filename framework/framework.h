#include <OpenGL/OpenGL.h>

void glGenVertexArrays(GLsizei n, GLuint *arrays);
void glBindVertexArray(GLuint array);

GLuint CreateShader(GLenum shader_type, const char *shader_string);
GLuint CreateProgram(size_t total_shaders, const GLuint *shader_list);
