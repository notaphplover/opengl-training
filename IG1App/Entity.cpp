#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

MyPolygon::MyPolygon(GLuint numL, GLdouble rd) : Abs_Entity() {
	mMesh = Mesh::generaPoligono(numL, rd);
	_mColor = glm::dvec4(0.5);
}

MyPolygon::~MyPolygon()
{
	delete mMesh; mMesh = nullptr;
};

void MyPolygon::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(_mColor.r, _mColor.g, _mColor.b);
		glLineWidth(2);
		mMesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1);
	}
}

glm::dvec4 MyPolygon::getColor() {
	return _mColor;
}

void MyPolygon::setColor(glm::dvec4 color) {
	_mColor = color;
}

MySierpinski::MySierpinski(GLdouble rd, GLuint numP) : Abs_Entity() {
	mMesh = Mesh::generaSierpinski(rd, numP);
	_mColor = glm::dvec4(0.0, 0.0, 1.0, 1.0);
}

MySierpinski::~MySierpinski()
{
	delete mMesh; mMesh = nullptr;
};

void MySierpinski::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(_mColor));
		glPointSize(2);
		mMesh->render();
		glPointSize(0);
	}
}

glm::dvec4 MySierpinski::getColor() {
	return _mColor;
}

void MySierpinski::setColor(glm::dvec4 color) {
	_mColor = color;
}

MyTrianguloRGB::MyTrianguloRGB(GLdouble rd, GLdouble loopRadius, GLdouble deltaElapsed) {
	mMesh = Mesh::generaTrianguloRGB(rd);
	this->deltaElapsed = deltaElapsed;
	this->deltaIncrement = 0.1;
	this->loopRadius = loopRadius;
}

MyTrianguloRGB::~MyTrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
};

void MyTrianguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
	}
}

void MyTrianguloRGB::update() {
	const GLdouble selfAngle = - this->deltaElapsed;
	const GLdouble loopAngle = this->deltaElapsed;

	auto matrix = glm::translate(dmat4(1), dvec3(this->loopRadius * cos(loopAngle), this->loopRadius * sin(loopAngle), 0.0));
	matrix = glm::rotate(matrix, selfAngle, dvec3(0.0, 0.0, 1.0));

	this->setModelMat(matrix);

	this->deltaElapsed += this->deltaIncrement;
}

MyRectangleRGB::MyRectangleRGB(GLdouble w, GLdouble h) {
	mMesh = Mesh::generateRectangulo(w, h);
}

MyRectangleRGB::~MyRectangleRGB() {
	delete mMesh; mMesh = nullptr;
};
 
void MyRectangleRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);

		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}