#include <GL/glu.h>
#include <QGLWidget>
#include <QDebug>
#include "EgyptWidget.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include "glm/gtx/string_cast.hpp"
// #include "EgyptWindow.h"
#include <QString>

// init textures
static GLuint MarcTex;
static GLuint EarthTex;
static GLuint sandTex;
static GLuint pyramidTex;
static GLuint shipTex;
static GLuint posterTex;


// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

static materialStruct goldShinyMaterials = {
  { 0.24725, 0.1995, 0.0745, 1.0},
  { 0.75164, 0.60648, 0.22648, 1.0},
  { 0.628281, 0.555802, 0.366065, 1.0},
  100
};


static materialStruct SilverShinyMaterials = {
  { 0.23125, 0.23125, 0.23125, 1.0},
  { 0.2775, 0.2775, 0.2775, 1.0},
  { 0.77391, 0.77391, 0.77391, 1.0},
  89.6
};

static materialStruct polishedgoldShinyMaterials = {
  { 0.24725, 0.2245, 0.0645, 1.0},
  { 0.34615, 0.3143, 0.0903, 1.0},
  { 0.797357, 0.723991, 0.208006, 1.0},
  83.2
};

static materialStruct emeraldMaterials = {
  { 0.0215, 0.1745, 0.0215, 0.55},
  { 0.07568, 0.61424, 0.07568, 0.55},
  { 0.633, 0.727811, 0.633, 0.55},
  76.8
};

static materialStruct PearlMaterials = {
  { 0.025, 0.20725, 0.20725, 0.922},
  { 1.0, 0.829, 0.829, 0.922},
  { 0.296648, 0.296648, 0.296648, 0.922},
  11.264
};

static materialStruct ObsidianMaterials = {
  { 0.05375, 0.05, 0.06625, 0.82},
  { 0.18275, 0.17, 0.22525, 0.82},
  { 0.332741, 0.328634, 0.346435, 0.82},
  38.4
};

static materialStruct RubyMaterials = {
  { 0.1745, 0.01175, 0.01175, 0.55},
  { 0.61424, 0.04136, 0.04136, 0.55},
  { 0.727811, 0.626959, 0.626959, 0.55},
  76.8
};


// constructor
EgyptWidget::EgyptWidget(QWidget *parent)
  : QGLWidget(parent),
    _glupar(-400.,0.,300.,100.,0.,125.,0.,0.,1.),
    _interval(10),
    _angle(0),
    _zoom(1),
    _angleView(0),
    _alienHeight(250),
    _alienRadius(35),
    _alienRotationRadius(150),
    _alienRotationSpeed(2),
    _alienSpinSpeed(2),
    abduct(false),
    _asc(false),
    _desc(false),
    _descend(0),
    _ascend(0),
    _return(false),
    _desc2(false),
    _descend2(0),
    _ascend2(0),
    _marcAsc(false),
    _leave(0),
    _exit(false),
    _limbAngle(45),
    _day(true),
    _armJoint(&SilverShinyMaterials),
    _armJointSphere(&polishedgoldShinyMaterials),
    _alien(&SilverShinyMaterials),
    _disc(&SilverShinyMaterials),
    _gate(&SilverShinyMaterials),
    _image("../textures/Marc_Dekamps.ppm"),
    _image2("../textures/Mercator-projection.ppm"),
    _image3("../textures/sand1.jpg"),
    _image4("../textures/hieroglyphics.jpg"),
    _image5("../textures/ship.jpg"),
    _image6("../textures/museum.jpg")
	{ // constructor


	} // constructor

// called when OpenGL context is set up
void EgyptWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);

  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	} // initializeGL()


// called every time the widget is resized
void EgyptWidget::resizeGL(int w, int h)
{ // resizeGL()

	// set the viewport to the entire widget
	glViewport(0, 0, w, h);
	glEnable(GL_LIGHTING); // enable lighting in general
        glEnable(GL_LIGHT0);   // each light source must also be enabled
	      glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);

  // normalise normals since our code includes non-uniform scaling operations
  glEnable(GL_NORMALIZE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  GLfloat spec[] = {1.0,1.0,1.0,1.0};
  GLfloat diffuse[] = {1.0,1.0,1.0,1.0};
  GLfloat ambient[] = {1.0,1.0,1.0,1.0};
  GLfloat dir[] = {0.0,0.0,0.0};

  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir);

  glLightfv(GL_LIGHT1,GL_SPECULAR,spec);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse);
  glLightfv(GL_LIGHT1,GL_AMBIENT,ambient);

  // generate all textures
  glGenTextures(1,&MarcTex);
  glGenTextures(1,&posterTex);
  glGenTextures(1,&EarthTex);
  glGenTextures(1,&shipTex);
  glGenTextures(1,&pyramidTex);
  glGenTextures(1,&sandTex);

	} // resizeGL()

