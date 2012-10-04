#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <vector>
#include "../framework/framework.h"
#include "../framework/shader.hpp"

const float vertex_data[] = {
     0.0f,    0.5f, 0.0f, 1.0f,
     0.5f, -0.366f, 0.0f, 1.0f,
    -0.5f, -0.366f, 0.0f, 1.0f,
     1.0f,    0.0f, 0.0f, 1.0f,
     0.0f,    1.0f, 0.0f, 1.0f,
     0.0f,    0.0f, 1.0f, 1.0f,
};

static GLuint vertex_buffer_object, vertex_array_object, shader_program;

static void InitializeVertexBuffer(void)
{
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data),
                 vertex_data, GL_STATIC_DRAW);
}

void InitializeProgram(void) {
    std::cout << "OpenGL initialization function\n" << std::endl;
    std::vector<GLuint> shaders;
    shaders.push_back(LoadShader(GL_VERTEX_SHADER, "pass_along.vert"));
    shaders.push_back(LoadShader(GL_FRAGMENT_SHADER, "uniform_color.frag"));
    shader_program = CreateProgram(shaders);
    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
}

void initialize_opengl(CGLContextObj cgl_ctx) {
    InitializeVertexBuffer();
    InitializeProgram();

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
}

void uninitialize_opengl(CGLContextObj cgl_ctx) {
    std::cout << "OpenGL un-initialization function\n" << std::endl;
}

void reshape (CGLContextObj cgl_ctx, int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void render(CGLContextObj cgl_ctx) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
            (void *) (sizeof(float)*3*4));

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glUseProgram(0);

    CGLFlushDrawable(cgl_ctx);
}
