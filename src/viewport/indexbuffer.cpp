#include "./indexbuffer.hpp"
/*
 This is the vertex buffer class
*/

IndexBuffer::IndexBuffer(const GLuint* data, GLuint count)
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
