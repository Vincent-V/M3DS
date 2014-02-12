#include "GLPrimitive.h"

#include "Tools.h"
#include "VertexArray.h"
#include "GLRender.h"

#include <cmath>

/*!
*
* @file
*
* @brief
* @author F. Aubert
*
*/

using namespace std;

namespace p3d {
static bool _isPrimitiveInit=false;

void initGLPrimitive() {
  if (!_isPrimitiveInit) {
    initGLRender();
    initSquare();
    initCylinder(true,20);
    initSphere(20,20);
    initCube();
    initCone(true,30);
    initTorus(10,40);
    initSegment();
    _isPrimitiveInit=true;
  }
}




static VertexArray _square(GL_TRIANGLE_STRIP);
static VertexArray _cylinder(GL_TRIANGLE_STRIP);
static VertexArray _cylinderCap(GL_TRIANGLE_FAN);
static VertexArray _cube(GL_TRIANGLE_STRIP);
static VertexArray _sphere(GL_TRIANGLE_STRIP);
static VertexArray _cone(GL_TRIANGLES);
static VertexArray _coneCap(GL_TRIANGLE_FAN);
static VertexArray _torus(GL_TRIANGLE_STRIP);
static GLuint _segmentBuffer;
static VertexArray *_gridPoint=0;
static VertexArray *_pointsPoint=0;
static VertexArray *_lineStripPoint=0;
static VertexArray *_linesPoint=0;



static std::vector<float> _vertex;
static std::vector<float> _normal;
static std::vector<float> _texCoord;
Vector3 _currentNormal;
Vector2 _currentTexCoord;

void resetAttrib() {
  _vertex.clear();_normal.clear();_texCoord.clear();
}

void normalAttrib(const p3d::Vector3 &n) {
  _currentNormal=n;
  _currentNormal.normalize();
}

void normalAttrib(double x,double y,double z) {
  normalAttrib(Vector3(x,y,z));
}

void texCoordAttrib(const p3d::Vector2 &t) {
  _currentTexCoord=t;
}

void texCoordAttrib(double s,double t) {
  texCoordAttrib(Vector2(s,t));
}

void vertexAttrib(const p3d::Vector3 &v) {
  _vertex.push_back(v.x());_vertex.push_back(v.y());_vertex.push_back(v.z());
  _normal.push_back(_currentNormal.x());_normal.push_back(_currentNormal.y());_normal.push_back(_currentNormal.z());
  _texCoord.push_back(_currentTexCoord.x());_texCoord.push_back(_currentTexCoord.y());
}

void addCommonAttrib(VertexArray *vao) {
  vao->add("position",_vertex,3,0);
  vao->add("normal",_normal,3,1);
  vao->add("texCoord",_texCoord,2,2);
}

void vertexAttrib(double x,double y,double z) {
  vertexAttrib(Vector3(x,y,z));
}

void initSquare() {
  std::vector<float> vertex{
    -1.0,1.0,0.0,
    -1.0,-1.0,0.0,
    1.0,1.0,0.0,
    1.0,-1.0,0.0
  };
  std::vector<float> normal{
    0.0,0.0,1.0,
    0.0,0.0,1.0,
    0.0,0.0,1.0,
    0.0,0.0,1.0
  };
  std::vector<float> texCoord{
    0.0,1.0,
    0.0,0.0,
    1.0,1.0,
    1.0,0.0
  };

  _square.add("position",vertex,3,0);
  _square.add("normal",normal,3,1);
  _square.add("texCoord",texCoord,2,2);
}

void initConeCap(int nbSlice) {
  resetAttrib();
  double theta=0.0;
  double stepTheta=2.0*M_PI/nbSlice;
  double x,y;
  normalAttrib(Vector3(0,0,1));
  texCoordAttrib(Vector2(0.5,0.5));
  vertexAttrib(Vector3(0,0,1));
  for(int i=0;i<nbSlice;i++) {
    x=cos(theta);y=sin(theta);
    texCoordAttrib(Vector2(x/2.0+0.5,y/2.0+0.5));
    vertexAttrib(Vector3(x,y,1.0));
    theta+=stepTheta;
  }
  texCoordAttrib(1.0,0.5);
  vertexAttrib(1,0,1);
  addCommonAttrib(&_coneCap);
}

void initCone(bool cap,int nbSlice) {
  resetAttrib();
  double step=2.0*M_PI/nbSlice;
  double theta=0.0;
  double x,y;
  for(int i=0;i<nbSlice+1;i++) {
    x=cos(theta);
    y=sin(theta);
    normalAttrib(Vector3(x/sqrt(2),y/sqrt(2),-1.0/sqrt(2)));
    texCoordAttrib(Vector2(theta/2.0/M_PI,0));
    vertexAttrib(Vector3(x,y,1.0));

    theta+=step/2.0;
    x=cos(theta);
    y=sin(theta);
    normalAttrib(Vector3(x/sqrt(2),y/sqrt(2),-1.0/sqrt(2)));
    texCoordAttrib(Vector2(theta/2.0/M_PI,1));
    vertexAttrib(Vector3(0,0,0));

    theta+=step/2.0;
    x=cos(theta);
    y=sin(theta);
    normalAttrib(Vector3(x/sqrt(2),y/sqrt(2),-1.0/sqrt(2)));
    texCoordAttrib(Vector2(theta/2.0/M_PI,0));
    vertexAttrib(Vector3(x,y,1.0));

  }
  addCommonAttrib(&_cone);
  if (cap) {
    initConeCap(nbSlice);
  }

}

void initTorus(int nbSlice,int nbStack) {
  double rg=1.0;
  double rp=0.2;
  double theta=0.0; // angle for external radius
  double phi=0.0;   // angle for internal radius
  double stepTheta=2.0*M_PI/(double)nbStack;
  double stepPhi=2.0*M_PI/(double)nbSlice;

  double nx0,ny0,nz0,nx1,ny1,nz1;
  double x0,y0,z0;
  double x1,y1,z1;
  resetAttrib();
  for(int i=0;i<nbStack+1;i++) {
    phi=0.0;
    for(int j=0;j<nbSlice+1;j++) {
      if (j==nbSlice) phi=0.0; // lazy-junction
      nx1=cos(phi);
      ny1=0.0;
      nz1=sin(phi);
      x1=rp*nx1+(rg-rp);
      y1=0.0;
      z1=rp*nz1;

      nx0=(nx1*cos(theta)-ny1*sin(theta));
      ny0=(nx1*sin(theta)+ny1*cos(theta));
      nz0=nz1;

      x0=(x1*cos(theta)-y1*sin(theta));
      y0=(x1*sin(theta)+y1*cos(theta));
      z0=z1;
      normalAttrib(nx0,ny0,nz0);
      texCoordAttrib(theta/(2.0*M_PI),phi/(2.0*M_PI));
      vertexAttrib(x0,y0,z0);
      phi+=stepPhi;
    }
    theta+=stepTheta;
  }
  addCommonAttrib(&_torus);
  vector<int> elem;
  elem.clear();
  int i;
  for(i=0;i<nbStack;i++) {
    for(int j=0;j<nbSlice+1;j++) {
      elem.push_back(i*(nbSlice+1)+j);
      elem.push_back(i*(nbSlice+1)+nbSlice+1+j);
    }
  }
  _torus.element(elem);
  _torus.restart((nbSlice+1)*2);

}





void initCylinderCap(int nbSlice) {
  resetAttrib();
  double theta=0.0;
  double stepTheta=2.0*M_PI/nbSlice;
  double x,y,z;
  for(int cap=0;cap<2;cap++) {
    theta=0.0;
    if (cap==0) z=1.0; else {z=0.0;stepTheta=-stepTheta;}
    normalAttrib(Vector3(0,0,z*2-1));
    texCoordAttrib(Vector2(0.5,0.5));
    vertexAttrib(Vector3(0,0,z));
    for(int i=0;i<nbSlice;i++) {
      x=cos(theta);y=sin(theta);
      texCoordAttrib(Vector2(x/2.0+0.5,y/2.0+0.5));
      vertexAttrib(Vector3(x,y,z));
      theta+=stepTheta;
    }
    texCoordAttrib(1.0,0.5);
    vertexAttrib(1,0,z);
  }
  addCommonAttrib(&_cylinderCap);
  _cylinderCap.restart(nbSlice+2);
}

void initCylinder(bool cap,int nbSlice) {
  resetAttrib();
  double step=2.0*M_PI/nbSlice;
  double theta=0.0;
  double x,y;
  for(int i=0;i<nbSlice;i++) {
    x=cos(theta);
    y=sin(theta);
    normalAttrib(Vector3(x,y,0.0));
    texCoordAttrib(Vector2(theta/2.0/M_PI,0));
    vertexAttrib(Vector3(x,y,1.0));

    texCoordAttrib(Vector2(theta/2.0/M_PI,1.0));
    vertexAttrib(Vector3(x,y,0.0));

    theta+=step;
  }
  normalAttrib(Vector3(1.0,0.0,0.0));
  texCoordAttrib(Vector2(1.0,0.0));
  vertexAttrib(Vector3(1.0,0.0,1.0));

  texCoordAttrib(Vector2(1.0,1.0));
  vertexAttrib(Vector3(1.0,0.0,0.0));
  addCommonAttrib(&_cylinder);
  if (cap) {
    initCylinderCap(nbSlice);
  }
}


void initSphere(int nbSlice,int nbStack) {
  resetAttrib();
  double stepTheta=2.0*M_PI/nbSlice;
  double stepPhi=M_PI/nbStack;
  double phi=-M_PI/2.0;
  for(int i=0;i<nbStack+1;i++) {
    double theta=0.0;
    double x,y,z;
    z=sin(phi);
    for(int j=0;j<nbSlice+1;j++) {
      x=cos(theta)*cos(phi);
      y=sin(theta)*cos(phi);
      normalAttrib(Vector3(x,y,z));
      texCoordAttrib(Vector2(theta/2.0/M_PI,phi/M_PI+0.5));
      vertexAttrib(Vector3(x,y,z));
      theta+=stepTheta;
    }
    phi+=stepPhi;
  }
  vector<int> elem;
  elem.clear();
  for(int i=0;i<nbStack;i++) {
    for(int j=0;j<nbSlice+1;j++) {
      elem.push_back(i*(nbSlice+1)+j);
      elem.push_back((i+1)*(nbSlice+1)+j);
    }
  }
  _sphere.element(elem);
  addCommonAttrib(&_sphere);
  _sphere.restart((nbSlice+1)*2);
}

void initCube() {
  std::vector<float> vertex{
    -1.0,1.0,1.0, // face z=1
    -1.0,-1.0,1.0,
    1.0,1.0,1.0,
    1.0,-1.0,1.0,
    -1.0,-1.0,-1.0, // face z=-1
    -1.0,1.0,-1.0,
    1.0,-1.0,-1.0,
    1.0,1.0,-1.0,
    1.0,-1.0,1.0, // face x=1
    1.0,-1.0,-1.0,
    1.0,1.0,1.0,
    1.0,1.0,-1.0,
    -1.0,-1.0,-1.0, // face x=-1
    -1.0,-1.0,1.0,
    -1.0,1.0,-1.0,
    -1.0,1.0,1.0,
    -1.0,1.0,1.0, // face y=1
    -1.0,1.0,-1.0,
    1.0,1.0,1.0,
    1.0,1.0,-1.0,
    -1.0,-1.0,-1.0, // face y=-1
    -1.0,-1.0,1.0,
    1.0,-1.0,-1.0,
    1.0,-1.0,1.0
  };
  std::vector<float> normal {
    0,0,1, // face z=1
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,-1, // face z=-1
    0,0,-1,
    0,0,-1,
    0,0,-1,
    1,0,0, // face x=1
    1,0,0,
    1,0,0,
    1,0,0,
    -1,0,0, // face x=-1
    -1,0,0,
    -1,0,0,
    -1,0,0,
    0,1,0, // face y=1
    0,1,0,
    0,1,0,
    0,1,0,
    0,-1,0, // face y=-1
    0,-1,0,
    0,-1,0,
    0,-1,0
  };
  std::vector<float> texCoord {
    0.0,1.0, // face
    0.0,0.0,
    1.0,1.0,
    1.0,0.0,
    0.0,1.0, // face
    0.0,0.0,
    1.0,1.0,
    1.0,0.0,
    0.0,1.0, // face
    0.0,0.0,
    1.0,1.0,
    1.0,0.0,
    0.0,1.0, // face
    0.0,0.0,
    1.0,1.0,
    1.0,0.0,
    0.0,1.0, // face
    0.0,0.0,
    1.0,1.0,
    1.0,0.0,
    0.0,1.0, // face
    0.0,0.0,
    1.0,1.0,
    1.0,0.0,

  };
  _cube.add("position",vertex,3,0);
  _cube.add("normal",normal,3,1);
  _cube.add("texCoord",texCoord,2,2);
  _cube.restart(4);

}

void initSegment() {
  // TODO : GL memory leak (change GLRender for empty buffer)
  glGenBuffers(1,&_segmentBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_segmentBuffer);
  glBufferData(GL_ARRAY_BUFFER,6*sizeof(GLfloat),0,GL_DYNAMIC_DRAW);
}


void drawSquare(double) {
  _square.draw();
}

void drawCylinder(double) {
  _cylinder.draw();
  _cylinderCap.draw();
}

void drawCube(double) {
  _cube.draw();
}

void drawSphere(double) {
  _sphere.draw();
}

void drawCone(double) {
  _cone.draw();
  _coneCap.draw();
}

void drawTorus(double) {
  _torus.draw();
}



/* very slow : for debug purpose only */
void drawLine(const Vector3 &a,const Vector3 &b) {
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER,_segmentBuffer);
  glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(GLfloat),a.fv());
  glBufferSubData(GL_ARRAY_BUFFER,3*sizeof(GLfloat),3*sizeof(GLfloat),b.fv());
  glVertexAttribPointer(0,3,GL_FLOAT,false,0,0);
  glDrawArrays(GL_LINES,0,2);
  glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(GLfloat),b.fv());
  glDisableVertexAttribArray(0);

}

