//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Abs_Entity  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };
	
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix
	
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 

	void setTexture(Texture* tex) { mTexture = tex; }

	Texture* mTexture = nullptr;


	
};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class MyPolygon : public Abs_Entity
{
public:
	explicit MyPolygon(GLuint numL, GLdouble rd);
	~MyPolygon();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	glm::dvec4 getColor();
	void setColor(glm::dvec4 color);
	
private:
	glm::dvec4 _mColor;
};

class MySierpinski : public Abs_Entity
{
public:
	explicit MySierpinski(GLdouble rd, GLuint numL);
	~MySierpinski();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	glm::dvec4 getColor();
	void setColor(glm::dvec4 color);

private:
	glm::dvec4 _mColor;
};

class MyTrianguloRGB : public Abs_Entity
{

private:
	GLdouble deltaElapsed;
	GLdouble deltaIncrement;
	GLdouble loopRadius;

public:
	explicit MyTrianguloRGB(GLdouble rd, GLdouble loopRadius, GLdouble deltaElapsed);
	~MyTrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void update();
};

class MyRectangleRGB : public Abs_Entity
{
public:
	explicit MyRectangleRGB(GLdouble w, GLdouble h);
	~MyRectangleRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


#endif //_H_Entities_H_