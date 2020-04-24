#include "./shader.hpp"


GLuint Shader::create_shader_program(char* dir = nullptr){
  GLuint vertex_shader;
  GLuint fragment_shader;
  if(dir != nullptr){

  }else{
    char vpath[] = "./src/res/shaders/vertex.glsl";
    char fpath[] = "./src/res/shaders/fragment.glsl";
    vertex_shader = create_shader(GL_VERTEX_SHADER, vpath);
    fragment_shader = create_shader(GL_FRAGMENT_SHADER, fpath);
  }
  std::clog<<"Linking program!\n";
  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glValidateProgram(shader_program);
  //glLinkProgram(shader);
  GLint result;
  glGetShaderiv(shader_program, GL_LINK_STATUS, &result);
  if(result == GL_FALSE){
      int length;
      glGetShaderiv(shader_program, GL_INFO_LOG_LENGTH, &length);
      char* message = (char *)alloca(length * sizeof(char));
      glGetShaderInfoLog(shader_program, length, &length, message);
      std::cerr<<"Failed to compile shaderprogram! type:"<<std::endl;
      std::cerr<<message<<std::endl;
      glDeleteProgram(shader_program);
      return 0;
  }else{
      std::clog<<"Shaderprogram compiled successfully!"<<std::endl;
      return shader_program;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return shader_program;
}

GLuint Shader::create_shader(GLenum type, char* path){
  GLuint shader = glCreateShader(type);
  std::string shaderStr = read_file(path);
  const char* shaderSrc = shaderStr.c_str();


  glShaderSource(shader, 1, &shaderSrc, nullptr);
  glCompileShader(shader);

  int result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE){
      int length;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
      char* message = (char *)alloca(length * sizeof(char));
      glGetShaderInfoLog(shader, length, &length, message);
      std::cerr<<"Failed to compile shader! type:"<<type<<std::endl;
      std::cerr<<message<<std::endl;
      glDeleteShader(shader);
      return 0;
  }else{
      std::clog<<"Shader compiled successfully! type: "<<type<<std::endl;
      return shader;
  }
}

std::string Shader::read_file(char *path){
  std::string content;
  std::ifstream fileStream(path, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

  fileStream.close();
  return content;
}
