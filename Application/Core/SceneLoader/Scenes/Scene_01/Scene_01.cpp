#include "Scene_01.hpp"

Scene_01::Scene_01(void) {}

Scene_01::~Scene_01(void) {
	Clear();
}

void Scene_01::Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
	m_Window = l_Window;
	m_Renderer = l_Renderer;

	m_Image = new TextureEntity(std::string("Application/Source/Scene_01/image.png"), m_Renderer, { 255, 255, 255 }, 200, 200);

	SDL_SetRenderDrawColor(m_Renderer, 133, 150, 176, 255);
	SDL_RenderClear(m_Renderer);
	m_Image->Draw(m_Renderer, m_Window->width - m_Image->GetDstRect()->w, 0);

	m_Status = true;
}

void Scene_01::Clear(void) {
	delete m_Image;
	m_Status = false;
}

void Scene_01::HandleEvent(SDL_Event *l_Event) {
}

void Scene_01::Draw(void) {
	SDL_RenderPresent(m_Renderer);
}

void Scene_01::Update(double l_Time) {
}
