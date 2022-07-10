#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <ProjectNyx.h>

class Sandbox : public Nyx::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

Nyx::Application* Nyx::CreateApplication() {
	return new Sandbox();
}

