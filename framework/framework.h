#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

void glGenVertexArrays(GLsizei n, GLuint *arrays);
void glBindVertexArray(GLuint array);

#ifdef __cplusplus
extern "C" {
#endif
    void initialize_opengl(CGLContextObj cgl_ctx);
    void uninitialize_opengl(CGLContextObj cgl_ctx);
    void reshape(CGLContextObj cgl_ctx, int w, int h);
    void render(CGLContextObj cgl_ctx);
#ifdef __cplusplus
}
#endif