// moves the angle of movement of alien limbs back and forth from 40 to 60
void EgyptWidget::updateLimbAngle(){

  if(_limbAngle ==40)
  {
    _forth = true;
  }
  else if (_limbAngle == 60)
  {
    _forth = false;
  }
  if(_forth)
  {
    _limbAngle++;
  }
  else
  {
    _limbAngle--;
  }
}

// update alien's angle of rotation
void EgyptWidget::updateAngle(){
  _angle += 1.0;
  // int n = (int) _angle;
  // if(n%360 ==0)
  // {
  //   _angle =0;
  // }
  updateLimbAngle();
  this->repaint();
}

//Sets the amount of zoom according to user input
void EgyptWidget::updateZoom(int i)
{
  _zoom = (double) i;
}

//Sets the roation on the z-axis around the origin according to user input
void EgyptWidget::angleView(int i)
{
  _angleView = (double) i;
}

// Updates the radius of the Alien Core according to user input
void EgyptWidget::updateAlienRadius(int i)
{
  _alienRadius = (double) i;
}

//Updates the radius of Alien's rotation according to user input
void EgyptWidget::updateAlienRotationRadius(int i)
{
  _alienRotationRadius = (double) i;
}

// Updates Height at which alien is placed according to user input
void EgyptWidget::updateAlienHeight(int i)
{
  _alienHeight = (double) i;
}

//Updates Alien's Sping speed depending on user input
void EgyptWidget::updateAlienSpinSpeed(QString i)
{
  bool ok;
  int num = i.toInt(&ok);
  if(!ok)
  {
    // qDebug() << "Conversion failed";
    // qDebug() << i;
  }
  else
  {
    //convert from rpm to degrees per 10ms
    _alienSpinSpeed = (double) (num *360*_interval)/(1000*60)*6;

  }

}

// Updates Alien's rotation Speed depending on user input
void EgyptWidget::updateAlienRotationSpeed(QString i)
{
  bool ok;
  int num = i.toInt(&ok);
  if(!ok)
  {
    // qDebug() << "Conversion failed";
    // qDebug() << i;
  }
  else
  {
  _alienRotationSpeed = (double) (num *360*_interval)/(1000*60)*6;
  }
}

// sets the scene setting to night
void EgyptWidget::lightsOff()
{
  _day = false;
}

//sets the scene setting to day
void EgyptWidget::lightsOn()
{
  _day = true;
}

//Signals the beginning of alien Abduction
void EgyptWidget::alienAbduct()
{
  abduct = true;
  _asc = true;
}


// Updates Material Properties of Alien's Core depending on user input
void EgyptWidget::updateAlienProperties(QString i)
{
  // qDebug() << i;
  if(i == "Polished Gold")
  {
    _alien = &polishedgoldShinyMaterials;
  }
  else if(i == "Polished Silver")
  {
    _alien = &SilverShinyMaterials;
  }
  else if(i == "Emerald")
  {
    _alien = &emeraldMaterials;
  }
  else if(i == "Gold")
  {
    _alien = &goldShinyMaterials;
  }
  else if(i == "Obsidian")
  {
    _alien = &ObsidianMaterials;
  }
  else if(i == "Pearl")
  {
    _alien = &PearlMaterials;
  }
  else if(i == "Ruby")
  {
    _alien = &RubyMaterials;
  }

}
// Updates Material Properties of alien arm joints depending on user input
void EgyptWidget::updateArmJointProperties(QString i)
{
  // qDebug() << i;
  if(i == "Polished Gold")
  {
    _armJoint = &polishedgoldShinyMaterials;
  }
  else if(i == "Polished Silver")
  {
    _armJoint = &SilverShinyMaterials;
  }
  else if(i == "Emerald")
  {
    _armJoint = &emeraldMaterials;
  }
  else if(i == "Gold")
  {
    _armJoint = &goldShinyMaterials;
  }
  else if(i == "Obsidian")
  {
    _armJoint = &ObsidianMaterials;
  }
  else if(i == "Pearl")
  {
    _armJoint = &PearlMaterials;
  }
  else if(i == "Ruby")
  {
    _armJoint = &RubyMaterials;
  }

}

