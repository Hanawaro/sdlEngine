#include "Scene_06.hpp"

#define AMOUNT_OF_CIRCLES	5
#define SPEED_START_LIMIT	200

struct Circle {
	double x = 0, y = 0;
	Uint16 r = 0;
	struct Color {
		Uint16 r = 0, g = 0, b = 0;
	} cl;

	double speedX = 0;
	double speedY = 0;

	void Draw(SDL_Renderer* m_Renderer) {
		filledCircleRGBA(
		m_Renderer,
			(int) x, (int) y,
			r,
			cl.r, cl.g, cl.b, 255
		);
	}
};

Scene_06::Scene_06(void) {}

Scene_06::~Scene_06(void) {
	Clear();
}

void Scene_06::Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer) {
	m_Window = l_Window;
	m_Renderer = l_Renderer;

	for (int i = 0; i < AMOUNT_OF_CIRCLES; i++) {
		m_Circles[i] = new Circle;
		m_Circles[i]->r = 50;
		m_Circles[i]->speedX = rand() % (SPEED_START_LIMIT * 2 + 1) - SPEED_START_LIMIT;
		m_Circles[i]->speedY = ( (rand() % 2 - 1) ? 1 : -1 ) * sqrt(SPEED_START_LIMIT * SPEED_START_LIMIT - m_Circles[i]->speedX * m_Circles[i]->speedX);
		//std::cout << ((rand() % 2 - 1) ? 1 : -1) << std::endl;
	}
	double tmp_SpeedY = 0;
	// First circle
	m_Circles[0]->x = m_Window->width / 4;
	m_Circles[0]->y = m_Window->height / 4;

	// Second circle
	m_Circles[1]->x = m_Window->width / 4;
	m_Circles[1]->y = m_Window->height / 4 * 3;

	// Third cirlce
	m_Circles[2]->x = m_Window->width / 4 * 3;
	m_Circles[2]->y = m_Window->height / 4;

	// Fourth circle
	m_Circles[3]->x = m_Window->width / 4 * 3;
	m_Circles[3]->y = m_Window->height / 4 * 3;

	// Fifth
	m_Circles[4]->x = m_Window->width / 2;
	m_Circles[4]->y = m_Window->height / 2;

	m_Status = true;
}

void Scene_06::Clear(void) {
	for (int i = 0; i < AMOUNT_OF_CIRCLES; i++)
		delete m_Circles[i];
	m_Status = false;
}

void Scene_06::HandleEvent(SDL_Event* l_Event) {
}

void Scene_06::Draw(void) {
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_Renderer);

	for (int i = 0; i < AMOUNT_OF_CIRCLES; i++) {
		m_Circles[i]->Draw(m_Renderer);
	}

	SDL_RenderPresent(m_Renderer);
}

