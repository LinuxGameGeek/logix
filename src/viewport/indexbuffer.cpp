#include "./indexbuffer.hpp"
#include <epoxy/gl.h>

IndexBuffer::IndexBuffer(const void* data, GLuint count)
:m_count(count){
  glGenBuffers(1, &m_rendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
  glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::bind() const{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::unbind() const{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint m_renderID;
GLuint m_count;
