#include "Scene.h"
//-------------------------------------------------------------------------

void Scene::update()
{
	/*for (auto u : gObjects) {
		u->update();
	}*/
}

void Scene::init()
{
	glEnable(GL_DEPTH_TEST);
	setGL();
	if (mId == 0) {

	}
	



}
void Scene::setState(int id)
{
	if (id != mId) {
		resetGL();
		free();
		mId = id;
		init();
	}

}
//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	
}
//-------------------------------------------------------------------------
void Scene::setGL()
{

	// OpenGL basic setting
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glClearColor(0.6, 0.7, 0.8, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);


}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);

}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const
{
	

}
