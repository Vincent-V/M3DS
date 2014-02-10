#include "BasicMesh.h"
#include "ObjLoader.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace p3d;

BasicMesh::~BasicMesh() {
  glDeleteBuffers(1,&_attributeBuffer);
  glDeleteBuffers(1,&_elementBuffer);
}


BasicMesh::BasicMesh() {
  _attributeBuffer=0;
  _elementBuffer=0;
}



void BasicMesh::updateBuffer() {

}




void BasicMesh::initTetrahedron() {
  std::vector<float> position={
    -10,0,-10, // 0
    10,0,-10,  // 1
    0,10,-20,  // 2

    -10,0,-10, // 0 = 3
    0,10,-20, // 2 = 4
    0,-10,-20,  // 3 = 5

    -10,0,-10, // 0 = 6
    10,0,-10,  // 1 = 7
    0,-10,-20,  // 3 = 8

    10,0,-10,  // 1 = 9
    0,10,-20,  // 2 = 10
    0,-10,-20,  // 3 = 11
  };

  std::vector<float> color={
    1,0,0,
    1,0,0,
    1,0,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,0,1,
    0,0,1,
    0,0,1,
    0,1,1,
    0,1,1,
    0,1,1
  };

  _element={
    0,1,2,3,4,5,6,7,8,9,10,11
  };



  _attribute.clear();
  for(unsigned int i=0;i<position.size()/3;++i) {

    _attribute.push_back(position[i*3+0]*0.09); // *0.09 pour être visible entre [-0.9,0.9]
    _attribute.push_back(position[i*3+1]*0.09);
    _attribute.push_back(position[i*3+2]*0.09+1.0);



    _attribute.push_back(color[i*3+0]);
    _attribute.push_back(color[i*3+1]);
    _attribute.push_back(color[i*3+2]);

  }
}


void BasicMesh::initObj(const ObjLoader &obj) {
  _attribute.clear();
  _element.clear();

  // initialisation de _attribute :
  // - obj.nbVertex() = nombre de sommets
  // - obj.position(i) = position du i-ème sommet de type Vector3 => obj.position(i).x() donne le x, .y() donne le y, etc
  // - obj.normal(i) = normale du i-ème sommet de type Vector3
  for(unsigned int i=0;i<obj.nbVertex();++i) {

    // TODO

  }

  // initialisation de _element (i.e. indices des triangles pour glDrawElements) :
  // - obj.nbFace() = nombre de triangles
  // - obj.indexVertex(i,j) = donne l'indice du j-ième sommet (j=0,1 ou 2) du i-ème triangle
  for(unsigned int i=0;i<obj.nbFace();i++) {

    // TODO

  }
}

void BasicMesh::initBuffer() {
  glGenBuffers(1,&_attributeBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_attributeBuffer);
  glBufferData(GL_ARRAY_BUFFER,_attribute.size()*sizeof(float),_attribute.data(),GL_STATIC_DRAW);


  glGenBuffers(1,&_elementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,_element.size()*sizeof(unsigned int),_element.data(),GL_STATIC_DRAW);
}

void BasicMesh::initVAO() {

  glGenVertexArrays(1,&_vao);
  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER,_attributeBuffer);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,0);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(void*)(3*sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);

  glBindVertexArray(0);
}

void BasicMesh::initDraw() {
  initBuffer();
  initVAO();
}


void BasicMesh::draw() {
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES,_element.size(),GL_UNSIGNED_INT,(const GLvoid *)(0*sizeof(GLuint)));
  glBindVertexArray(0);
}

