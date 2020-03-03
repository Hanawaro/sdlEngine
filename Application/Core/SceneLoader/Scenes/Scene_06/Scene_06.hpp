#ifndef SCENE_06_HPP
#define SCENE_06_HPP

#include "../Scene.hpp"

struct Circle;

class Scene_06 : public Scene {
public:
	Scene_06(void);
	~Scene_06(void);

	void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
	void Clear(void);

	void HandleEvent(SDL_Event* l_Event);
	void Draw(void);
	void Update(double l_Time);
private:
	Circle* m_Circles[5];

	double m_LeftSys[2][2];
	double m_LeftSys_back[2][2];
			 
	double m_RightSys[2][2];
	double m_RightSys_back[2][2];

	// for calculate
	double radius = 0,
		   distance = 0;
	double LeftX = 0, LeftY = 0,
		   RightX = 0, RightY = 0;
	double opredelitel = 0;
	double RightSpeedX = 0, RightSpeedY = 0,
		   LeftSpeedX = 0, LeftSpeedY = 0;
};

#endif