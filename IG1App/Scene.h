//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

#define TEXTURES_FOLDER "../Bmps/"
#define TEXTURE_FLOOR TEXTURES_FOLDER + "baldosaC.bmp"

//-------------------------------------------------------------------------

class Scene	
{
private:

	Texture* floor;

	MyTrianguloRGB* colorTriangle;

public:
	Scene() {
		colorTriangle = new MyTrianguloRGB(30, 200.0, 0.0);

		floor = new Texture();
		floor->load((std::string)TEXTURE_FLOOR);
	}
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;

	void update();
	
protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Texture*> gTextures;

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

