#ifndef SCENE_LOADER_HPP
#define SCENE_LOADER_HPP

#include <SDL.h>

#include <Logger.hpp>

#include "../Entity/Window/Window.hpp"
#include "Scenes/Scene.hpp"

#define AMOUNT_OF_SCENES 6

class SceneLoader {
public:
	enum Scenes {
		EMPTY = -1,
		START = 0,
		SCENE_01 = 0,
		SCEME_02,
		SCENE_03,
		SCENE_04,
		SCENE_05,
		SCENE_06,
		END
	};
public:
	SceneLoader(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
	~SceneLoader(void);

	void SetScene(Scenes l_Scene);
	void SetStartScene(void);

	void ClearScene(void);

	void HandleEvent(SDL_Event *l_Event);
	void Draw(void);
	void Update(double l_Time);

	Sint16 GetActiveScene(void) const;
	bool GetStatusScene(Scenes l_Scene) const;
private:
	WindowEntity* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	Scene* m_Scenes[AMOUNT_OF_SCENES];
	Scenes m_ActiveScene = EMPTY;
};

#endif