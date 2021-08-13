#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QTimer>
#include <QBoxLayout>
#include <QLabel>
#include "EgyptWidget.h"

class EgyptWindow: public QWidget
	{
	public:


	// constructor / destructor
	EgyptWindow(QWidget *parent);
	~EgyptWindow();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
		// file menu
		QMenu *fileMenu;
			// quit action
			QAction *actionQuit;

	// window layout
	QBoxLayout *windowLayout;

	// beneath that, the main widget
	EgyptWidget *egyptWidget;
	// and a slider for the number of vertices
	QSlider *zoomSlider;
	QSlider *angleViewSlider;
	QSlider *alienHeightSlider;
	QLabel *rotateValue;

	QTimer *otimer;

	// resets all the interface elements
	void ResetInterface();
	};

#endif
