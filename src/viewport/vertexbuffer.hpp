#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <epoxy/gl.h>

class VertexBuffer{
  public:
    VertexBuffer(const void* data, GLuint size);
    ~VertexBuffer();
    void bind() const;
    void unbind() const;
  private:
    GLuint m_rendererID;
};

#endif
