#include <Entry.hpp>

NYX::Application* NYX::CreateApp() {
	NYX::AppConfig config{};
	config.extent = { 800, 600 };
	config.title = "Nyx Sandbox";
	config.icon = "";
	config.version = { 1, 0, 0 };
	return new NYX::Application(config);
}