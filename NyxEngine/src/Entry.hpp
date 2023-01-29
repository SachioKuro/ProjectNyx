#pragma once

#include "Application.hpp"

extern NYX::Application* NYX::CreateApp();

int main() {
	auto app = NYX::CreateApp();
	app->Run();
	delete app;
	return 0;
}