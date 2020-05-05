#ifndef UI_H
#define UI_H

/*
 This class is responsible for the Ui of the application.
*/
#include "./renderer.hpp"
#include <gtkmm-3.0/gtkmm.h>

class Ui{
	public:
		Ui(int argc, char* argv[]);
		~Ui();
		Gtk::Window* window;
		Gtk::Paned* paned;
		Renderer* viewport;
		Gtk::GLArea* glArea;
    	Glib::RefPtr<Gtk::Application> app;
	private:
		Glib::RefPtr<Gtk::Builder> builder;
};
#endif //UI_H