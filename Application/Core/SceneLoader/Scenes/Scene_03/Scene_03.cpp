#include "Scene_03.hpp"

Scene_03::Scene_03(void) {}

Scene_03::~Scene_03(void) {
	Clear();
}

void Scene_03::Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
	m_Window = l_Window;
	m_Renderer = l_Renderer;

	SDL_SetRenderDrawColor(m_Renderer, 18, 18, 18, 18);
	SDL_RenderClear(m_Renderer);

	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

	for (int i = 0; i * 50 < m_Window->width; i++) {
		for (int j = 0; j * 50 < m_Window->height; j++) {
			int starX = rand() % ((i + 1) * 50 - 1) + i * 50;
			int starY = rand() % ((j + 1) * 50 - 1) + j * 50;
			boxRGBA(
				m_Renderer,
				starX, starY,
				starX + 1, starY + 1,
				rand() % 56 + 200, rand() % 56 + 200, rand() % 56 + 200, 255
			);
		}
	}

	m_Status = true;
}

void Scene_03::Clear(void) {
	m_Status = false;
}

void Scene_03::HandleEvent(SDL_Event* l_Event) {
}

void Scene_03::Draw(void) {
	SDL_RenderPresent(m_Renderer);
}

void Scene_03::Update(double l_Time) {
}
