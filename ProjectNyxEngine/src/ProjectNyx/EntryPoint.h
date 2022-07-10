#pragma once

#ifdef NYX_PLATFORM_WINDOWS

extern Nyx::Application* Nyx::CreateApplication();

int main(int argc, char** argv) {
	auto app = Nyx::CreateApplication();
	app->Run();
	delete app;
}

#endif