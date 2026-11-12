#include "gl43.h"
#define GLAD_GL_IMPLEMENTATION
#include "gl.h"
#include <stdlib.h>

void *io__read_bytes(const char *_Path) {
    FILE *f = NULL;
    f = fopen(_Path, "rb");
    fseek(f, 0, SEEK_END);
    long long s = ftell(f);
    rewind(f);
    char *b = malloc(s+1);
    fread(b, 1, s, f);
    b[s] = '\0';
    fclose(f);
    return b;
}

unsigned gl43_new_program(unsigned *_Type, const char **_String, int _Count) {
    unsigned program = glCreateProgram();
    unsigned *shader = calloc(_Count, sizeof(unsigned));
    for (int i = 0; i < _Count; i++) {
        shader[i] = glCreateShader(_Type[i]);
        glShaderSource(shader[i], 1, &_String[i], NULL);
        glCompileShader(shader[i]);
        int compiled;
        glGetShaderiv(shader[i], GL_COMPILE_STATUS, &compiled);
        if (compiled) glAttachShader(program, shader[i]);
        else {
            int logLength = 0;
            glGetShaderiv(shader[i], GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                char *infoLog = (char*)malloc(logLength);
                glGetShaderInfoLog(shader[i], logLength, NULL, infoLog);
                fprintf(stderr, "[GL43]: %s\n", infoLog);
                free(infoLog);
            }
        }
    }
    glLinkProgram(program);
    for (int i = 0; i < _Count; i++) {
        glDetachShader(program, shader[i]);
        glDeleteShader(shader[i]);
    }
    free(shader);
    return program;
}

unsigned gl43_load_program(const char *_VertexPath, const char *_FragmentPath) {
    char *v = io__read_bytes(_VertexPath);
    char *f = io__read_bytes(_FragmentPath);
    gl43_new_program(
        (unsigned[]){GL_VERTEX_SHADER, GL_FRAGMENT_SHADER},
        (const char*[]){v, f},
        2
    );
    free(v);
    free(f);
}

unsigned gl43_load_compute(const char *_ComputePath) {
    char *c = io__read_bytes(_ComputePath);
    gl43_new_program(
        (unsigned[]){GL_COMPUTE_SHADER},
        (const char*[]){c},
        1
    );
    free(c);
}