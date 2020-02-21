//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>
#include "Texture.h"

#include <String.h>
#include <set>

//-------------------------------------------------------------------------

class Scene	
{
private:

	MyTrianguloRGB* colorTriangle;
	std::vector<Texture*> gTextures;
	const std::string BASE_PATH_TO_BMPS = "../Bmps/";
	const std::vector<std::string> TEXTURES = { "baldosaC.bmp", "baldosaF.bmp", "baldosaP.bmp", "container.bmp", "grass.bmp",
		"papelC.bmp", "", "papelE.bmp", "windowC.bmp", "windowV.bmp", "Zelda.bmp" };

public:
	Scene() {
		colorTriangle = new MyTrianguloRGB(30, 200.0, 0.0);
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

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

