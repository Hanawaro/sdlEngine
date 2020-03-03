#include "Scene_02.hpp"

Scene_02::Scene_02(void) {}

Scene_02::~Scene_02(void) {
	Clear();
}

void Scene_02::Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
	m_Window = l_Window;
	m_Renderer = l_Renderer;

	SDL_SetRenderDrawColor(m_Renderer, 255, 219, 223, 255);
	SDL_RenderClear(m_Renderer);
	// sea
	boxRGBA(
		m_Renderer,
		0, 270,
		m_Window->width,
		m_Window->height,
		21, 96, 189, 255
	);
	// body
	filledTrigonRGBA(
		m_Renderer, 
		270, 330,
		270, 360,
		250, 360,
		237, 237, 237, 255
	);
	boxRGBA (
		m_Renderer,
		270, 300,
		550, 360,
		237, 237, 237, 255
		);
	boxRGBA(
		m_Renderer,
		400, 280,
		490, 299,
		240, 240, 240, 255
	);
	boxRGBA(
		m_Renderer,
		300, 325,
		450, 326,
		0, 0, 0, 255
	);
	// manifold
	boxRGBA(
		m_Renderer,
		399, 299,
		375, 240,
		8, 3, 3, 255
	);
	// Bottom
	boxRGBA(
		m_Renderer,
		200, 350,
		585, 390,
		0, 54, 153, 255
	);
	boxRGBA(
		m_Renderer,
		490, 325,
		585, 389,
		0, 54, 153, 255
	);
	filledTrigonRGBA(
		m_Renderer,
		490, 325,
		490, 389,
		435, 389,
		0, 54, 153, 255
	);
	filledTrigonRGBA(
		m_Renderer,
		585, 390,
		585, 325,
		640, 325,
		0, 54, 153, 255
	);
	// header
	boxRGBA(
		m_Renderer,
		445, 160,
		448, 279,
		0, 0, 0, 255
	);
	lineRGBA(
		m_Renderer,
		445, 160,
		200, 350,
		0, 0, 0, 255
	);
	lineRGBA(
		m_Renderer,
		448, 160,
		640, 325,
		0, 0, 0, 255
	);
	// windows
	filledCircleRGBA(
		m_Renderer,
		510, 360,
		12,
		71, 136, 255, 255
	);
	filledCircleRGBA(
		m_Renderer,
		560, 360,
		12,
		71, 136, 255, 255
	);

	m_Status = true;
}

void Scene_02::Clear(void) {
	m_Status = false;
}

void Scene_02::HandleEvent(SDL_Event* l_Event) {
}

void Scene_02::Draw(void) {
	SDL_RenderPresent(m_Renderer);
}

void Scene_02::Update(double l_Time) {
}
