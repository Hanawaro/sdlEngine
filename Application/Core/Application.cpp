#include "Application.hpp"

Application::Application(const std::string& l_Title, Uint16 l_Width, Uint16 l_Height, Sint16 l_PosX, Sint16 l_PosY, Uint32 l_Flag) {
	init(l_Title.c_str(), l_Width, l_Height, l_PosX, l_PosY, l_Flag);
}

Application::~Application(void) {
	destroy();
}

bool Application::isRunning(void) const { return m_isRunning; }

void Application::HandleEvent(void) {
	while (SDL_PollEvent(&m_Event)) {
		switch (m_Event.type) {
		case SDL_QUIT:
			m_isRunning = false;
			m_SceneLoader->ClearScene();
			break;
		case SDL_KEYDOWN:
			switch (m_Event.key.keysym.sym) {
			case SDLK_LEFT:
				m_SceneLoader->SetScene((SceneLoader::Scenes)( m_SceneLoader->GetActiveScene() - 1));
				break;
			case SDLK_RIGHT:
				m_SceneLoader->SetScene((SceneLoader::Scenes)(m_SceneLoader->GetActiveScene() + 1));
				break;
			case SDLK_F5:
				m_SceneLoader->SetScene((SceneLoader::Scenes)m_SceneLoader->GetActiveScene());
				break;
			case SDLK_1:
				m_SceneLoader->SetScene((SceneLoader::Scenes) 0 );
				break;
			case SDLK_2:
				m_SceneLoader->SetScene((SceneLoader::Scenes) 1 );
				break;
			case SDLK_3:
				m_SceneLoader->SetScene((SceneLoader::Scenes) 2 );
				break;
			case SDLK_4:
				m_SceneLoader->SetScene((SceneLoader::Scenes) 3 );
				break;
			case SDLK_5:
				m_SceneLoader->SetScene((SceneLoader::Scenes) 4);
				break;
			case SDLK_6:
				m_SceneLoader->SetScene((SceneLoader::Scenes) 5 );
				break;
			}
		default:
			m_SceneLoader->HandleEvent(&m_Event);
			break;
		}			
	}
}

void Application::Update(void) {
	// Updating
	m_Timer.tick();
	m_Accumulator += m_Timer.delta;
	//std::cout << "Delta is " << m_Timer.delta << " and limit is " << m_Limit*1000 << std::endl;
	if (m_SceneLoader->GetStatusScene((SceneLoader::Scenes)m_SceneLoader->GetActiveScene())) {
		while (m_Accumulator > m_Limit*1000) {
			m_Accumulator -= m_Limit * 1000;
			m_SceneLoader->Update(m_Limit * 1000);
		}
	} else {
		// Manage scenes
	}
}

void Application::Render(void) {
	m_SceneLoader->Draw();
}

void Application::init(const char* l_Title, Uint16 l_Width, Uint16 l_Height, Sint16 l_PosX, Sint16 l_PosY, Uint32 l_Flag) {
	// Logger init
	Logger::Init(Logger::IMPORTANT);
	Logger::LogImportant(std::string("Creating the application class"));
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		Logger::LogError(std::string("SDL could not initialize! SDL_Error: ") + SDL_GetError());
		Logger::Destroy();
		return;
	}
	Logger::LogMessage(std::string("SDL initialized"));
	// Init IMG
	int tmp_imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(tmp_imgFlags) & tmp_imgFlags)) {
		Logger::LogError(std::string("SDL_image could not initialuze! SDL_image: ") + IMG_GetError());
		SDL_Quit();
		Logger::LogImportant(std::string("SDL quited"));
		Logger::LogSucsess(std::string("Memory cleared"));
		Logger::Destroy();
		return;
	}
	Logger::LogMessage(std::string("IMG initialized"));
	// Init TTF
	if (TTF_Init() < 0) {
		Logger::LogError(std::string("TTF could not initialize! TTF_Error: ") + TTF_GetError());
		IMG_Quit();
		Logger::LogImportant(std::string("IMG quited"));
		SDL_Quit();
		Logger::LogImportant(std::string("SDL quited"));
		Logger::LogSucsess(std::string("Memory cleared"));
		Logger::Destroy();
		return;
	}
	Logger::LogMessage(std::string("SDL initialized"));
	// Initialize window
	m_Window = new WindowEntity();
	m_Window->width = l_Width;
	m_Window->height = l_Height;
	if (!(m_Window->window = SDL_CreateWindow(l_Title, l_PosX, l_PosY, l_Width, l_Height, l_Flag))) {
		Logger::LogError(std::string("Window could not be created! SDL_Error: ") + SDL_GetError());
		delete m_Window;
		Logger::LogImportant(std::string("Window deleted"));
		TTF_Quit();
		Logger::LogImportant(std::string("TTF quited"));
		IMG_Quit();
		Logger::LogImportant(std::string("IMG quited"));
		SDL_Quit();
		Logger::LogImportant(std::string("SDL quited"));
		Logger::LogSucsess(std::string("Memory cleared"));
		Logger::Destroy();
		return;
	}
	Logger::LogMessage(std::string("Window initialized"));
	// Initialize renderer
	if (!(m_Renderer = SDL_CreateRenderer(m_Window->window, -1, NULL))) {
		Logger::LogError(std::string("Renderer could not be created! SDL_Error: ") + SDL_GetError());
		SDL_DestroyWindow(m_Window->window);
		delete m_Window;
		Logger::LogImportant(std::string("Window deleted"));
		TTF_Quit();
		Logger::LogImportant(std::string("TTF quited"));
		IMG_Quit();
		Logger::LogImportant(std::string("IMG quited"));
		SDL_Quit();
		Logger::LogImportant(std::string("SDL quited"));
		Logger::LogSucsess(std::string("Memory cleared"));
		Logger::Destroy();
		return;
	}
	Logger::LogMessage(std::string("Renderer initialized"));
	// Initialize scene loader
	m_SceneLoader = new SceneLoader(m_Window, m_Renderer);
	Logger::LogMessage(std::string("Scene loader initialized"));
	// Start game loop and load start scene
	m_isRunning = true;
	m_initFlag = true;
	m_SceneLoader->SetStartScene();

	Logger::LogSucsess(std::string("Application class created\n"));
}

void Application::destroy(void) {
	Logger::LogImportant(std::string("Deleting application class"));
	if (m_initFlag) {
		// Delete scene loader
		delete m_SceneLoader;
		Logger::LogMessage(std::string("Scene loader deleted"));
		// Destroy renderer
		SDL_DestroyRenderer(m_Renderer);
		Logger::LogMessage(std::string("Renderer deleted"));
		// Delete and destroy window
		SDL_DestroyWindow(m_Window->window);
		delete m_Window;
		Logger::LogMessage(std::string("Window deleted"));
		// Ttf quit
		TTF_Quit();
		Logger::LogMessage(std::string("TTF quited"));
		// Img quit
		IMG_Quit();
		Logger::LogMessage(std::string("IMG quited"));
		// Sdl quit
		SDL_Quit();
		Logger::LogMessage(std::string("SDL quited"));
		Logger::LogSucsess(std::string("Application class deleted"));
		// Destroy logger
		Logger::Destroy();
	}
}

