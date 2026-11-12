#pragma once
#include "gl.h"

#define GL43_MAP_DISCARD_WRITE (GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)
#define GL43_MAP_UNSYNC_WRITE  (GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT)

unsigned gl43_new_program(unsigned *_Type, const char **_String, int _Count);
unsigned gl43_load_program(const char *_VertexPath, const char *_FragmentPath);
unsigned gl43_load_compute(const char *_ComputePath);