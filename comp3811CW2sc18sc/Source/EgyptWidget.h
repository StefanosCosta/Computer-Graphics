#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QObject>
#include <QImage>
#include "Image.h"

struct materialStruct;

class EgyptWidget: public QGLWidget
	{ //

	  Q_OBJECT

	public:
	EgyptWidget(QWidget *parent);
	double _angleView;

	public slots:
	void updateAngle();
	void updateZoom(int);
	void updateAlienRadius(int);
	void updateAlienHeight(int);
	void updateAlienRotationRadius(int);
	void updateAlienSpinSpeed(const QString);
	void updateAlienRotationSpeed(const QString);
	void alienAbduct();
	void updateArmJointProperties(const QString);
	void updateArmJointSphereProperties(const QString);
	void updateAlienProperties(const QString);
	void updateDiscProperties(const QString);
	void updateGateProperties(const QString);
	void lightsOff();
	void lightsOn();
	void angleView(int);

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();


	private:

		double _angle;
		double _zoom;
		double _alienRadius;
		double _alienRotationRadius;
		double _alienHeight;
		double _alienRotationSpeed;
		double _alienSpinSpeed;
		double _alienSize;
		bool abduct;
		bool _day;
		double _ascend;
		double _descend;
		bool _asc;
		bool _desc;
		bool _marcAsc;
		double _marcAscend;
		double _angletmp;
		double _angletmp2;
		double _spintmp;
		bool _return;
		bool _desc2;
		double _ascend2;
		double _descend2;
		double _leave;
		bool _exit;
		int _interval;
		int _limbAngle;
		bool _forth;
		materialStruct *_armJoint;
		materialStruct *_armJointSphere;
		materialStruct *_disc;
		materialStruct *_alien;
		materialStruct *_gate;

		Image   _image;
		Image _image2;
		Image _image3;
		Image _image4;
		Image _image5;
		Image _image6;

	        QImage* p_qimage;
		void fillimage();
	  void pyramid(float size, const materialStruct&);
		void plane(const materialStruct&);
		void cube();
		void alien();
		void octahedron(float scale, const materialStruct& );
		void animate();
		void drawBillBoard(GLuint txt,unsigned int w,unsigned int h, const GLubyte* field);
		void ApplyLighting();
		void boxMan();
		void updateLimbAngle();
		void alienLimb(float angle, bool clockwise);


	  struct GluPar {
	    float _x;
	    float _y;
	    float _z;
	    float _at_x;
	    float _at_y;
	    float _at_z;
	    float _up_x;
	    float _up_y;
	    float _up_z;

	    GluPar( float x,
		    float y,
		    float z,
		    float at_x,
		    float at_y,
		    float at_z,
		    float up_x,
		    float up_y,
		    float up_z ):
	      _x(x),
	      _y(y),
	      _z(z),
	      _at_x(at_x),
	      _at_y(at_y),
	      _at_z(at_z),
	      _up_x(up_x),
	      _up_y(up_y),
	      _up_z(up_z)
	    {
	    }

	  };

	  GluPar _glupar;

	}; // class GLPolygonWidget

#endif
