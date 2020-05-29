#include "./shader.hpp"


Shader::Shader(char* dirpath){

	std::vector<GLuint> shaders;
	DIR *dir = nullptr;
	dir = opendir(dirpath);
	if(dir != nullptr){
		std::clog<<"loading files from: "<<dirpath<<"\n";
		while((drnt = readdir(dir))){
			std::clog<<drnt->d_name<<std::endl;
			char path[500];
			if(std::strcmp("vertex.glsl", drnt->d_name) == 0){
				sprintf(path, "%s/%s", dirpath, drnt->d_name);
				shaders.push_back(create_shader(GL_VERTEX_SHADER, path));
			}else if(std::strcmp("fragment.glsl", drnt->d_name) == 0){
				sprintf(path, "%s/%s", dirpath, drnt->d_name);
				shaders.push_back(create_shader(GL_FRAGMENT_SHADER, path));
			}else{
			}
		}
	}else{
		std::cerr<<"Couldnt open dir\n";
	}
	closedir(dir);
	shader_program = create_shader_program(&shaders);
	for(unsigned int i = 0; i < shaders.size(); i++)
	glDeleteShader(shaders[i]);
}

Shader::~Shader(){}

void Shader::bind() const{
	glUseProgram(shader_program);
}

void Shader::unbind() const{
	glUseProgram(0);
}

void Shader::set_uniform4f(const std::string& name, glm::vec4 data){
	glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(data));
}

void Shader::set_uniform2f(const std::string& name, glm::vec2 data){
	glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(data));
}

void Shader::set_uniform_mat4f(const std::string& name, const glm::mat4& matrix){
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set_uniform_float(const std::string& name, const GLfloat& Float){
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &Float);
}

GLuint Shader::get_uniform_location(const std::string& name){
	return glGetUniformLocation(shader_program, name.c_str());
}

GLuint Shader::create_shader_program(std::vector<GLuint>* shaders){
  std::clog<<"Linking program!\n";
  GLuint shader_program = glCreateProgram();
  for(unsigned int i = 0; i < shaders->size (); i++){
  	glAttachShader(shader_program, shaders->at(i));
  }
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
