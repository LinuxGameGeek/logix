#ifndef VERTEX_ATTRIB_ELEMENT_H
#define VERTEX_ATTRIB_ELEMENT_H

#include <epoxy/gl.h>

struct VertexAttribElement{
	GLuint type;
	GLuint count;
	bool normalized;
	static GLuint getTypeSize(GLuint varType){
		switch(varType){
			case GL_FLOAT: return sizeof(GLfloat);
			case GL_UNSIGNED_INT: return sizeof(GLuint);
			case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		}
		return 0;
	}
};
#endif

#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <epoxy/gl.h>
#include <vector>

class VertexBufferLayout{
public:
	inline VertexBufferLayout():stride(0){};
	//void add(GLuint count, GLuint type);

	void add(GLuint count, GLuint type){
		elements.push_back({type, count, false});
		switch(type){
			case GL_FLOAT: stride += count * sizeof(GLfloat); break;
			case GL_UNSIGNED_INT: stride += count * sizeof(GLuint); break;
			case GL_UNSIGNED_BYTE: stride += count * sizeof(GLubyte); break;
		}
	}

	inline const std::vector<VertexAttribElement> getElements() const& {return elements;}
	inline GLuint getStride() const {return stride;}

private:
	std::vector<VertexAttribElement> elements;
	GLuint stride;
};

#endif