#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "./vertexbuffer.hpp"
#include "./vertexbufferlayout.hpp"

class VertexArray{
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;
	private:
		GLuint rendererID;
};

#endif