#ifndef _H_SCENE
#define _H_SCENE

class Scene {
public:
	/* Constructor / Destructor */
	Scene();
	~Scene();

	/* Getters */
	static Scene* getActiveScene();

	/* Setters */
	static void setActiveScene(Scene* scene);

private:
	/* currently active state */
	static Scene* m_activeScene;

};

#endif