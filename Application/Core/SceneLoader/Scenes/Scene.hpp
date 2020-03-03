#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

#include <Logger.hpp>

#include "../../Entity/Window/Window.hpp"
#include "../../Entity/Texture/Texture.hpp"
#include "../../Entity/Text/Text.hpp"

class Scene {
public:
	virtual void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) = 0;
	virtual void Clear(void) = 0;

	virtual void HandleEvent(SDL_Event *l_Event) = 0;
	virtual void Draw(void) = 0;
	virtual void Update(double l_Time) = 0;

	bool GetStatus(void) { return m_Status; }
protected:
	WindowEntity* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	bool m_Status = false;
};

#endif