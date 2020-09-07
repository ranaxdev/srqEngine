#include "Scene.h"

/* No active scene initially */
Scene* Scene::active_scene = nullptr;

Scene::Scene(){
	
}

/* Return the currently active scene as reference */
Scene* Scene::getActiveScene() { return active_scene; }

/* Set a scene to be active */
void Scene::setActiveScene(Scene* scene) { Scene::active_scene = scene;  }
