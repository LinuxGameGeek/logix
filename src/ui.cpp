#include <iostream>

#include "./ui.hpp"

Ui::Ui (int argc, char* argv[]){
	app = Gtk::Application::create(argc, argv);
	builder = Gtk::Builder::create();
	try{
		builder->add_from_file("./src/res/glade/logix.glade");
	}catch(const Glib::FileError& ex){
      std::cerr << "FileError: " << ex.what() << std::endl;
      Gtk::Main::quit();
	}catch(const Glib::MarkupError& ex){
      std::cerr << "MarkupError: " << ex.what() << std::endl;
      Gtk::Main::quit();
	}catch(const Gtk::BuilderError& ex){
      std::cerr << "BuilderError: " << ex.what() << std::endl;
      Gtk::Main::quit();
	}
	builder->get_widget("mainWindow", window);
	builder->get_widget("glArea", glArea);
	viewport = new Renderer(glArea);
}

Ui::~Ui(){
	delete viewport;
}

Gtk::Window* window = nullptr;
Gtk::GLArea* glArea = nullptr;
Renderer* viewport = nullptr;
