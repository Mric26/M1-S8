#ifndef VIEWER_H
#define VIEWER_H

// GLEW lib: needs to be included first!!
#include <GL/glew.h> 

// OpenGL library 
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

// OpenGL Mathematics
#include </home/a/amorel/m1info/sim/ext/glm-0.9.4.1/glm/glm.hpp>
#include </home/a/amorel/m1info/sim/ext/glm-0.9.4.1/glm/gtc/matrix_transform.hpp>

#include <QGLFormat>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <stack>

#include "camera.h"
#include "meshLoader.h"
#include "shader.h"

class Viewer : public QGLWidget {
 public:
  Viewer(char *filename,
	 const QGLFormat &format=QGLFormat::defaultFormat());
  ~Viewer();
  
 protected :
  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL(int width,int height);
  virtual void keyPressEvent(QKeyEvent *ke);
  virtual void mousePressEvent(QMouseEvent *me);
  virtual void mouseMoveEvent(QMouseEvent *me);

 private:
  // OpenGL objects creation
  void createVAO();
  void deleteVAO();

  void createTextures();
  void deleteTextures();

  void createFBO();
  void deleteFBO();

  // drawing functions 
  void drawSceneFromCamera(GLuint id);
  void drawSceneFromLight(GLuint id);
  void drawShadowMap(GLuint id);

  void loadTexture(GLuint id,const char *filename);
  void createShaders();

  QTimer        *_timer;    // timer that controls the animation
  unsigned int   _currentshader; // current shader index

  Mesh   *_mesh;   // the mesh
  Camera *_cam;    // the camera

  glm::vec3 _light; // light direction
  bool      _mode;  // camera motion or light motion
  bool      _showShadowMap;

  std::vector<std::string> _vertexFilenames;   // all vertex filenames
  std::vector<std::string> _fragmentFilenames; // all fragment filenames
  std::vector<Shader *>    _shaders;           // all the shaders 

  // vbo/vao ids 
  GLuint _vaoObject;
  GLuint _vaoFloor;
  GLuint _vaoQuad;

  GLuint _object[5];
  GLuint _floor[4];
  GLuint _quad;

  // texture ids 
  GLuint _texColor[2];
  GLuint _texNormal[2];
  
  // fbo id and associated depth texture 
  GLuint _fbo;
  GLuint _texDepth; // this will be our shadowmap! 
  unsigned int _depthResol; // this is the resolution of the shadowmap (squared texture)
};

#endif // VIEWER_H
