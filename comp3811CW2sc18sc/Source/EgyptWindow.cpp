#include "EgyptWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "EgyptWidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>

// constructor / destructor
EgyptWindow::EgyptWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// create menu bar
	menuBar = new QMenuBar(this);

	// create file menu
	fileMenu = menuBar->addMenu("&File");

	// create the action
	actionQuit = new QAction("&Quit", this);

	// leave signals & slots to the controller

	// add the item to the menu
	fileMenu->addAction(actionQuit);

	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);

	//create first Controls Layout:
	QWidget *controls = new QWidget();
	// create main widget
	egyptWidget = new EgyptWidget(this);


	//vertical box for controls
	QVBoxLayout *QVLayout = new QVBoxLayout;

	//create new row in vertical box as Horizontal box
	QHBoxLayout *QHLayout2 = new QHBoxLayout;

	//create Buttons for control box
	QPushButton *abductbtn = new QPushButton("Abduct");
	QPushButton *lightbtn = new QPushButton("Day");
	QPushButton *darkbtn = new QPushButton("Night");

	//add widgets to horizontal layout
	QHLayout2->addWidget(lightbtn);
	QHLayout2->addWidget(darkbtn);

	//Add abduct button to the vlayout
	QVLayout->addWidget(abductbtn);
	QVLayout->addLayout(QHLayout2);

	//Create radius controls in Form Layout:
	QHBoxLayout *alienLayout = new QHBoxLayout;
	QFormLayout *alienForm = new QFormLayout;


	//create alien spin speed controls in same form layout:
	QLabel *spinLbl = new QLabel("Alien Spin (rpm):");
	QLineEdit *spinValue = new QLineEdit();
	spinValue->setFixedWidth(150);
	spinValue->setPlaceholderText("Insert Spin speed here");
	alienForm->addRow(spinLbl,spinValue);

	// create alien rotate controls and place them in the same Form layour
	QLabel *alienRotateLbl = new QLabel("Alien Rotation(rpm):");
	QLineEdit *rotateValue = new QLineEdit();
	rotateValue->setFixedWidth(150);
	rotateValue->setPlaceholderText("Insert Rotation speed");
	alienForm->addRow(alienRotateLbl,rotateValue);

	// Create Sliders and labels for alien manipulation
	QSlider *alienRtRadiusSlider = new QSlider(Qt::Horizontal);
	QSlider *alienSizeSlider = new QSlider(Qt::Horizontal);
	alienHeightSlider = new QSlider(Qt::Horizontal);
	QLabel *alienRtRadius = new QLabel("Alien Rotation Radius");
	QLabel *radiusLbl = new QLabel("Alien Core Radius:");
	QLabel *alienHeight = new QLabel("Alien Height");

	//Set slider Properties according to egyptWidget presets
	alienHeightSlider->setMaximum(300);
	alienHeightSlider->setMinimum(150);
	alienHeightSlider->setValue(200);

	alienSizeSlider->setMaximum(40);
	alienSizeSlider->setMinimum(5);
	alienSizeSlider->setValue(30);

	alienRtRadiusSlider->setMaximum(200);
	alienRtRadiusSlider->setValue(150);

	//add sliders and labels in same Form layout
	alienForm->addRow(radiusLbl,alienSizeSlider);
	alienForm->addRow(alienRtRadius,alienRtRadiusSlider);
	alienForm->addRow(alienHeight,alienHeightSlider);

	//place The form in an Hlayout box
	alienLayout->addLayout(alienForm);
	QVLayout->addLayout(alienLayout);


	// Create list of Colour property options
	QStringList commands = { "Emerald","Polished Silver","Gold","Polished Gold", "Obsidian", "Pearl", "Ruby"};

	//Create groupbox, label and combobox for colour properties drop down menu of Arm Joints
	QGroupBox *armJointGroup = new QGroupBox();
	QLabel *armJointLbl = new QLabel("Alien Arm Joint Material Properties:");
	QComboBox *armJointBox = new QComboBox;
	QGridLayout *grid = new QGridLayout;
	armJointBox->addItems(commands);
	armJointBox->setCurrentIndex(1);
	//place them in a gridLayout
	grid->addWidget(armJointLbl,0,0);
	grid->addWidget(armJointBox,1,0,1,2);
	armJointGroup->setLayout(grid);

	//Create drop down menu controls for Arm Joint Spheres
	QGroupBox *armJointGroup2 = new QGroupBox();
	QLabel *armJointLbl2 = new QLabel("Alien Arm Joint Sphere Material Properties:");
	QComboBox *armJointBox2 = new QComboBox;
	QGridLayout *grid2 = new QGridLayout;
	armJointBox2->addItems(commands);
	armJointBox2->setCurrentIndex(3);
	grid2->addWidget(armJointLbl2,0,0);
	grid2->addWidget(armJointBox2,1,0,1,2);
	armJointGroup2->setLayout(grid2);


	//Create drop down menu controls for Alien Core
	QGroupBox *armJointGroup3 = new QGroupBox();
	QLabel *armJointLbl3 = new QLabel("Alien Core Material Properties:");
	QComboBox *armJointBox3 = new QComboBox;
	QGridLayout *grid3 = new QGridLayout;
	armJointBox3->addItems(commands);
	armJointBox3->setCurrentIndex(1);
	grid3->addWidget(armJointLbl3,0,0);
	grid3->addWidget(armJointBox3,1,0,1,2);
	armJointGroup3->setLayout(grid3);


	//Create drop down menu controls for Disc
	QGroupBox *armJointGroup4 = new QGroupBox();
	QLabel *armJointLbl4 = new QLabel("Alien Disc Material Properties:");
	QComboBox *armJointBox4 = new QComboBox;
	QGridLayout *grid4 = new QGridLayout;
	armJointBox4->addItems(commands);
	armJointBox4->setCurrentIndex(3);
	grid4->addWidget(armJointLbl4,0,0);
	grid4->addWidget(armJointBox4,1,0,1,2);
	armJointGroup4->setLayout(grid4);


	//Create drop down menu controls for Alien Gate
	QGroupBox *armJointGroup5 = new QGroupBox();
	QLabel *armJointLbl5 = new QLabel("Alien Abduct Gate Material Properties:");
	QComboBox *armJointBox5 = new QComboBox;
	QGridLayout *grid5 = new QGridLayout;
	armJointBox5->addItems(commands);
	armJointBox5->setCurrentIndex(3);
	grid5->addWidget(armJointLbl5,0,0);
	grid5->addWidget(armJointBox5,1,0,1,2);
	armJointGroup5->setLayout(grid5);

	//add the Grid layouts to the main controls vlayout
	QVLayout->addWidget(armJointGroup);
	QVLayout->addWidget(armJointGroup2);
	QVLayout->addWidget(armJointGroup3);
	QVLayout->addWidget(armJointGroup4);
	QVLayout->addWidget(armJointGroup5);

	//add the vlayout to the main control box
  controls->setLayout(QVLayout);
	controls->setFixedWidth(300);


	//create Second Controls Box:
	QVBoxLayout *controls2 = new QVBoxLayout;
	controls2->addWidget(egyptWidget);

	// add control boxes to widget
	windowLayout->addWidget(controls);
	windowLayout->addLayout(controls2);


	// create labels for second control box
	QLabel *zoomLbl = new QLabel("Zoom:");
	QLabel *rotateLbl = new QLabel("Rotate Viewing Angle:");


	// create sliders for scene zoom and angle manipulation
	zoomSlider = new QSlider(Qt::Horizontal);
	angleViewSlider = new QSlider(Qt::Horizontal);
	angleViewSlider->setMinimum(0);
	angleViewSlider->setMaximum(360);
	zoomSlider->setMinimum(10);
	zoomSlider->setMaximum(95);

	//create new row hlayouts in new controls box
	QHBoxLayout *QHLayout = new QHBoxLayout;
	QHBoxLayout *rotateLayout = new QHBoxLayout;

	// add zoom components to first layout
	QHLayout->addWidget(zoomLbl);
	QHLayout->addWidget(zoomSlider);

	//add rotation components to second layout
	rotateLayout->addWidget(rotateLbl);
	rotateLayout->addWidget(angleViewSlider);

	//add row hlayouts to main controls layout
	controls2->addLayout(QHLayout);
	controls2->addLayout(rotateLayout);


	// Create timer
	otimer = new QTimer(this);
	//Set timer to timeout every 10 milliseconds
	otimer->start(10);
	//connect timer to mainwidget to update refresh rate
	connect(otimer, SIGNAL(timeout()),  egyptWidget, SLOT(updateAngle()) );



	//connect slider signals to corresponding slots
	connect(angleViewSlider, SIGNAL(valueChanged(int)), egyptWidget, SLOT(angleView(int)));
	connect(zoomSlider, SIGNAL(valueChanged(int)), egyptWidget, SLOT(updateZoom(int)));
	connect(alienHeightSlider, SIGNAL(valueChanged(int)), egyptWidget, SLOT(updateAlienHeight(int)));
	connect(alienSizeSlider, SIGNAL(valueChanged(int)), egyptWidget, SLOT(updateAlienRadius(int)));
	connect(alienRtRadiusSlider, SIGNAL(valueChanged(int)), egyptWidget, SLOT(updateAlienRotationRadius(int)));

	//connect QLineEdits to corresponding Slots
	connect(spinValue,SIGNAL(textChanged(const QString &)),egyptWidget,SLOT(updateAlienSpinSpeed(const QString &)));
	connect(rotateValue,SIGNAL(textChanged(const QString &)),egyptWidget,SLOT(updateAlienRotationSpeed(const QString &)));

	//Connect buttons to corresponding slots
	connect(lightbtn,SIGNAL(clicked()),egyptWidget,SLOT(lightsOn()));
	connect(darkbtn,SIGNAL(clicked()),egyptWidget,SLOT(lightsOff()));
	connect(abductbtn,SIGNAL(clicked()),egyptWidget,SLOT(alienAbduct()));

	//connect comboboxes to corresponding slots
	connect(armJointBox,SIGNAL(currentTextChanged(const QString &)),egyptWidget,SLOT(updateArmJointProperties(const QString &)));
	connect(armJointBox2,SIGNAL(currentTextChanged(const QString &)),egyptWidget,SLOT(updateArmJointSphereProperties(const QString &)));
	connect(armJointBox3,SIGNAL(currentTextChanged(const QString &)),egyptWidget,SLOT(updateAlienProperties(const QString &)));
	connect(armJointBox4,SIGNAL(currentTextChanged(const QString &)),egyptWidget,SLOT(updateDiscProperties(const QString &)));
	connect(armJointBox5,SIGNAL(currentTextChanged(const QString &)),egyptWidget,SLOT(updateGateProperties(const QString &)));


	} // constructor

EgyptWindow::~EgyptWindow()
	{ // destructor
	delete zoomSlider;
	delete egyptWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void EgyptWindow::ResetInterface()
	{ // ResetInterface()

	angleViewSlider->setMinimum(0);
	angleViewSlider->setMaximum(360);


	// now force refresh
	egyptWidget->update();
	update();
	} // ResetInterface()
