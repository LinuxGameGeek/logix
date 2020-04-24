#include "./ui.hpp"
#include <iostream>

int main(int argc, char* argv[]){
	std::cout<<".\n";
	Ui window(argc, argv);
	return window.app->run(*window.window);
}