void Scene_06::Update(double l_Time) {
	bool intersection[AMOUNT_OF_CIRCLES] = { false };

	for (int i = 0; i < AMOUNT_OF_CIRCLES; i++) {
		if (m_Circles[i]->x - m_Circles[i]->r < 0) {
			m_Circles[i]->x = m_Circles[i]->r;
			m_Circles[i]->speedX *= -1;
		}
		if (m_Circles[i]->x + m_Circles[i]->r > m_Window->width) {
			m_Circles[i]->x = m_Window->width - m_Circles[i]->r;
			m_Circles[i]->speedX *= -1;
		}
		if (m_Circles[i]->y - m_Circles[i]->r < 0) {
			m_Circles[i]->y = m_Circles[i]->r;
			m_Circles[i]->speedY *= -1;
		}
		if (m_Circles[i]->y + m_Circles[i]->r > m_Window->height) {
			m_Circles[i]->y = m_Window->height - m_Circles[i]->r;
			m_Circles[i]->speedY *= -1;
		}

		m_Circles[i]->x += l_Time / 1000 * m_Circles[i]->speedX;
		m_Circles[i]->y += l_Time / 1000 * m_Circles[i]->speedY;
	}

	for (int i = 0; i < AMOUNT_OF_CIRCLES; i++) {
		if (!intersection[i]) {
			for (int j = i + 1; j < AMOUNT_OF_CIRCLES; j++) {
				radius = (m_Circles[i]->r + m_Circles[j]->r) * (m_Circles[i]->r + m_Circles[j]->r);
				distance = (m_Circles[i]->x - m_Circles[j]->x) * (m_Circles[i]->x - m_Circles[j]->x) + (m_Circles[i]->y - m_Circles[j]->y) * (m_Circles[i]->y - m_Circles[j]->y);
				if ( radius >= distance ) {

					double norm = sqrt((m_Circles[i]->x - m_Circles[j]->x) * (m_Circles[i]->x - m_Circles[j]->x) + (m_Circles[i]->y - m_Circles[j]->y) * (m_Circles[i]->y - m_Circles[j]->y));

					m_RightSys[0][0] = (m_Circles[j]->x - m_Circles[i]->x) / norm;	// x of Ox
					m_RightSys[1][0] = (m_Circles[j]->y - m_Circles[i]->y) / norm;	// y of Ox
					m_RightSys[0][1] = -m_RightSys[1][0];	// x of Oy
					m_RightSys[1][1] = m_RightSys[0][0];	// y of Oy

					m_LeftSys[0][0] = -m_RightSys[0][0];	// x of Ox
					m_LeftSys[1][0] = -m_RightSys[1][0];	// y of Ox
					m_LeftSys[0][1] = m_RightSys[0][1];	// x of Oy
					m_LeftSys[1][1] = m_RightSys[1][1];		// y of Oy

					// Determinand of right sys
					opredelitel = m_RightSys[0][0] * m_RightSys[1][1] - m_RightSys[0][1] * m_RightSys[1][0];
					m_RightSys_back[0][0] = m_RightSys[1][1] / opredelitel;
					m_RightSys_back[0][1] = - m_RightSys[0][1] / opredelitel;
					m_RightSys_back[1][0] = - m_RightSys[1][0] / opredelitel;
					m_RightSys_back[1][1] = m_RightSys[0][0] / opredelitel;

					// Determinand of left sys
					opredelitel = m_LeftSys[0][0] * m_LeftSys[1][1] - m_LeftSys[0][1] * m_LeftSys[1][0];
					m_LeftSys_back[0][0] = m_LeftSys[1][1] / opredelitel;
					m_LeftSys_back[0][1] = -m_LeftSys[0][1] / opredelitel;
					m_LeftSys_back[1][0] = -m_LeftSys[1][0] / opredelitel;
					m_LeftSys_back[1][1] = m_LeftSys[0][0] / opredelitel;
					
					RightSpeedX = - abs(m_LeftSys_back[0][0] * m_Circles[j]->speedX + m_LeftSys_back[0][1] * m_Circles[j]->speedY);
					RightSpeedY = m_RightSys_back[1][0] * m_Circles[i]->speedX + m_RightSys_back[1][1] * m_Circles[i]->speedY;

					LeftSpeedX = - abs(m_RightSys_back[0][0] * m_Circles[i]->speedX + m_RightSys_back[0][1] * m_Circles[i]->speedY);
					LeftSpeedY = m_LeftSys_back[1][0] * m_Circles[j]->speedX + m_LeftSys_back[1][1] * m_Circles[j]->speedY;

					m_Circles[i]->speedX = m_RightSys[0][0] * RightSpeedX + m_RightSys[0][1] * RightSpeedY;
					m_Circles[i]->speedY = m_RightSys[1][0] * RightSpeedX + m_RightSys[1][1] * RightSpeedY;

					m_Circles[j]->speedX = m_LeftSys[0][0] * LeftSpeedX + m_LeftSys[0][1] * LeftSpeedY;
					m_Circles[j]->speedY = m_LeftSys[1][0] * LeftSpeedX + m_LeftSys[1][1] * LeftSpeedY;

					double step = - ( ceil( ((m_Circles[i]->r + m_Circles[j]->r - sqrt(distance) ) / 2 ) ) );

					m_Circles[i]->x += m_RightSys[0][0] * step + m_RightSys[0][1] * 0;
					m_Circles[i]->y += m_RightSys[1][0] * step + m_RightSys[1][1] * 0;

					m_Circles[j]->x += m_LeftSys[0][0] * step + m_LeftSys[0][1] * 0;
					m_Circles[j]->y += m_LeftSys[1][0] * step + m_LeftSys[1][1] * 0;

					int colorR = rand() % 256;
					int colorG = rand() % 256;
					int colorB = rand() % 256;

					m_Circles[j]->cl.r = colorR;
					m_Circles[j]->cl.g = colorG;
					m_Circles[j]->cl.b = colorB;

					m_Circles[i]->cl.r = colorR;
					m_Circles[i]->cl.g = colorG;
					m_Circles[i]->cl.b = colorB;
				}
			}
		}
	}
}
