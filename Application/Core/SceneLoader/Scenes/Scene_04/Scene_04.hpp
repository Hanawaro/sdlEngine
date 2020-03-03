#ifndef SCENE_04_HPP
#define SCENE_04_HPP

#include <limits>
#include <sstream>
#include "../Scene.hpp"

#define PATH "Application/cfg/graph.cfg"

struct Graph {
	Uint16 AmoutOfPointer = UINT16_MAX;
	double a = DBL_MAX;
	double b = DBL_MAX;
	double left = DBL_MAX;
	double right = DBL_MAX;
	double* valeus = nullptr;
};

struct Sys {
	double left = DBL_MAX, right = DBL_MAX, up = INT16_MIN, down = INT16_MAX;
	double pixel_stepX = DBL_MAX, pixel_stepY = DBL_MAX;
	double point_stepX = DBL_MAX, point_stepY = DBL_MAX;
	double needToOx = DBL_MAX, needToOy = DBL_MAX;
	TextEntity* t_Left, * t_Right, * t_Up, * t_Down, * t_Center;
	TextEntity* t_MouseX, * t_MouseY;
};

struct MousePos {
	Sint16 posX = -10000,
		posY = -10000;
};
class Scene_04 : public Scene {
public:
	Scene_04(void);
	~Scene_04(void);

	void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
	void Clear(void);

	void HandleEvent(SDL_Event* l_Event);
	void Draw(void);
	void Update(double l_Time);
private:
	bool readCfg(const std::string& l_Path);
	int readLine(FILE* l_cfg, char* l_Buffer);
	bool parsLine(const char* l_Buffer);
	void tune(void);
	void stdDraw(void);

	const std::string transToDouble(double l_Value);
	const std::string transToInt(Uint16 l_Value);
private:
	Graph m_Graph;
	Sys m_Sys;
	MousePos m_Mouse;

	bool m_isConfig = false;
};

#endif