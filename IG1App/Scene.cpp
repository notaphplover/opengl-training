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

	delete floor; floor = nullptr;

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

	/*
	 * Velas sends kisses and hugs from the past <3
	 * Velas also approves this
	 *
	 * GL_REPLACE Utilizar exclusivamente la textura: C = T(s,t)
     * GL_MODULATE. Modular ambos colores: C = C * T(s,t)
     * GL_ADD. Sumar ambos colores: C = C + T(s,t)
	 */
	floor->bind(GL_MODULATE); // Modulate mixes color and texture.

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	

	floor->unbind();
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


