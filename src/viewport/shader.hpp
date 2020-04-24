#ifndef SHADER_H
#define SHADER_H
#include <epoxy/gl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

class Shader{
  public:
    static GLuint create_shader_program(char*);
    static GLuint create_shader(GLenum, char* path);
  protected:
  private:
    static std::string read_file(char*);
};
#endif