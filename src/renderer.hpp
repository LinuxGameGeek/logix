#ifndef RENDERER_H
#define RENDERER_H

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
};

#endif //