void drawLineTo(const Vector3 &a) {
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER,_segmentBuffer);
  glBufferSubData(GL_ARRAY_BUFFER,3*sizeof(GLfloat),3*sizeof(GLfloat),a.fv());
  glVertexAttribPointer(0,3,GL_FLOAT,false,0,0);
  glDrawArrays(GL_LINES,0,2);
  glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(GLfloat),a.fv());
  glDisableVertexAttribArray(0);

}


void drawPoint(const Vector3 &a) {
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER,_segmentBuffer);
  glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(GLfloat),a.fv());
  glVertexAttribPointer(0,3,GL_FLOAT,false,0,0);
  glDrawArrays(GL_POINTS,0,1);
  glDisableVertexAttribArray(0);

}

void drawMoveTo(const Vector3 &a) {
  glBindBuffer(GL_ARRAY_BUFFER,_segmentBuffer);
  glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(GLfloat),a.fv());
}

void fillGrid(const std::vector<Vector3> &point,int nbU) {
  if (!_gridPoint || _gridPoint->nbVertex()!=int(point.size())) {
    delete _gridPoint;
    _gridPoint=new VertexArray(GL_TRIANGLE_STRIP);
    _gridPoint->add("position",point,0);
    vector<int> element((point.size()-nbU)*2);
    int index=0;
    for(unsigned int i=0;i<point.size()-nbU;++i) {
      element[index++]=i;
      element[index++]=i+nbU;
    }
    _gridPoint->element(element);
    _gridPoint->restart(2*nbU);
  }
  else {
    _gridPoint->update("position",point);
  }
  _gridPoint->draw();
}