// Updates Material Properties of alien Disc depending on user input
void EgyptWidget::updateDiscProperties(QString i)
{
  // qDebug() << i;
  if(i == "Polished Gold")
  {
    _disc = &polishedgoldShinyMaterials;
  }
  else if(i == "Polished Silver")
  {
    _disc = &SilverShinyMaterials;
  }
  else if(i == "Emerald")
  {
    _disc = &emeraldMaterials;
  }
  else if(i == "Gold")
  {
    _disc = &goldShinyMaterials;
  }
  else if(i == "Obsidian")
  {
    _disc = &ObsidianMaterials;
  }
  else if(i == "Pearl")
  {
    _disc = &PearlMaterials;
  }
  else if(i == "Ruby")
  {
    _disc = &RubyMaterials;
  }

}

// Updates Material Properties of alien arm joint Spheres depending on user input
void EgyptWidget::updateArmJointSphereProperties(QString i)
{
  // qDebug() << i;
  if(i == "Polished Gold")
  {
    _armJointSphere = &polishedgoldShinyMaterials;
  }
  else if(i == "Polished Silver")
  {
    _armJointSphere = &SilverShinyMaterials;
  }
  else if(i == "Emerald")
  {
    _armJointSphere = &emeraldMaterials;
  }
  else if(i == "Gold")
  {
    _armJointSphere = &goldShinyMaterials;
  }
  else if(i == "Obsidian")
  {
    _armJointSphere = &ObsidianMaterials;
  }
  else if(i == "Pearl")
  {
    _armJointSphere = &PearlMaterials;
  }
  else if(i == "Ruby")
  {
    _armJointSphere = &RubyMaterials;
  }

}

// Updates Material Properties of alien gate depending on user input
void EgyptWidget::updateGateProperties(QString i)
{
  if(i == "Polished Gold")
  {
    _gate = &polishedgoldShinyMaterials;
  }
  else if(i == "Polished Silver")
  {
    _gate = &SilverShinyMaterials;
  }
  else if(i == "Emerald")
  {
    _gate = &emeraldMaterials;
  }
  else if(i == "Gold")
  {
    _gate = &goldShinyMaterials;
  }
  else if(i == "Obsidian")
  {
    _gate = &ObsidianMaterials;
  }
  else if(i == "Pearl")
  {
    _gate = &PearlMaterials;
  }
  else if(i == "Ruby")
  {
    _gate = &RubyMaterials;
  }

}

//Creates an octahedron scaled to form a crystal
void EgyptWidget::octahedron(float scale, const materialStruct& material)
{

  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  // create top of crystal:

  float halfscale = 0.5*scale;
  glm::vec3 v1 = { halfscale, -halfscale, 0.0};
  glm::vec3 v2 = { halfscale, halfscale, 0.0};
  glm::vec3 v3 = { 0., 0., scale };

  glm::vec3 n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = { halfscale, halfscale, 0};
  v2 = {-halfscale, halfscale, 0};

  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-halfscale, halfscale, 0};
  v2 = {-halfscale,-halfscale, 0};

  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-halfscale, -halfscale, 0};
  v2 = { halfscale, -halfscale, 0};

  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  // Create bottom of crystal

  v1 = { halfscale, -halfscale, 0.0};
  v2 = { halfscale, halfscale, 0.0};
  v3 = { 0., 0., -scale };

  n  = glm::normalize(glm::cross(v3 - v2, v2 - v1));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = { halfscale, halfscale, 0};
  v2 = {-halfscale, halfscale, 0};


  n  = glm::normalize(glm::cross(v3 - v2, v2 - v1));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-halfscale, halfscale, 0};
  v2 = {-halfscale,-halfscale, 0};

  n  = glm::normalize(glm::cross(v3 - v2, v2 - v1));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-halfscale, -halfscale, 0};
  v2 = { halfscale, -halfscale, 0};

  n  = glm::normalize(glm::cross(v3 - v2, v2 - v1));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(v2[0], v2[1], v2[2]);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

}

// creates a pyramid using provided material properties and height scaling
//Applies textures such that they are horizontally applied on each triangle forming it
void EgyptWidget::pyramid(float scale, const materialStruct& material){

  // enable texturing
  glEnable(GL_TEXTURE_2D);

  //apply material properties
  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  //define triangle coordinates
  glm::vec3 v1 = { scale, -scale, 0.0};
  glm::vec3 v2 = { scale, scale, 0.0};
  glm::vec3 v3 = { 0., 0., scale };

  // calculate normal and normalize it to unit vector
  glm::vec3 n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);
  glVertex3f(v1[0], v1[1], v1[2]);
  glTexCoord2f(1.0,0.0);
  glVertex3f(v2[0], v2[1], v2[2]);
  glTexCoord2f(0.5,1.0);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = { scale, scale, 0};
  v2 = {-scale, scale, 0};


  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);
  glVertex3f(v1[0], v1[1], v1[2]);
    glTexCoord2f(1.0,0.0);
  glVertex3f(v2[0], v2[1], v2[2]);
  glTexCoord2f(0.5,1.0);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-scale, scale, 0};
  v2 = {-scale,-scale, 0};

  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glColor3f(0.0,1.0,0.0);   // blue; facing positive x-axis

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);
  glVertex3f(v1[0], v1[1], v1[2]);
  glTexCoord2f(1.0,0.0);
  glVertex3f(v2[0], v2[1], v2[2]);
  glTexCoord2f(0.5,1.0);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  v1 = {-scale, -scale, 0};
  v2 = { scale, -scale, 0};

  n  = glm::normalize(glm::cross(v2 - v1, v3 - v2));

  glNormal3fv(glm::value_ptr(n));
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);
  glVertex3f(v1[0], v1[1], v1[2]);
  glTexCoord2f(1.0,0.0);
  glVertex3f(v2[0], v2[1], v2[2]);
  glTexCoord2f(0.5,1.0);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

 // disable texturing
 glDisable(GL_TEXTURE_2D);
}

