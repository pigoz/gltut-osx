#import "shader.hpp"

GLuint CreateShader(GLenum shader_type, const char *shader_string)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_string, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
        GLchar *log_str = new GLchar[log_len + 1];
        glGetProgramInfoLog(shader, log_len, NULL, log_str);

        const char *shader_type_str = NULL;
        switch(shader_type) {
            case GL_VERTEX_SHADER:   shader_type_str = "vertex"; break;
//            case GL_GEOMETRY_SHADER: shader_type_str = "geometry"; break;
            case GL_FRAGMENT_SHADER: shader_type_str = "fragment"; break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n",
            shader_type_str, log_str);
    }
    return shader;
}

GLuint CreateProgram(const std::vector<GLuint> &shader_list)
{
    GLuint program = glCreateProgram();

    for(size_t i = 0; i < shader_list.size(); i++)
        glAttachShader(program, shader_list[i]);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint log_len;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &log_len);
        GLchar *log_str = new GLchar[log_len + 1];
        glGetProgramInfoLog(program, log_len, NULL, log_str);
        fprintf(stderr, "Linker failure: %s\n", log_str);
    }

    for(size_t i = 0; i < shader_list.size(); i++)
        glDetachShader(program, shader_list[i]);

    return program;
}
