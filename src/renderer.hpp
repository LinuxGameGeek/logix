#ifndef RENDERER_H
#define RENDERER_H
/*
 This is the renderer of the viewport
*/
#include "viewport/shader.hpp"
#include "viewport/vertexbuffer.hpp"
#include "viewport/indexbuffer.hpp"
#include "viewport/vertexarray.hpp"
#include <iostream>
#include <gtkmm-3.0/gtkmm/glarea.h>
#include <epoxy/gl.h>

class Renderer{
	public:
		Renderer(Gtk::GLArea*);
		void realize();
    	void unrealize();
    	void resize(int width, int height);
    	bool render(const Glib::RefPtr<Gdk::GLContext>&);
	private:
		Gtk::GLArea* glArea;
		GLuint shader_program;
		GLuint vao;
		IndexBuffer* ibptr;
		VertexBuffer* vbptr;
		VertexArray* vaptr;
		VertexBufferLayout* vblptr;
};

#endif //