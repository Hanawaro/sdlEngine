#ifndef SCENE_05_HPP
#define SCENE_05_HPP

#include "../Scene.hpp"

#define SPEED		10	
#define ACCELERATOR	100

struct Rectangle {
	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	double x, y;
	int w, h;
};


class Scene_05 : public Scene {
public:
	Scene_05(void);
	~Scene_05(void);

	void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
	void Clear(void);

	void HandleEvent(SDL_Event* l_Event);
	void Draw(void);
	void Update(double l_Time);
private:

	double m_Speed = SPEED;
	double m_Accelerator = ACCELERATOR;

	Rectangle m_Rectangle;
};

#endif