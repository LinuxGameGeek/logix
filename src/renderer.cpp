//#include <ui.hpp>
#include "./renderer.hpp"

Renderer::Renderer(Gtk::GLArea* glarea)
:glArea(glarea){
 	glArea->signal_realize().connect(sigc::mem_fun(*this, &Renderer::realize));
 	glArea->signal_unrealize().connect(sigc::mem_fun(*this, &Renderer::unrealize), false);
	glArea->signal_render().connect(sigc::mem_fun(*this, &Renderer::render));
	glArea->signal_resize ().connect(sigc::mem_fun(*this, &Renderer::resize));
}

void Renderer::realize(){
	std::cout<<glGetString(GL_VERSION)<<std::endl;
	glArea->make_current();
	std::cout<<"realize\n";
	try{
		glArea->throw_if_error();

		shader_program = Shader::create_shader_program(nullptr);
		glUseProgram(shader_program);

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

		int location = epoxy_glGetUniformLocation(shader_program, "u_Color");
		glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);


	 	glBindVertexArray(0);
 		glUseProgram(0);
 		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}catch(const Gdk::GLError& gle){
		std::cerr << "An error occured making the context current during realize:" << std::endl;
		std::cerr << gle.domain() << "-" << gle.code() << "-" << gle.what() << std::endl;
	}
}

void Renderer::unrealize(){
	delete vbptr;
	delete ibptr;
	delete vaptr;
	delete vblptr;
	glArea->make_current();
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

}

bool Renderer::render(const Glib::RefPtr<Gdk::GLContext>&  context ){
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_program);

	//glBindVertexArray(vao);
	vaptr->bind();
	ibptr->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
	glUseProgram(0);
	return true;
}
