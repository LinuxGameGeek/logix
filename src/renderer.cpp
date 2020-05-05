//#include <ui.hpp>
#include "./renderer.hpp"

Renderer::Renderer(Gtk::GLArea* glarea)
/*:glArea(glarea)*/{
	glArea = glarea;

	glArea->add_events(Gdk::BUTTON_MOTION_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON2_MOTION_MASK | Gdk::BUTTON3_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_HINT_MASK | Gdk::SCROLL_MASK);

 	glArea->signal_realize().connect(sigc::mem_fun(*this, &Renderer::realize));
 	glArea->signal_unrealize().connect(sigc::mem_fun(*this, &Renderer::unrealize), false);
	glArea->signal_render().connect(sigc::mem_fun(*this, &Renderer::render));
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
	std::clog<<epoxy_gl_version()<<"\n";
	std::clog<<epoxy_glsl_version()<<"\n";
	try{
		glArea->throw_if_error();
		std::clog<<glGetString(GL_VERSION)<<"\n";
		std::clog<<glGetString(GL_VENDOR)<<"\n";
		char path[] = "./src/res/shaders";
		shader_program = new Shader(path);
		shader_program->bind();
		//shader_program = Shader::create_shader_program(nullptr);
		//glUseProgram(shader_program);

		GLfloat pos[] = {
			-0.5f, -0.5f, -1,
			0.5f, -0.5f, -1,
			0.5f, 0.5f, -1,
			-0.5f, 0.5f, -1
		};
		GLuint ind[] = {
			0, 1, 2,
			2, 3, 0
		};


		vaptr = new VertexArray();

		//glGenVertexArrays(1, &vao);
		//glBindVertexArray(vao);

		vbptr = new VertexBuffer(pos, 4 * 3 * sizeof(GLfloat));

		vblptr = new VertexBufferLayout;
		vblptr->add(3, GL_FLOAT);
		//vblptr->add(3, GL_FLOAT);
		//vblptr->add(2, GL_FLOAT);
		vaptr->addBuffer(*vbptr, *vblptr);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

		ibptr = new IndexBuffer(ind, 6);
		//int location = epoxy_glGetUniformLocation(shader_program->get_program(), "u_Color");
		//glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
		//glm::vec4 data = {0.2f, 0.3f, 0.8f, 1.0f};
		shader_program->set_uniform4f ("u_Color", {0.2f, 0.3f, 0.8f, 1.0f});
		//viewport.proj = glm::ortho(-width/height/2, width/height/2, -height/width/2, height/width/2);
		//shader_program->set_uniform_mat4f ("mvp", viewport.proj);
	 	//glBindVertexArray(0);
 		//glUseProgram(0);
 		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}catch(const Gdk::GLError& gle){
		std::cerr << "An error occured making the context current during realize:" << std::endl;
		std::cerr << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
	}
}

void Renderer::unrealize(){
	glArea->make_current();
	delete vbptr;
	delete ibptr;
	delete vaptr;
	delete vblptr;
	delete shader_program;
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
	glClear(GL_COLOR_BUFFER_BIT);
	shader_program->bind();

	glBindVertexArray(vao);
	vaptr->bind();
	ibptr->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
	glUseProgram(0);
	return true;
}

bool Renderer::mouse_move(GdkEventMotion* event){
	glm::vec3 diff = mouse_translate(glm::vec3(mouse.x, mouse.y, 0.0)) - mouse_translate(glm::vec3(event->x, event->y, 0.0));
	std::clog<<diff.x<<" "<<diff.y<<"\n";
	if(mouse.button == 1){
		viewport.pos = viewport.pos - diff;
		std::clog<<viewport.pos .x<<" "<<viewport.pos.y<<" "<<viewport.pos.z<<"\n";
		glArea->queue_render();
	}
	mouse.x = event->x;
	mouse.y = event->y;
	return true;
}

bool Renderer::mouse_scroll(GdkEventScroll* event){
	if(event->direction == GDK_SCROLL_DOWN && viewport.zoom>1){
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
	//if(event->mouse.button == 1){	//left mouse button
	//
	//}
	return true;
}

bool Renderer::button_release(GdkEventButton* button){
	mouse.button = 0;
	return true;
}

void Renderer::update_view(){
	viewport.view = glm::translate(glm::mat4(1.0f), glm::vec3(viewport.pos.x, -viewport.pos.y, -viewport.pos.z));
	viewport.model = glm::translate(glm::mat4(1.0f), glm::vec3( 0, 0, 1.0));
	if(viewport.dim.x<viewport.dim.y){
		viewport.proj =  glm::ortho(-viewport.dim.x/viewport.dim.y/viewport.zoom, viewport.dim.x/viewport.dim.y/viewport.zoom, -1.0f/viewport.zoom, 1.0f/viewport.zoom);
	}else{
		viewport.proj =  glm::ortho(-1.0f/viewport.zoom, 1.0f/viewport.zoom, -viewport.dim.y/viewport.dim.x/viewport.zoom, viewport.dim.y/viewport.dim.x/viewport.zoom);
	}
	viewport.mvp = viewport.proj * viewport.view * viewport.model;

	shader_program->bind();
	shader_program->set_uniform_mat4f ("mvp", viewport.mvp);
}

glm::vec3 Renderer::mouse_translate(glm::vec3 pos){
	return glm::unProject(pos, viewport.model, viewport.proj, glm::vec4(0.0f, 0.0f, viewport.dim.x, viewport.dim.y));
}
