#include "SceneLoader.hpp"

#include <sstream>

#include "Scenes/Scene_01/Scene_01.hpp"
#include "Scenes/Scene_02/Scene_02.hpp"
#include "Scenes/Scene_03/Scene_03.hpp"
#include "Scenes/Scene_04/Scene_04.hpp"
#include "Scenes/Scene_05/Scene_05.hpp"
#include "Scenes/Scene_06/Scene_06.hpp"

SceneLoader::SceneLoader(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
	m_Window = l_Window;
	m_Renderer = l_Renderer;
	m_ActiveScene = EMPTY;
	Logger::LogImportant(std::string("Creating the scenes"));

	m_Scenes[0] = new Scene_01();
	m_Scenes[1] = new Scene_02();
	m_Scenes[2] = new Scene_03();
	m_Scenes[3] = new Scene_04();
	m_Scenes[4] = new Scene_05();
	m_Scenes[5] = new Scene_06();

	bool status = true;
	for (int i = 0; i < AMOUNT_OF_SCENES; i++)
		if (!m_Scenes[i]) {
			std::stringstream tmp_ss;
			tmp_ss << i;
			std::string error;
			tmp_ss >> error;
			Logger::LogError(std::string("Could not create scene ") + error);
			status = false;
		}
	if (status) Logger::LogSucsess(std::string("All scenes are created"));
}

SceneLoader::~SceneLoader(void) {
	Logger::LogImportant(std::string("Deleting all scenes"));
	delete m_Scenes[0];
	delete m_Scenes[1];
	delete m_Scenes[2];
	delete m_Scenes[3];
	delete m_Scenes[4];
	delete m_Scenes[5];
	Logger::LogSucsess(std::string("All scenes deleted"));
}

void SceneLoader::SetScene(Scenes l_Scene) {
	if (l_Scene != EMPTY && l_Scene != END) {
		if(m_ActiveScene != EMPTY && m_ActiveScene != END)
			ClearScene();
		m_ActiveScene = l_Scene;
		m_Scenes[(int) l_Scene]->Init(m_Window, m_Renderer);
		Logger::LogSucsess(std::string("The scene loaded"));
	} else {
		Logger::LogError(std::string("Could not load the scene"));
	}
}

void SceneLoader::SetStartScene(void) {
	SetScene(START);
}

void SceneLoader::ClearScene(void) {
	if (m_ActiveScene != EMPTY && m_ActiveScene != END) {
		m_Scenes[m_ActiveScene]->Clear();
		Logger::LogSucsess("The scene cleared\n");
		m_ActiveScene = EMPTY;
	} else {
		Logger::LogWarning("Could not clear the scene\n");
	}
}

void SceneLoader::HandleEvent(SDL_Event *l_Event) {
	if (m_ActiveScene != EMPTY && m_ActiveScene != END) {
		m_Scenes[m_ActiveScene]->HandleEvent(l_Event);
	} else {
		Logger::LogError("Could not load the scene");
	}
}

void SceneLoader::Draw(void) {
	if (m_ActiveScene != EMPTY && m_ActiveScene != END) {
		m_Scenes[m_ActiveScene]->Draw();
	} else {
		Logger::LogError("Could not load the scene");
	}
}

void SceneLoader::Update(double l_Time) {
	if (m_ActiveScene != EMPTY && m_ActiveScene != END) {
		m_Scenes[m_ActiveScene]->Update(l_Time);
	} else {
		Logger::LogError("Could not load the scene");
	}
}

Sint16 SceneLoader::GetActiveScene(void) const { return m_ActiveScene; }

bool SceneLoader::GetStatusScene(Scenes l_Scene) const {
	if (m_ActiveScene != EMPTY && m_ActiveScene != END) {
		return m_Scenes[(int) l_Scene]->GetStatus();
	}
	Logger::LogError("Could not load the scene");
	return false;
}