// creates a plane using provided material properties and normal coordinates
void EgyptWidget::plane(const materialStruct &material){
  //enable texturing
  glEnable(GL_TEXTURE_2D);

  //apply material properties to front of plane
  glMaterialfv(GL_FRONT, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   material.specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   material.shininess);

  //apply material properties to back of plane
  glMaterialfv(GL_BACK, GL_AMBIENT,    material.ambient);
  glMaterialfv(GL_BACK, GL_DIFFUSE,    material.diffuse);
  glMaterialfv(GL_BACK, GL_SPECULAR,   material.specular);
  glMaterialf(GL_BACK, GL_SHININESS,   material.shininess);

  GLfloat normals[][3] = { {0, 0 ,1} };

  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f( 1.0,  1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
  glEnd();

  //disable texturing
  glDisable(GL_TEXTURE_2D);
}


void EgyptWidget::cube(){

  //enable texturing
  glEnable(GL_TEXTURE_2D);


  // the correctly calculated normals for the cube faces below
  GLfloat normals[][3] = { {1., 0. ,0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };


  // make cube properties brassMaterials
  materialStruct* p_front = &brassMaterials;

  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  //create one face with texturing
  //front plane
  glNormal3fv(normals[5]);
  glBegin(GL_POLYGON);
    glTexCoord2f(0.8, 0.8);
    glVertex3f(  1.0,  -1.0,  1.0);
    glTexCoord2f(0.8, 0.2);
    glVertex3f(  1.0,  -1.0, -1.0);
    glTexCoord2f(0.2, 0.2);
    glVertex3f( -1.0,  -1.0, -1.0);
    glTexCoord2f(0.2, 0.8);
    glVertex3f( -1.0,  -1.0,  1.0);
  glEnd();

  //bind back to default texture
  glBindTexture(GL_TEXTURE_2D,0);

  //right plane
  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
  glEnd();

  // bottom
  glNormal3fv(normals[3]);
  glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
  glEnd();

  //top
  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);
    glVertex3f( 1.0,  1.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
  glEnd();

  //left plane
  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
    glVertex3f( -1.0, -1.0,  1.0);
    glVertex3f( -1.0, -1.0, -1.0);
    glVertex3f( -1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0,  1.0);
  glEnd();

  //back plane
  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
    glVertex3f(  1.0,  1.0,  1.0);
    glVertex3f(  1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0,  1.0);
  glEnd();




  glDisable(GL_TEXTURE_2D);
}

//creates an alien Limb at the angle passed to it given its rotation
void EgyptWidget::alienLimb(float angle, bool clockwise)
{
  glPushMatrix();

  float sign = 1;
  if(!clockwise){sign = sign*-1;}

  // create new quadric object
  GLUquadricObj *joint = gluNewQuadric();
  gluQuadricDrawStyle(joint,GLU_FILL);
  gluQuadricTexture(joint,GL_TRUE);
  gluQuadricOrientation(joint,GLU_OUTSIDE);

  //set joint material properties from user input
  materialStruct* p_front = _armJoint;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  // set joint size to 1/8 of core size
  double jointSize = 0.125;

  // rotate the cylinder joint by requested angle on y axis to place arm
  glRotatef(angle,0,1,0);

  //place the joint at the end of the core's radius at that angle
  glTranslatef(0,0,1);
  gluCylinder(joint,jointSize,jointSize,1,60,60);

  //place the next joint at the end of the previous joint + half the radius of the second joint
  glTranslatef(0,0,1+jointSize);

  //set the size of the next joint to 1/4 the size of the alien core
  double jointSphereRadius = 0.25;

  //rotate the sphere so that its centre point that would normally face the camera
  // is now facing away from the alien core/ cylinder arm joint on the x axis
  glRotatef(-angle + sign*90,0,1,0);

  // set arm joint sphere material properties as user input
  p_front = _armJointSphere;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  //draw joint sphere
  gluSphere(joint,jointSphereRadius,60,60);
  // glScalef(1/0.25,1/0.25,1/0.25);



  //// set arm joint material properties as user input
  p_front = _armJoint;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  //rotate next joint at a constant rate of 50 degrees per frame counterclockwise
  //on the current matrix, the x axis is now the z axis due to last rotation
  glRotated(-50*_angle,1,0,0);

  // place next joint at the other end of the previous joint
  glTranslatef(0,0,jointSphereRadius/1.2);

  glPushMatrix();
  //set  radius of cylinder joint as half that of the previous sphere joint
  //and height as half of first joint
  gluCylinder(joint,jointSize,jointSize,0.5,60,60);

  //place next sphere at end of cylinder joint
  glTranslatef(0,0,0.5 + jointSize);
  // glScalef(0.25,0.25,0.25);

  //apply material properties from user input
  p_front = _armJointSphere;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
  //draw sphere joint
  gluSphere(joint,jointSphereRadius,60,60);
  glPopMatrix();
  glPopMatrix();
}


/* creates an alien made of spheres, cylinders and torus
using material properties from user input */
void EgyptWidget::alien()
{
  // set alien core material properties
  materialStruct* p_front = _alien;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  // create new glu object
  GLUquadricObj *alien = gluNewQuadric();
  gluQuadricDrawStyle(alien,GLU_FILL);
  gluQuadricTexture(alien,GL_TRUE);
  gluQuadricOrientation(alien,GLU_OUTSIDE);

  // CREATE ALIEN  ///
  glPushMatrix();

  glPushMatrix();
  // Place diamond on top of core at half the core's size and at a distance of ts diameter
  glTranslatef(0,0,2*_alienRadius);
  glScalef(0.5,0.5,0.5);
  this->octahedron(_alienRadius,*_alien);
  glScalef(1/0.5,1/0.5,1/0.5);
  glPopMatrix();

  //rotate alien to face camera
  // glRotatef(180,0,0,1);

  // enable texturing, apply current texture to sphere and revert back to default
  glEnable(GL_TEXTURE_2D);
  gluSphere(alien,_alienRadius,60,60);
  glBindTexture(GL_TEXTURE_2D,0);

  // rotate disc 180 degrees so that it is horizontally aligned
  // glRotatef(180,0,0,1);

  //apply disc's user input material properties
  p_front = _disc;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  //deform torus to a tenth of its height to create a disc:
  glScalef(1,1,0.1);
  glutSolidTorus(_alienRadius, _alienRadius,60,60);
  glScalef(1,1,10);
  //undo deformation

  //apply gate's user input material properties
  p_front = _gate;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  //Place first gate component at the bottom of core
  glTranslatef(0,0,-_alienRadius);

  //set torus inner and outer radi to a 5th of the core's radius
  glutSolidTorus(0.20*_alienRadius, 0.20*_alienRadius,60,60);

  //Place second gate component at the bottom of the first component
  glTranslatef(0,0,-0.25*_alienRadius);
  glutSolidTorus(0.125*_alienRadius, 0.125*_alienRadius,60,60);

  // return to initial coordinates at centre of core
  glTranslatef(0,0,1.25*_alienRadius);
  glScalef(_alienRadius,_alienRadius,_alienRadius);
  // create 4 alien limbs using limbangle
  alienLimb(_limbAngle,true);
  alienLimb(-_limbAngle,false);
  alienLimb(180-_limbAngle,true);
  alienLimb(-180+_limbAngle,false);

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

}


// Animates Alien Abduction:
void EgyptWidget::animate()
{
    // Place alien at its height from user input
    glTranslatef(0,0,_alienHeight);
    // If abduction is not occuring
    if(abduct == false)
    {

      if(_alienRotationSpeed == 0)
      {
        glRotatef(_angletmp,0,0,1);
      }
      else
      {
        glRotatef(_alienRotationSpeed*_angle,0,0,1);
        //save angle of rotation
        _angletmp = _alienRotationSpeed*_angle;
      }

    }
    else
    {
      // if abduction is occuring, remain stationary at last rotation angle
      glRotatef(_angletmp,0,0,1);
    }
    // Place alien at distance from origin being radius
    glTranslatef(0,_alienRotationRadius,0);

    //if abduction is not occuring
    if(abduct == false)
    {
      //spin alien around itself and save angle of rotation
      glRotatef(_alienSpinSpeed*_angle,0,0,1);
      _spintmp = _alienSpinSpeed*_angle;
    }
    else
    {
      //if abduction is occuring remain stationary at last spin angle
      glRotatef(_spintmp,0,0,1);
    }

    // If first ascension is occuring
    if(abduct == true && _asc == true)
    {
      // Ascend alien
      glTranslatef(0,0,_ascend);

      //if ascension does not place alien outside of map, keep ascending
      if(_ascend< (400))
      {
        _ascend+=5;

      }
      else
      {
        //otherwise signal time for alien descent
        _desc = true;
      }
    }

    // if first descent is occuring
    if(abduct == true && _desc ==true)
    {
      // undo rotating animation
      glRotatef(-_spintmp,0,0,1);
      glTranslatef(0,-_alienRotationRadius,0);
      glRotatef(-_angletmp,0,0,1);

      //place alien above Marc
      glTranslatef(-15,0,-_descend);
      //make alien face the camera
      glRotatef(180,0,0,1);

      // descend alien to height 250:
      if(_descend < (400+_alienHeight-250))
      {
        _descend+=3;
      }
      else
      {
        //once height is reached signal Marc abduction
        _marcAsc = true;
      }
    }

    // if Marc has been abducted and alien must return
    if(abduct == true &&_return ==true)
    {
      // start ascending
      glTranslatef(0,0,_ascend2);

      //if alien has not left the scene keep ascending
      if(_ascend2 < (400))
      {
        _ascend2+=5;
      }
      else
      {
        //otherwise signal second descent
        _desc2 = true;
      }
    }

    //if second descent is occuring
    if(abduct == true &&_desc2 ==true)
    {
      //place alien back to above the origin
      glTranslatef(15,0,0);

      //descend alien
      glTranslatef(0,0,-_descend2);

      //apply rotating animation while descending
      glRotatef(_alienRotationSpeed*_angle,0,0,1);
      glTranslatef(0,_alienRotationRadius,0);
      glRotatef(_alienSpinSpeed*_angle,0,0,1);

      //if alien has reached  the previous alien height signal the exit
      if(_descend2 > (400-_alienHeight+250))
      {
        _exit = true;
        _desc2 =false;
      }
      else
      {
        //otherwise descend
        _descend2+=1;
      }
    }

    if(abduct == true && _exit == true)
    {
      //make alien leave by spiralling upwards and to its right depending on its rotation
      glTranslatef(_leave,0,_leave);
      // if alien has left the scene, reset animation
      if(_leave > 450)
      {
        _desc = false;
        _desc2 = false;
        _asc = false;
        _return = false;
        abduct = false;
        _marcAsc = false;
        _exit = false;
        _ascend =0;
        _ascend2 = 0;
        _descend = 0;
        _descend2 = 0;
        _marcAscend = 0;
        _leave =0;
      }
      else
      {
        //otherwise keep going
        _leave +=3;
      }
    }

}

// Draws a billboard with the texture provided to it
void EgyptWidget::drawBillBoard(GLuint txt,unsigned int w,unsigned int h, const GLubyte* field)
{
    //define material properties as brass
   materialStruct* p_front = &brassMaterials;

   glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
   glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
  //  create new quadric object
   GLUquadricObj *pole = gluNewQuadric();
   gluQuadricDrawStyle(pole,GLU_FILL);
  //  gluQuadricTexture(cone,GL_TRUE);
   gluQuadricOrientation(pole,GLU_OUTSIDE);

   // Create first pole with height 20 and radius 1
   gluCylinder(pole,1,1,20,60,60);

   //Generate and Apply texture Provided
  //  glGenTextures(1,&txt);
   glBindTexture(GL_TEXTURE_2D,txt);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, field);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   //save current matrix for later
   glPushMatrix();
   //bring board into place
   glTranslatef(10+1,1,15);
   // Set the width of the plane as 10 and its height as 5
   glScalef(10,1,5);
   //rotate the plane around the x axis to make it face up
   glRotatef(90,1,0,0);

   //draw the plane
   this->plane(brassMaterials);

   glScalef(1/10,1,1/5);

   //revert back to default texture
   glBindTexture(GL_TEXTURE_2D,0);

   //revert back to previous world coordinates to undo rotation on x axis
   glPopMatrix();

   //create second Pole
   glPushMatrix();
   //place cylinder at distance which is the sum of the widths of the pole and plane
   glTranslatef(20 + 2,0,0);
   gluCylinder(pole,1,1,20,60,60);
   glPopMatrix();
}

// Turns lights on or off depending on whether it's day or night
void EgyptWidget::ApplyLighting()
{
  if(_day == true)
  {
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glClearColor(0.0f,0.6f,0.6f,0.0f);
  }
  else
  {
    glDisable(GL_LIGHT0);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
  }
}

// Creates a box man out of cubes from top to bottom
void EgyptWidget::boxMan()
{
  glPushMatrix();

  //default height is (2 + 4 +5) = 11
  glTranslatef(0,0,11);

  // create head with size 1 (height = 2)
  glPushMatrix();
  this->cube();
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D,0);

  //move to bottom of head
  glTranslatef(0,0,-1-2.5);
  // create Torso with double double width and depth and 2.5 times height of head
  glPushMatrix();
  glScalef(2,2,2.5); //(height = 5) , width = 4
  this->cube();
  glScalef(1/2,1/2,1/2.5);
  glPopMatrix();

  //create left hand
  glPushMatrix();
  //move to left edge of torso
  glTranslatef(-2 -0.8 -0.1,0,0);
  //hand with 0.8 times width, 1.5 times depth and double height of head
  glScalef(0.8,1.5,2);
  this->cube();
  glPopMatrix();

  //create right hand
  glPushMatrix();
  //move to right edge of torso
  glTranslatef(2+0.8 +0.1,0,0);
  //hand with 0.8 times width, 1.5 times depth and double height of head
  glScalef(0.8,1.5,2);
  this->cube();
  glPopMatrix();

  //Create left leg
  glPushMatrix();
  // move to bottom left of torso
  glTranslatef(-1,0,-4.5);
  //leg with 0.9 times width,the depth and double height of head
  glScalef(0.9,1,2); // (height = 4)
  this->cube();
  glPopMatrix();

  //create right leg
  glPushMatrix();
  // move to bottom right of torso
  glTranslatef(1,0,-2.5 -2);
  //leg with 0.9 times width,the depth and double height of head
  glScalef(0.9,1,2);
  this->cube();
  glPopMatrix();

  glPopMatrix();

}

