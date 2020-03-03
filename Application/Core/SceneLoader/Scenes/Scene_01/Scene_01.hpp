#ifndef SCENE_01_HPP
#define SCENE_01_HPP

#include "../Scene.hpp"

class Scene_01 : public Scene {
public:
	Scene_01(void);
	~Scene_01(void);
	
	void Init(WindowEntity* l_Window, SDL_Renderer* l_Renderer);
	void Clear(void);

	void HandleEvent(SDL_Event* l_Event);
	void Draw(void);
	void Update(double l_Time);
private:
	TextureEntity* m_Image = nullptr;
};

#endif