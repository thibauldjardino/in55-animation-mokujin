#include "TP01.h"

#include "ModelLoader.h"

#include "Shapes/Basis.h"
#include "Shapes/Cubes.h"
#include "Shapes/Pyramid.h"
#include "Shapes/Cylinder.h"
#include "Shapes/Star.h"
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
Pyramid* pyr;
Cylinder* cyl;
Star* star;
MultipleColorCube* cube;
Camera *camera;
Mokujin *mokujin;

TP01::TP01()
{
    setWindowTitle(trUtf8("IN55-TP01"));

    basis = new Basis( 10.0 );
    star = new Star( 6, 1.0, 1.4, 1.0 );
    pyr = new Pyramid( 5, 2.0, 10.0 );
    cyl = new Cylinder( 32, 1.5, 0.0, 10.0 );
    cube = new MultipleColorCube();
    camera = new Camera(15,15,15);

    mokujin = new Mokujin(this);
    mokujin->setFramework(this);
    std::cout << camera->m_forwardOrientation->w << " " << camera->m_forwardOrientation->x << " " << camera->m_forwardOrientation->y << " " << camera->m_forwardOrientation->z << " " << std::endl;
}


TP01::~TP01()
{
    delete basis;
    delete star;
    delete pyr;
    delete cyl;
    delete cube;
    delete camera;
    delete mokujin;
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


    /*ModelLoader model;

        if (!model.Load("../release/Mokujin/mokujin_squelette_bound.dae"))
        {
            cout << "NOT Good!" << endl;
        }

        QVector<float> *vertices;
        QVector<float> *normals;
        QVector<unsigned int> *indices;

        model.getBufferData(&vertices, &normals, &indices);

        QSharedPointer<Node> m_rootNode = model.getNodeData();


        //std::cout << m_rootNode.data()->name.toStdString() << std::endl;
        //std::cout << m_rootNode.data()->transformation. << std::endl;
        //()<<m_rootNode.data()->transformation;
        //qDebug()<<m_rootNode.data()->nodes;


    */
    return true;
}


void
TP01::render()
{


    // Initialisation de la caméra
    lookAt(camera->m_position->x, camera->m_position->y, camera->m_position->z, camera->m_forwardOrientation->x+camera->m_position->x, camera->m_forwardOrientation->y+camera->m_position->y, camera->m_forwardOrientation->z+camera->m_position->z, camera->m_upOrientation->x, camera->m_upOrientation->y, camera->m_upOrientation->z );


    // Rendu des objets
    pushMatrix();
    rotate( angle1, 0, 1, 0 );
    rotate( angle2, 1, 0, 0 );


    basis->draw();

    pushMatrix();
    //this->applyMatrix(QMatrix4x4(1,0,0,2,0,1,0,2,0,0,1,2,0,0,0,1));
        //star->draw();
    //translate(2,2,2);
    scale(0.005,0.005,0.005);
    mokujin->draw();
    popMatrix();
    popMatrix();
    /*pushMatrix();
    translate( -10.0, 0, 0 );

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
    popMatrix();*/

    if(mokujin->currentTime>=0 && mokujin->currentTime<1 && mokujin->currentAnimation.length()!=0) {
        mokujin->currentTime+=mokujin->timeStep;
    }
    else if(mokujin->currentTime>1) {
        mokujin->currentTime = 0;
    }

}


void
TP01::keyPressEvent( QKeyEvent* event )
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

    case Qt::Key_R:
        //			angle1 = angle2 = 0.0f;
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
        mokujin->currentAnimation="";
        mokujin->currentTime=-1;
        break;

    case Qt::Key_1:
        //Marche
        mokujin->currentAnimation=1;
        break;

    case Qt::Key_2:
        //Rotation du buste
        mokujin->currentAnimation=2;
        break;

    case Qt::Key_3:
        mokujin->currentAnimation=3;
        break;

    case Qt::Key_4:
        mokujin->currentAnimation=4;
        break;
    }
}
