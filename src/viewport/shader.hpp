#ifndef SHADER_H
#define SHADER_H
#include <epoxy/gl.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <dirent.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
  public:
  	Shader(char* dirpath);
  	~Shader();
  	void bind() const;
  	void unbind() const;
  	inline GLuint get_program(){return shader_program;};

  	void set_uniform4f(const std::string& name, glm::vec4);
  	void set_uniform_mat4f(const std::string& name, const glm::mat4&);

    static GLuint create_shader_program(std::vector<GLuint>* shaders);
    static GLuint create_shader(GLenum, char* path);
  protected:
  private:
  	GLuint shader_program;
    static std::string read_file(char*);
    struct dirent *drnt;

    inline GLuint get_uniform_location(const std::string& name);
};
#endif