void drawGrid(const std::vector<Vector3> &point,int nbU) {
  if (!_gridPoint || _gridPoint->nbVertex()!=int(point.size())) {
    delete _gridPoint;
    _gridPoint=new VertexArray(GL_LINES);
    _gridPoint->add("position",point,0);
    vector<int> element(point.size()*4-nbU*2);
    int index=0;
    for(unsigned int i=0;i<point.size();++i) {
      if (i<(point.size()-nbU)) {
        element[index++]=i;
        element[index++]=i+nbU;
      }
      if (i%nbU) {
        element[index++]=i;
        element[index++]=i-1;
      }
    }
    _gridPoint->element(element);
  }
  else {
    _gridPoint->update("position",point);
  }
  _gridPoint->draw();
}

void drawLineStrip(const std::vector<Vector3> &point,int nbVertex) {
  if (nbVertex==-1) nbVertex=point.size();
  if (!_lineStripPoint || _lineStripPoint->nbVertex()!=nbVertex) {
    delete _lineStripPoint;
    _lineStripPoint=new VertexArray(GL_LINE_STRIP);
    _lineStripPoint->add("position",point,0);
  }
  else {
    _lineStripPoint->update("position",point);
  }
  _lineStripPoint->draw(nbVertex);
}

void drawLines(const std::vector<Vector3> &point,int nbVertex) {
  if (nbVertex==-1) nbVertex=point.size();
  if (!_linesPoint || _linesPoint->nbVertex()!=nbVertex) {
    delete _linesPoint;
    _linesPoint=new VertexArray(GL_LINES);
    _linesPoint->add("position",point,0);
  }
  else {
    _linesPoint->update("position",point);
  }
  _linesPoint->draw(nbVertex);
}


void drawPoints(const std::vector<Vector3> &point) {
  if (point.empty()) {
    if (!_pointsPoint)
      throw ErrorD("polyline VAO is empty (should be initialized before)");
  }
  else {
    if (true) {//!_pointsPoint || _pointsPoint->nbVertex()!=point.size()) {
      delete _pointsPoint;
      _pointsPoint=new VertexArray(GL_POINTS);
      _pointsPoint->add("position",point,0);
    }
    else {
      _pointsPoint->update("position",point);
    }
  }
  _pointsPoint->draw();
}


}



