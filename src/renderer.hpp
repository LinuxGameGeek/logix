#ifndef RENDERER_DATA_H
#define RENDERER_DATA_H
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
struct scene{				//viewport data
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 mvp;
	float zoom = 1.0f;
	glm::vec2 dim;
	glm::vec3 pos = {0, 0, 1.0f};
};

struct pointer{				//mouse data
	int button;
	int x, y;
};

struct keyboard{			//keyboard data

};

#endif

#ifndef RENDERER_H
#define RENDERER_H
/*
 This is the renderer of the viewport
*/
#include "viewport/shader.hpp"
#include "viewport/vertexbuffer.hpp"
#include "viewport/indexbuffer.hpp"
#include "viewport/vertexarray.hpp"
#include <gtkmm-3.0/gtkmm/glarea.h>
#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <gdkmm-3.0/gdkmm/glcontext.h>
//#include <glibmm-2.4/glibmm/refptr.h>
//#include <epoxy/gl.h>
//#include <epoxy/glx.h>
#include <iostream>

class Renderer{
	public:
		Renderer(Gtk::GLArea*);								//constructor connects the following callbacks:
		void realize();										//called when widget glArea is created
    	void unrealize();									//called when widget glArea is destroyed
    	void resize(int width, int height);					//called when the glArea is resized
    	bool render(const Glib::RefPtr<Gdk::GLContext>&);	//called when the viewport should render itself
    	bool mouse_move(GdkEventMotion* event);				//called when both mouse button pressed and mouse moved
    	bool mouse_scroll(GdkEventScroll* event);			//called when the mouse is wheel is rotated
    	bool button_press(GdkEventButton* button);			//called when a button is pressed
    	bool button_release(GdkEventButton* button);		//called when a button is released
	private:
		Gtk::GLArea* glArea;								//pointer to the glArea widget, created in ui object
		GLuint vao;
		IndexBuffer* ibptr;
		VertexBuffer* vbptr;
		VertexArray* vaptr;
		VertexBufferLayout* vblptr;
		Shader* shader_program;

		pointer mouse;										//mouse variable obj
		scene viewport;										//viewport variable obj

		void update_view();									//This function is resposible for paning and zooming the viewport
		glm::vec3 mouse_translate(glm::vec3);				//translates screen coords to world coords

};

#endif //