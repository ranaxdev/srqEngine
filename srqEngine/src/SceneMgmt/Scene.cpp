#include "Scene.h"

/* Init active scene to null*/
Scene* Scene::m_activeScene = nullptr;

/* Constructor/Destructor temporarily blank */
Scene::Scene() {}
Scene::~Scene() {}

/* Set a scene as active to render it's data */
void Scene::setActiveScene(Scene* scene) {
	m_activeScene = scene;
}

/* Return currently active scene for general querying */
Scene* Scene::getActiveScene(){
	return m_activeScene;
}