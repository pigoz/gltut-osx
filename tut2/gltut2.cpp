#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "../framework/framework.h"
#include "../framework/shader.hpp"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

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
                 vertex_data, GL_STREAM_DRAW);
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

void ComputePositionOffsets(float &fXOffset, float &fYOffset)
{
    const float fLoopDuration = 5.0f;
    const float fScale = 3.14159f * 2.0f / fLoopDuration;
    float fElapsedTime = getElapsedTime();
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
    fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}

void AdjustVertexData(float fXOffset, float fYOffset)
{
    std::vector<float> fNewData(ARRAY_COUNT(vertex_data));
    memcpy(&fNewData[0], vertex_data, sizeof(vertex_data));
    for(int iVertex = 0; iVertex < ARRAY_COUNT(vertex_data); iVertex += 4)
    {
        fNewData[iVertex] += fXOffset;
        fNewData[iVertex + 1] += fYOffset;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_data), &fNewData[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void render(CGLContextObj cgl_ctx) {
    float fXOffset = 0.0f, fYOffset = 0.0f;
    ComputePositionOffsets(fXOffset, fYOffset);
    AdjustVertexData(fXOffset, fYOffset);

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
