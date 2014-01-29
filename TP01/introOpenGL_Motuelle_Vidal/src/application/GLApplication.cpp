#include "GLApplication.h"

#include <iostream>

using namespace std;

GLApplication::~GLApplication() {
}

GLApplication::GLApplication() {

    //initStrip(200,-0.8,0.8,-0.8,0.8);
    initRing(20,0.2,0.6);

}

void GLApplication::initStrip(int nbSlice,float xmin,float xmax,float ymin,float ymax){
    float interv = (xmax - xmin) / nbSlice ;
    float intervColor = 1 / (float)nbSlice ;
    float courant = xmin;
    for(int i=0;i<=nbSlice;++i) {
        _trianglePosition.push_back(courant);
        _trianglePosition.push_back(ymin);
        _trianglePosition.push_back(0.0);
        _triangleColor.push_back(0);_triangleColor.push_back(intervColor*i);_triangleColor.push_back(0);_triangleColor.push_back(1);
        _trianglePosition.push_back(courant);
        _trianglePosition.push_back(ymax);
        _trianglePosition.push_back(0.0);
        _triangleColor.push_back(0);_triangleColor.push_back(0);_triangleColor.push_back(1-(intervColor*i));_triangleColor.push_back(1);
        courant += interv ;
    }


}

void GLApplication::initRing(int nbSlice,float r0,float r1){
   float theta_max = 2 * 3.14159;
   float interv_theta = theta_max / nbSlice ;
   float theta_courant = 0;
   float intervColor = 1 / (float)nbSlice ;

   for(int i=0;i<=nbSlice;++i) {
       _trianglePosition.push_back(r0 * cos(theta_courant));
       _trianglePosition.push_back(r0 * sin(theta_courant));
       _trianglePosition.push_back(0.0);
       _triangleColor.push_back(0);_triangleColor.push_back(intervColor*i);_triangleColor.push_back(0);_triangleColor.push_back(1);
       _trianglePosition.push_back(r1 * cos(theta_courant));
       _trianglePosition.push_back(r1 * sin(theta_courant));
       _trianglePosition.push_back(0.0);
       _triangleColor.push_back(0);_triangleColor.push_back(0);_triangleColor.push_back(1-(intervColor*i));_triangleColor.push_back(1);
       theta_courant += interv_theta ;
   }



}



/** ********************************************************************** **/
void GLApplication::initialize() {
  // appelée 1 seule fois à l'initialisation du contexte
  // => initialisations OpenGL
  glClearColor(1,1,1,1);

  glLineWidth(2.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


  _shader0=initProgram("simple");


  initTriangleBuffer();
  initTriangleVAO();
  initTexture();


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


}

void GLApplication::draw() {
  // appelée après chaque update
  // => tracer toute l'image
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(_shader0);
  glBindVertexArray(_triangleVAO);

  glDrawArrays(GL_TRIANGLE_STRIP,0,_trianglePosition.size()/3);

  glBindVertexArray(0);
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
GLuint GLApplication::initProgram(const std::string &filename) {
  GLuint program;

  string vertexSource=p3d::readTextFile(filename+".vert");
  string fragmentSource=p3d::readTextFile(filename+".frag");

  program=glCreateProgram();
  GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
  glAttachShader(program,vertexShader);
  glAttachShader(program,fragmentShader);

  const char *source;
  source=vertexSource.c_str();
  glShaderSource(vertexShader,1,&source,NULL);
  source=fragmentSource.c_str();
  glShaderSource(fragmentShader,1,&source,NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  glBindAttribLocation(program,0,"position");



  glLinkProgram(program);
  return program;
}


void GLApplication::initTexture() {
    QImage img;
    img.load("../media/lagoon.jpg");
    img=img.convertToFormat(QImage::Format_ARGB32);

    glGenTextures(1,&_textureId);
    glBindTexture(GL_TEXTURE_2D,_textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width(),img.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.bits());

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}


void GLApplication::initTriangleBuffer() {

  glGenBuffers(1,&_trianglePositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
  glBufferData(GL_ARRAY_BUFFER,_trianglePosition.size()*sizeof(float),_trianglePosition.data(),GL_STATIC_DRAW);

  glGenBuffers(1,&_triangleColorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
  glBufferData(GL_ARRAY_BUFFER,_triangleColor.size()*sizeof(float),_triangleColor.data(),GL_STATIC_DRAW);

  glGenBuffers(1,&_elementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,_elementData.size()*sizeof(unsigned int),_elementData.data(),GL_STATIC_DRAW);

}


void GLApplication::initTriangleVAO() {
  glGenVertexArrays(1,&_triangleVAO);
  glBindVertexArray(_triangleVAO);

  glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

  glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
  glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);


  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);


  glBindVertexArray(0);
}



