#include "Application.hpp"

namespace NYX {
	static bool s_isRunning = true;

	void Application::Init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			NYX_ERROR("SDL_Init failed: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}

		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0) {
			NYX_ERROR("IMG_Init failed: %s", IMG_GetError());
			exit(EXIT_FAILURE);
		}

		if (TTF_Init() < 0) {
			NYX_ERROR("TTF_Init failed: %s", TTF_GetError());
			exit(EXIT_FAILURE);
		}

		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) < 0 ||
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512))
		{
			NYX_ERROR("Mix_Init or Mix_OpenAudio failed: %s", Mix_GetError());
			exit(EXIT_FAILURE);
		}

		auto windowFlags = 
			SDL_WINDOW_SHOWN | 
			SDL_WINDOW_RESIZABLE | 
			SDL_WINDOW_ALLOW_HIGHDPI;
		m_window = SDL_CreateWindow(
			m_appConfig.title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_appConfig.extent.width,
			m_appConfig.extent.height,
			windowFlags
		);

		if (!m_window) {
			NYX_ERROR("SDL_CreateWindow failed: %s", SDL_GetError());
			return;
		}

		auto rendererFlags =
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC;
		m_renderer = SDL_CreateRenderer(
			m_window,
			-1,
			rendererFlags
		);

		if (!m_renderer) {
			NYX_ERROR("SDL_CreateRenderer failed: %s", SDL_GetError());
			return;
		}

		m_eventDispatcher = new EventDispatcher();
		Locator::SetService<EventDispatcherService>(m_eventDispatcher);

		m_eventDispatcher->RegisterCallback(EventType::SystemEvent, Application::OnExit);

		m_inputs = new Inputs();
		m_inputs->InitInputs(m_window);
	}

	void Application::Run() {
		auto scene = new ECS::Scene(m_renderer);
		scene->start();
		while (s_isRunning) {
			m_inputs->DispatchInputEvents();

			if (m_inputs->IsMouseButtonDown(SDL_BUTTON_LEFT)) {
				NYX_DEBUG_P("Mouse button left is down\n");
				auto mousePosition = m_inputs->GetMousePosition();
				NYX_DEBUG_P("%s\n", mousePosition.ToString().c_str());
			}

			if (m_inputs->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
				s_isRunning = false;
			}

			if (m_inputs->IsKeyDown(SDL_SCANCODE_F)) {
				SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}

			if (m_inputs->IsKeyDown(SDL_SCANCODE_A)) {
				NYX_DEBUG_P("Hello Universe!")
			}

			SDL_RenderClear(m_renderer);
			scene->update(0.1);
			SDL_RenderPresent(m_renderer);
		}
		NYX_DELETE(scene);

		SDL_Quit();
	}

	void Application::OnExit(Event* event) {
		s_isRunning = false;
		event->SetHandled();
	}
}