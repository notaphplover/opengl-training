#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

#define TRIANGLE_POINTS 3
#define RECTANGLE_POINTS 4

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 

    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    if (!vTexCoords.empty()) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
    }
    
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

glm::dvec4* Mesh::generateRandomColor() {

    double randomRed = (float)rand() / (float)RAND_MAX;
    double randomGreen = (float)rand() / (float)RAND_MAX;
    double randomBlue = (float)rand() / (float)RAND_MAX;

    return new glm::dvec4(randomRed, randomGreen, randomBlue, 1.0);
}

Mesh* Mesh::generatePolygonBase(GLuint numL, GLuint numP, int mPrimitive, GLdouble rd) {
    double offSet = M_PI / 2;
    double angle = 0.0;
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = mPrimitive;
    mesh->mNumVertices = numP;
    mesh->vVertices.reserve(numP);

    for (double i = 0; i < numL; ++i) {
        angle = offSet + i * 2.0 * M_PI / numL;
        mesh->vVertices.emplace_back(rd * cos(angle), rd * sin(angle), 0.0);
    }
    return mesh;
}


Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {
    return Mesh::generatePolygonBase(numL, numL, GL_LINE_LOOP, rd);
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
    
    int randomPoint = 0;
    Mesh* mesh = Mesh::generatePolygonBase(TRIANGLE_POINTS, numP, GL_POINTS, rd);

    for (int i = TRIANGLE_POINTS; i < numP; ++i) {
        
        mesh->vVertices.emplace_back(
            (mesh->vVertices[i - 1].x + mesh->vVertices[randomPoint].x) / 2,
            (mesh->vVertices[i - 1].y + mesh->vVertices[randomPoint].y) / 2,
            (mesh->vVertices[i - 1].z + mesh->vVertices[randomPoint].z) / 2
        );
        randomPoint = rand() % TRIANGLE_POINTS;
    }

    return mesh;
}

Mesh* Mesh::generaTrianguloRGB(GLdouble rd) {
    Mesh* triangle = Mesh::generatePolygonBase(TRIANGLE_POINTS, TRIANGLE_POINTS, GL_TRIANGLES, rd);
    triangle->vColors.reserve(TRIANGLE_POINTS);

    for (int i = 0; i < TRIANGLE_POINTS; ++i) {
        triangle->vColors.push_back(*Mesh::generateRandomColor());
    }
    return triangle;
}

Mesh* Mesh::generateRectangulo(GLdouble w, GLdouble h) {
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = RECTANGLE_POINTS;
    mesh->vVertices.reserve(RECTANGLE_POINTS);

    GLdouble halfW = w / 2;
    GLdouble halfH = h / 2;
    GLdouble minusHalfW = -halfW;
    GLdouble minusHalfH = -halfH;

    // V0
    mesh->vVertices.emplace_back(minusHalfW, halfH, -100);
    // V1
    mesh->vVertices.emplace_back(minusHalfW, minusHalfH, -100);
    // V2
    mesh->vVertices.emplace_back(halfW, halfH, -100);
    // V3
    mesh->vVertices.emplace_back(halfW, minusHalfH, -100);
    

    glm::dvec4* colorNW = Mesh::generateRandomColor();
    glm::dvec4* colorNE = Mesh::generateRandomColor();
    glm::dvec4* colorSW = Mesh::generateRandomColor();
    glm::dvec4* colorSE = Mesh::generateRandomColor();

    // V0
    mesh->vColors.push_back(*colorNW);
    // V1
    mesh->vColors.push_back(*colorSW);
    // V2
    mesh->vColors.push_back(*colorNE);
    // V3
    mesh->vColors.push_back(*colorSE);
    

    return mesh;
}