#include "./vertexbuffer.hpp"

VertexBuffer::VertexBuffer(const void* data, GLuint size){
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
  glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::bind() const{
  glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::unbind() const{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
