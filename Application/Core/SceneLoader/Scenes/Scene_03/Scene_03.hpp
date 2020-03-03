#ifndef SCENE_03_HPP
#define SCENE_03_HPP

#include "../Scene.hpp"

class Scene_03 : public Scene {
public:
	Scene_03(void);
	~Scene_03(void);

	void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
	void Clear(void);

	void HandleEvent(SDL_Event* l_Event);
	void Draw(void);
	void Update(double l_Time);
private:
};

#endif