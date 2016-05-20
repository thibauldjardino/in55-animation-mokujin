#include "TP01.h"


#include "Shapes/Basis.h"
#include "Shapes/Cubes.h"
#include "Shapes/Pyramid.h"
#include "Shapes/Cylinder.h"
#include "Shapes/Star.h"
#include "Camera.h"
#include <iostream>

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;
GLfloat translate1 = 0.0f;
GLfloat translate2 = 0.0f;
GLfloat translate3 = 0.0f;

const GLfloat g_AngleSpeed = 10.0f;
const GLfloat g_TranslationSpeed = 1.0f;

Basis* basis;
Pyramid* pyr;
Cylinder* cyl;
Star* star;
MultipleColorCube* cube;
Camera *camera;

TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));

    basis = new Basis( 10.0 );
    star = new Star( 6, 1.0, 1.4, 1.0 );
    pyr = new Pyramid( 5, 2.0, 10.0 );
    cyl = new Cylinder( 32, 1.5, 0.0, 10.0 );
    cube = new MultipleColorCube();
    camera = new Camera();
}


TP01::~TP01()
{
    delete basis;
    delete star;
    delete pyr;
    delete cyl;
    delete cube;
    delete camera;
}


bool
TP01::initializeObjects()
{
	// Fond gris
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable( GL_DEPTH_TEST );

	// Chargement des shaders
	createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

	return true;
}


void
TP01::render()
{
	// Initialisation de la caméra
    lookAt(camera->m_position->x, camera->m_position->y, camera->m_position->z, camera->m_orientation->x, camera->m_orientation->y, camera->m_orientation->z );


	// Rendu des objets
	pushMatrix();
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 1, 0, 0 );
        translate(translate1,translate2,translate3);

        basis->draw();

        pushMatrix();
        translate( -10.0, 0, 0 );
        star->draw();
        popMatrix();

        pushMatrix();
        translate( 10.0, 0, 0 );
        pyr->draw();
        popMatrix();

        pushMatrix();
        translate( -5.0, 0, 0 );
        cyl->draw();
        popMatrix();

        pushMatrix();
        translate( 5.0, 0, 0 );
        cube->draw();
        popMatrix();
    popMatrix();
}


void
TP01::keyPressEvent( QKeyEvent* event )
{
	switch( event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

		case Qt::Key_Left:
            camera->translateX(g_TranslationSpeed);
            translate1 += g_TranslationSpeed;
//			angle1 -= g_AngleSpeed;
			break;

		case Qt::Key_Right:
        camera->translateX(-g_TranslationSpeed);
        translate1 -= g_TranslationSpeed;
//			angle1 += g_AngleSpeed;
			break;

		case Qt::Key_Up:
        camera->translateY(g_TranslationSpeed);
        translate3 += g_TranslationSpeed;
//			angle2 -= g_AngleSpeed;
			break;

		case Qt::Key_Down:
        camera->translateY(-g_TranslationSpeed);
        translate3 -= g_TranslationSpeed;
//			angle2 += g_AngleSpeed;
			break;

		case Qt::Key_R:
//			angle1 = angle2 = 0.0f;
			break;
	}
}
