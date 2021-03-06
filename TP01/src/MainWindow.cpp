﻿#include "MainWindow.h"

#include "ModelLoader.h"

#include "Shapes/Basis.h"
#include "Camera.h"
#include "Quaternion.h"
#include <iostream>

#include "Mokujin.h"

using namespace std;


GLfloat angle1 = 30.0f;
GLfloat angle2 = 20.0f;
GLfloat translate1 = 0.0f;
GLfloat translate2 = 0.0f;
GLfloat translate3 = 0.0f;

const GLfloat g_AngleSpeed = 0.05f;
const GLfloat g_TranslationSpeed = 0.5f;

Basis* basis;
Camera *camera;
Mokujin *mokujin;

MainWindow::MainWindow()
{
    setWindowTitle(trUtf8("IN55-TP01"));

    basis = new Basis( 10.0 );
    camera = new Camera(10,10,10,0,3,0);

    mokujin = new Mokujin();

}


MainWindow::~MainWindow()
{
    delete basis;
    delete camera;
    delete mokujin;
}


bool
MainWindow::initializeObjects()
{
    // Fond gris
    glClearColor( 0.3f, 0.3f, 0.6f, 1.0f );
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
MainWindow::render()
{


    // Initialisation de la caméra
    lookAt(camera->m_position->x, camera->m_position->y, camera->m_position->z, camera->m_forwardOrientation->x+camera->m_position->x, camera->m_forwardOrientation->y+camera->m_position->y, camera->m_forwardOrientation->z+camera->m_position->z, camera->m_upOrientation->x, camera->m_upOrientation->y, camera->m_upOrientation->z );


    // Rendu des objets
    pushMatrix();
    rotate( angle1, 0, 1, 0 );
    rotate( angle2, 1, 0, 0 );


    basis->draw();

    pushMatrix();

    scale(0.005,0.005,0.005);
    mokujin->draw();
    popMatrix();
    popMatrix();


    if(mokujin->currentAnimation!="" && mokujin->currentTime<1)
    {
        mokujin->currentTime+=mokujin->timeStep;
    }

}


void
MainWindow::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
    case Qt::Key_Escape:
        close();
        break;

    case Qt::Key_Q:
        camera->translateX(g_TranslationSpeed);
        break;

    case Qt::Key_D:
        camera->translateX(-g_TranslationSpeed);

        break;

    case Qt::Key_Z:
        camera->translateY(g_TranslationSpeed);
        break;

    case Qt::Key_S:
        camera->translateY(-g_TranslationSpeed);
        break;

    case Qt::Key_A:
        camera->translateZ(g_TranslationSpeed);
        break;

    case Qt::Key_E:
        camera->translateZ(-g_TranslationSpeed);
        break;

    case Qt::Key_O:
        camera->rotateX(-g_AngleSpeed);
        break;

    case Qt::Key_L:
        camera->rotateX(g_AngleSpeed);
        break;

    case Qt::Key_K:
        camera->rotateY(g_AngleSpeed);
        break;

    case Qt::Key_M:
        camera->rotateY(-g_AngleSpeed);
        break;

    case Qt::Key_I:
        camera->rotateZ(-g_AngleSpeed);
        break;

    case Qt::Key_P:
        camera->rotateZ(g_AngleSpeed);
        break;

    case Qt::Key_0:
        mokujin->nbFrames = 60;
        mokujin->timeStep = 1/(1.0f*mokujin->nbFrames);
        mokujin->currentAnimation="";
        mokujin->currentTime=-1;
        break;

    case Qt::Key_1:
        //Marche
        mokujin->nbFrames = 60;
        mokujin->timeStep = 1/(1.0f*mokujin->nbFrames);
        mokujin->currentAnimation="1";
        mokujin->currentTime=0;
        break;

    case Qt::Key_2:
        //Rotation du buste
        mokujin->nbFrames = 60;
        mokujin->timeStep = 1/(1.0f*mokujin->nbFrames);
        mokujin->currentAnimation="2";
        mokujin->currentTime=0;
        break;

        //Saut groupé
    case Qt::Key_3:
        mokujin->nbFrames = 120;
        mokujin->timeStep = 1/(1.0f*mokujin->nbFrames);
        mokujin->currentAnimation="3";
        mokujin->currentTime=0;
        break;

        //Grand écart plus mains en garde
    case Qt::Key_4:
        mokujin->nbFrames = 60;
        mokujin->timeStep = 1/(1.0f*mokujin->nbFrames);
        mokujin->currentAnimation="4";
        mokujin->currentTime=0;
        break;
    }
}
