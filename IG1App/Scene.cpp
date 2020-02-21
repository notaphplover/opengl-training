#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <time.h>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	srand(time(NULL));

	// allocate memory and load resources

    // Lights
    // Textures

    // Graphics objects (entities) of the scene

	// Transforms

	int i = 0;
	for (std::string pathToText : TEXTURES) {
		gTextures[i]->load(BASE_PATH_TO_BMPS + pathToText); // el segundo argumento inica la opacidad de la textura, por defecto está a 255(si no le pones nada)
		i++;
	}

	// Rectánglo de colores
	gObjects.push_back(new MyRectangleRGB(1000, 500));
	// Triangulo de colorines
	gObjects.push_back(colorTriangle);
	// Triangulo Sierpinski
	gObjects.push_back(new MySierpinski(200, 5000));
	// Triángulo normal
	gObjects.push_back(new MyPolygon(3, 200));
	// Círculo
	gObjects.push_back(new MyPolygon(2000, 200));
	// Ejes
	gObjects.push_back(new EjesRGB(400.0));
	
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}

	for (Texture* tex : gTextures) {
		delete tex; tex = nullptr;
	}

}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test
	glEnable(GL_TEXTURE_2D);

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 
	glDisable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}

void Scene::update() {
	this->colorTriangle->update();
}

//-------------------------------------------------------------------------


