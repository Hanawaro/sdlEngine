#include "Scene_05.hpp"

Scene_05::Scene_05(void) {}

Scene_05::~Scene_05(void) {
	Clear();
}

void Scene_05::Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
	m_Window = l_Window;
	m_Renderer = l_Renderer;

	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);

	m_Rectangle.w = 200;
	m_Rectangle.h = 100;

	m_Rectangle.x = 15;
	m_Rectangle.y = m_Window->height / 2 - m_Rectangle.h / 2;

	m_Status = true;
}

void Scene_05::Clear(void) {
	m_Speed = SPEED;
	m_Accelerator = ACCELERATOR;
	m_Status = false;
}

void Scene_05::HandleEvent(SDL_Event* l_Event) {
}

void Scene_05::Draw(void) {
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);
	if ((int)m_Rectangle.x < m_Window->width)
		boxRGBA(
			m_Renderer,
			(int)m_Rectangle.x, (int)m_Rectangle.y,
			(int)(m_Rectangle.x + m_Rectangle.w), (int)(m_Rectangle.y + m_Rectangle.h),
			m_Rectangle.r, m_Rectangle.g, m_Rectangle.b, 255
		);
	SDL_RenderPresent(m_Renderer);
}

void Scene_05::Update(double l_Time) {
	if ((int)m_Rectangle.x < m_Window->width) {
		m_Rectangle.x = m_Rectangle.x + m_Speed * l_Time / 1000 + m_Accelerator * l_Time / 1000 * l_Time / 1000 * 0.5;
		m_Speed = m_Speed + m_Accelerator * l_Time / 1000;
	}
}
