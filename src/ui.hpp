#ifndef UI_H
#define UI_H

#include <gtkmm-3.0/gtkmm.h>

class Ui{
	public:
		Ui(int argc, char* argv[]);
		Gtk::Window* window;
    	Gtk::GLArea* glArea;
    	Glib::RefPtr<Gtk::Application> app;
	private:
		Glib::RefPtr<Gtk::Builder> builder;
};
#endif //UI_H