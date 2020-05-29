//#include <ui.hpp>
#include "./renderer.hpp"

Renderer::Renderer(Gtk::GLArea* glarea)
/*:glArea(glarea)*/{
	glArea = glarea;

	glArea->add_events(Gdk::BUTTON_MOTION_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON2_MOTION_MASK | Gdk::BUTTON3_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_HINT_MASK | Gdk::SCROLL_MASK);

 	glArea->signal_realize().connect(sigc::mem_fun(*this, &Renderer::realize));
 	glArea->signal_unrealize().connect(sigc::mem_fun(*this, &Renderer::unrealize), false);
	glArea->signal_render().connect(sigc::mem_fun(*this, &Renderer::render), false);
	glArea->signal_resize().connect(sigc::mem_fun(*this, &Renderer::resize));
	glArea->signal_motion_notify_event().connect(sigc::mem_fun(*this, &Renderer::mouse_move));
	glArea->signal_scroll_event().connect(sigc::mem_fun(*this, &Renderer::mouse_scroll));
	glArea->signal_button_press_event().connect(sigc::mem_fun(*this, &Renderer::button_press));
	glArea->signal_button_release_event().connect(sigc::mem_fun(*this, &Renderer::button_release));
}

void Renderer::realize(){
	std::clog<<"realize"<<std::endl;
	//glArea->set_required_version(4, 5);
	glArea->make_current();
	glArea->set_auto_render(true);
	std::clog<<"make current"<<std::endl;
	//std::clog<<epoxy_gl_version()<<"\n";
	//std::clog<<epoxy_glsl_version()<<"\n";


	glArea->make_current();
	std::cout<<glGetString(GL_VERSION)<<std::endl;
	std::cout<<"realize\n";
	try{
		glArea->throw_if_error();
		std::clog<<glGetString(GL_VERSION)<<"\n";
		std::clog<<glGetString(GL_VENDOR)<<"\n";

		bgrid = new Grid(glm::vec3(-8.0, 0.0, -1.0), glm::vec3(8.0, 0.0, -1.0), &viewport.mvp, 0.025f);
		rgrid = new Grid(glm::vec3(-8.0, 0.0, -1.0), glm::vec3(8.0, 0.0, -1.0), &viewport.mvp, 1.0f, glm::vec4(1.0f, 0.5f, 0.3f, 0.6f));

		sizei = glm::vec2(0.4, 0.4);
		posi = glm::vec2(1.0, 0.0);
		colorp = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
		nodelist.mvp = &viewport.mvp;
		nodelist.create(types::AND, posi);
		//nodelist.create(types::AND, glm::vec2(3.0, 0.0));
		//rect = new Rectangle(&posi, &sizei, &viewport.mvp, &colorp);
		//crc = new Circle(&posi, &sizei.x, &viewport.mvp, &colorp);
	}catch(const Gdk::GLError& gle){
		std::cerr << "An error occured making the context current during realize:" << std::endl;
		std::cerr << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
	}
}

void Renderer::unrealize(){
	glArea->make_current();

	delete rgrid;
	delete bgrid;
	nodelist.clear();
	//delete rect;
	//delete crc;
	try
	{
		glArea->throw_if_error();
	}
	catch(const Gdk::GLError& gle)
	{
		std::cerr << "An error occured making the context current during unrealize" << std::endl;
		std::cerr << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
	}
}

void Renderer::resize(int width, int height){
	viewport.dim.x = width;
	viewport.dim.y = height;
}

bool Renderer::render(const Glib::RefPtr<Gdk::GLContext>&  context ){
	std::clog<<"render\n";
	update_view();
	//glArea->attach_buffers();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT);


	//bgrid->draw();
	//rgrid->draw();
	nodelist.draw();
	//rect->draw();
	//crc->draw();
	return true;
}

bool Renderer::mouse_move(GdkEventMotion* event){
	glm::vec3 diff = mouse_translate(glm::vec3(mouse.x, mouse.y, 0.0)) - mouse_translate(glm::vec3(event->x, event->y, 0.0));
	std::clog<<diff.x<<" "<<diff.y<<"\n";
	if(mouse.button == 1){
		viewport.pos = viewport.pos - diff;
		std::clog<<viewport.pos .x<<" "<<viewport.pos.y<<" "<<viewport.pos.z<<"\n";
		//glArea->queue_draw();
		//glArea->queue_draw();
		glArea->queue_render();
		//glArea->signal_render();
	}
	mouse.x = event->x;
	mouse.y = event->y;
	return true;
}

bool Renderer::mouse_scroll(GdkEventScroll* event){
	//nodelist.create(types::AND, glm::vec2(4.0, 3.0));
	if(event->direction == GDK_SCROLL_DOWN && viewport.zoom>0.2){
		viewport.zoom = viewport.zoom - 0.1;
	}else if(event->direction == GDK_SCROLL_UP && viewport.zoom<10){
		viewport.zoom = viewport.zoom + 0.1;
	}
	glArea->queue_render();
	std::clog<<viewport.zoom<<"\n";
	return true;
}


bool Renderer::button_press(GdkEventButton* event){
	std::clog<<event->button<<"\n";
	mouse.button = event->button;
	mouse.x = event->x;
	mouse.y = event->y;
	if(event->button == 3){	//left mouse button
		//glm::vec3 var = mouse_translate(glm::vec3(event->x, event->y, 0.0));
		//std::clog<<var.x<<" "<<var.y<<"\n";
		//nodelist.create(types::AND, glm::vec2(4.0, 3.0));
	}
	return true;
}

bool Renderer::button_release(GdkEventButton* button){
	mouse.button = 0;
	return true;
}

void Renderer::update_view(){
	std::clog<<"update view\n";
	viewport.view = glm::translate(glm::mat4(1.0f), glm::vec3(viewport.pos.x, -viewport.pos.y, -viewport.pos.z));
	viewport.model = glm::translate(glm::mat4(1.0f), glm::vec3( 0, 0, 1.0));
	if(viewport.dim.x<viewport.dim.y){
		viewport.proj =  glm::ortho(-viewport.dim.x/viewport.dim.y/viewport.zoom, viewport.dim.x/viewport.dim.y/viewport.zoom, -1.0f/viewport.zoom, 1.0f/viewport.zoom);
	}else{
		viewport.proj =  glm::ortho(-1.0f/viewport.zoom, 1.0f/viewport.zoom, -viewport.dim.y/viewport.dim.x/viewport.zoom, viewport.dim.y/viewport.dim.x/viewport.zoom);
	}
	viewport.mvp = viewport.proj * viewport.view;

}

glm::vec3 Renderer::mouse_translate(glm::vec3 pos){
	return glm::unProject(pos, viewport.model, viewport.proj, glm::vec4(0.0f, 0.0f, viewport.dim.x, viewport.dim.y));
}
