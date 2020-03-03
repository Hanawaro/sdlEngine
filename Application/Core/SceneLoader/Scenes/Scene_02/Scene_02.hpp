#ifndef SCENE_02_HPP
#define SCENE_02_HPP

#include "../Scene.hpp"

class Scene_02 : public Scene {
public:
	Scene_02(void);
	~Scene_02(void);

	void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
	void Clear(void);

	void HandleEvent(SDL_Event* l_Event);
	void Draw(void);
	void Update(double l_Time);
private:
};

#endif