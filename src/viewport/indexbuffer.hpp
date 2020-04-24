#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <epoxy/gl.h>

class IndexBuffer{
  public:
   IndexBuffer(const void* data, GLuint count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    
    inline GLuint GetCount() const {return m_count;}
  private:
    GLuint m_rendererID;
    GLuint m_count;
};

#endif
