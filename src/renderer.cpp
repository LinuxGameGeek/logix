//#include <ui.hpp>
#include "./renderer.hpp"

#include <iostream>
#include <epoxy/gl.h>

Renderer::Renderer(Gtk::GLArea* glarea)
:glArea(glarea){
 	glArea->signal_realize().connect(sigc::mem_fun(*this, &Renderer::realize));
 	glArea->signal_unrealize().connect(sigc::mem_fun(*this, &Renderer::unrealize), false);
	glArea->signal_render().connect(sigc::mem_fun(*this, &Renderer::render));
	glArea->signal_resize ().connect(sigc::mem_fun(*this, &Renderer::resize));
}

void Renderer::realize(){
	std::clog<<glGetString(GL_VERSION)<<"\n";
	glArea->make_current();
	std::cout<<"realize\n";
	try{
		glArea->throw_if_error();
	}catch(const Gdk::GLError& gle){
		std::cerr << "An error occured making the context current during realize:" << std::endl;
		std::cerr << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
	}
}

void Renderer::unrealize(){
	glArea->make_current();
	try
	{
		windowPtr->glArea->throw_if_error();
		delete rect;
	}
	catch(const Gdk::GLError& gle)
	{
		std::cerr << "An error occured making the context current during unrealize" << std::endl;
		std::cerr << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
	}
}

void Renderer::resize(int width, int height){

}

bool Renderer::render(const Glib::RefPtr<Gdk::GLContext>&  context ){

	return true;
}
