

//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

//#include <GL/freeglut.h>
//#include <glm.hpp>
#include "PxPhysicsAPI.h"
#include "core.hpp"
#include "Render/Camera.h"
//#include "Entity.h"

#include <vector>
//#include "Texture.h"

//-------------------------------------------------------------------------

class Scene
{
public:
	Scene() :mId(0) {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
	virtual void update();
	void init();
	void setState(int id);
	void render(Camera const& cam) const;


protected:
	void free();
	void setGL();
	void resetGL();
	int mId;
	
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_
