#include "GLApplication.h"

#include <iostream>

using namespace std;
using namespace p3d;

GLApplication::~GLApplication() {
}

GLApplication::GLApplication() {

  _lightPosition.set(0,0,0);

  _meshGL.initTetrahedron();

  _angle=0.0;





}




/** ********************************************************************** **/
void GLApplication::initialize() {
  // appelée 1 seule fois à l'initialisation du contexte
  // => initialisations OpenGL
  glClearColor(1,1,1,1);

//  glLineWidth(2.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);



  _shader.attribute("position",0);
  _shader.attribute("color",1);
  _shader.read("openGL3D");

  glEnable(GL_DEPTH_TEST); // chaque fragment source subit le test du depth buffer
    glDepthFunc(GL_LESS);  // le test passe si depth(source) < depth(destination)
    glClearDepth(1); // valeur d'initialisation du depth destination de tous les pixels lors d'un glClear


  _meshGL.initDraw();
}

void GLApplication::resize(int width,int height) {
  // appelée à chaque dimensionnement du widget OpenGL
  // (inclus l'ouverture de la fenêtre)
  // => réglages liés à la taille de la fenêtre
  glViewport(0,0,width,height);
  // ...
}

void GLApplication::update() {
  // appelée toutes les 20ms (60Hz)
  // => mettre à jour les données de l'application
  // avant l'affichage de la prochaine image (animation)
  // ...

  _angle+=2;


  _transform.setTranslation(0,0,-15);
  _transform.rotate(_angle,Vector3(1,0.2,0));
  _transform.translate(0,0,15);
}

void GLApplication::draw() {
  // appelée après chaque update
  // => tracer toute l'image

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // affecte le color buffer et le depth buffer avec les valeurs d'initialisation



  glUseProgram(_shader.id());

  _meshGL.draw();
  glUseProgram(0);

  snapshot(); // capture opengl window if requested
}

/** ********************************************************************** **/
/** i = button number, s = button text
 */
void GLApplication::leftPanel(int i,const std::string &s) {
  cout << "GLApplication : button clicked " << i << " " << s << endl;
  /*
  switch (i) {
    case 0:menu0();break;
    case 1:menu1();break;
  }
  */
}

/** *********************************************************** **/