// called every time the widget needs painting
void EgyptWidget::paintGL()
{ // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
      	glLoadIdentity();

  // set Perspective settings
  gluPerspective(100-_zoom,4/3,100,1000);
	// You must set the matrix mode to model view directly before enabling the depth test
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result

	glLoadIdentity();

  //apply lighting conditions day/night
  this->ApplyLighting();

  //if abduction is taking place bring camera closer and higher
  if(abduct)
  {
    _glupar._at_x = 100;
    _glupar._at_y = 0;
    _glupar._at_z = 125;
  }
  else
  {
    //otherwise place it low
    _glupar._at_x = 0;
    _glupar._at_y = 0;
    _glupar._at_z = 20;
  }

  //place the camera
  gluLookAt(
      _glupar._x,
      _glupar._y,
      _glupar._z,
      _glupar._at_x,
      _glupar._at_y,
      _glupar._at_z,
      _glupar._up_x,
      _glupar._up_y,
      _glupar._up_z);

  //apply lighting after camera is placed
  GLfloat light_pos1[] = {0, 0, 300, 1.};
  glLightfv(GL_LIGHT1,GL_POSITION, light_pos1);
  glEnable(GL_LIGHT1);

  //rotate to align scene with camera
  glRotatef(-90,0,0,1);
  //Perform Rotation from user input
  glRotatef(-_angleView,0,0,1);

  int i;

  //////// CREATE FLOOR ///////////
  glPushMatrix();
  //set floor size to 500 more than view to allow effect of horizon
  glScaled(1500,1500,1);

  // bind to sand texture
  glBindTexture(GL_TEXTURE_2D,sandTex);
  glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGB,
                _image3.Width(),
                _image3.Height(),
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                _image3.imageField());

  //set to repeat
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//set to average out
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //add golden floor
  this->plane(goldShinyMaterials);

  //bind back to default texture
  glBindTexture(GL_TEXTURE_2D,0);
  glScaled(1/1500,1/1500,1);
  glPopMatrix();
  /////// END FLOOR CREATION ///////

  ////CREAT MARC BoxMan////
  glPushMatrix();

  // Bind to Marc Texture
  glBindTexture(GL_TEXTURE_2D,MarcTex);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGB,
               _image.Width(),
               _image.Height(),
               0,
               GL_RGB,
               GL_UNSIGNED_BYTE,
              _image.imageField());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // plave mark next to origin and prepare for a boxman of height 10
  glTranslatef(-15,0,0);

  // if abduction is occuring and marc is ascending
  if(abduct == true && _marcAsc == true)
  {
    GLfloat alienDiff[] = {0.0,1.0,0.0,1.0};
    GLfloat defaultDiff[] = {1.0,1.0,1.0,1.0};
    GLfloat cut[] = {120};
    GLfloat defaultCut[] = {180};
    GLfloat light_pos0[] = {0, 0, 200, 1.};
    GLfloat dir[] = {0.0,0.0,0.0};

    //rotate mark around himself
    glRotatef(_angle,0,0,1);
    //ascend mark
    glTranslatef(0,0,_marcAscend);
    //if marc has not been taken keep ascending
    if(_marcAscend<200)
    {
      _marcAscend+=1;
      glLightfv(GL_LIGHT1,GL_POSITION, light_pos0);
      glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dir);
      glLightfv(GL_LIGHT1,GL_SPOT_CUTOFF,cut);
      glLightfv(GL_LIGHT1,GL_DIFFUSE,alienDiff);
    }
    else
    { //otherwise  signal alien return
      _return = true;
      _asc = true;
      glLightfv(GL_LIGHT1,GL_DIFFUSE,defaultDiff);
      glLightfv(GL_LIGHT1,GL_SPOT_CUTOFF,defaultCut);
      glLightfv(GL_LIGHT1,GL_POSITION, light_pos1);
    }
  }

  //set marc boxman to double its size
  glScalef(2,2,2);

  // if marc cube is being abducted and alien is returning, don't draw Marc
  if(abduct && _return)
  {

  }
  else
  {
    //otherwise draw Marc
    this->boxMan();
  }
  //undo scaling
  glScalef(1/2,1/2,1/2);
  glPopMatrix();
  ///////// END Marc CUBE CREATION //////////


  //////// Draw double billboard //////////
  // Draw a billboard with the Earth texture next to marc
  //make texture replace the material Properties
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  this->drawBillBoard(EarthTex,_image2.Width(),_image2.Height(),_image2.imageField());
  //revert back to mixing material properties with texture
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  //Draw another billborad on top of it to create a larger billboard using the museum texture
  glPushMatrix();
  glTranslatef(0,0,11);
  this->drawBillBoard(posterTex,_image6.Width(),_image6.Height(),_image6.imageField());
  glPopMatrix();
  //////// END Double billboard Creation //////////


  //Add pyramids

  // define pyramid coordinates in array
  float arr[16] = {-225,-0,
                    225,0,
                    125,200,
                    -125,200};


  // Generate bind to pyramid hieroglyphics texture
  glBindTexture(GL_TEXTURE_2D,pyramidTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image4.Width(), _image4.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image4.imageField());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


  // Place a pyramid at each coordinate in coordinate array
  for( i = 0; i<4; i++)
  {
    glPushMatrix();
    glTranslatef(arr[2*i],arr[2*i+1],0.);
    this->pyramid(75.,goldShinyMaterials);
    glPopMatrix();
  }

  // define billboard coordinates in array
  float arr2[16] = {-145,0,
                    145,0,
                    125,120,
                    -125,120};
  // add billboard angles of rotation in array
  int angles[4] = {90,90,0,0};

  // draw billboards at each coordinate and rotation
  for( i = 0; i<4; i++)
  {
    glPushMatrix();
    glTranslatef(arr2[2*i],arr2[2*i+1],0.);
    glRotatef(angles[i],0,0,1);
    this->drawBillBoard(posterTex,_image6.Width(),_image6.Height(),_image6.imageField());
    glPopMatrix();
  }

  int j = 0;
  // add angles from the centre that will be the billboard  in an array
  float angles2[7] = {45,67.5,90,112.5,135};

  // if it is day
  if(_day)
  {
    // Draw the people around the billboard at the angles from the array with radius 40
    for( i = 0; i<4; i++)
    {
      for(j=0; j<5;j++)
      {
        glPushMatrix();
        glTranslatef(0,10,0);

        glTranslatef(arr2[2*i],arr2[2*i+1],10.);
        if(arr2[2*i]>0 && arr2[2*i+1] == 0)
        {
          glRotatef(-90,0,0,1);
        }
        if(arr2[2*i] < 0 && arr2[2*i+1] == 0)
        {
          glRotatef(90,0,0,1);
        }
        //rotate boxman around billboard with radius 40
        glRotatef(angles2[j],0,0,1);
        glTranslatef(-40,0,0);
        glRotatef(-angles2[j],0,0,1);

        //double the size of a boxman
        glScalef(2,2,2);
        this->boxMan();
        glPopMatrix();
      }
    }
  }


  //apply animation to alien ship
  this->animate();

  // bind to alien texture
  glBindTexture(GL_TEXTURE_2D,shipTex);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGB,
               _image5.Width(),
               _image5.Height(),
               0,
               GL_RGB,
               GL_UNSIGNED_BYTE,
               _image5.imageField());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // create alien ship
  this->alien();


  glLoadIdentity();

	// flush to screen
	glFlush();

	} // paintGL()
