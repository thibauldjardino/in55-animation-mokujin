#ifndef MOKUJIN_H
#define MOKUJIN_H

#include "Shapes/Shape.h"
#include "ModelLoader.h"
#include <iostream>
#include <qthread.h>
#include "GlWindow.h"
#include "TP01.h"

class Mokujin : public Object3D
{
public:
    Mokujin(TP01 *win);
    std::string currentAnimation;
    float currentTime;
    float timeStep;
    unsigned int nbFrames;

protected:
    void drawShape( const char* shader_name );
    void drawNode(const Node &node);
    void drawMesh(const Mesh *mesh);

    void buildNodeList (const Node &root, QVector<Node> *list);

    //Marche
    QMatrix4x4 animation1(const Node &node);

    //Rotation du buste
    QMatrix4x4 animation2(const Node &node);


    QMatrix4x4 animation3(const Node &node);


    QMatrix4x4 animation4(const Node &node);



protected:
    ModelLoader              m_loader;
    QMatrix4x4 m_projection, m_view;
    GLsizei                  m_cnt;

    QVector<float> *vertices;
    QVector<float> *normals;
    QVector<unsigned int> *indices;
    QSharedPointer<Node> m_rootNode;
    TP01 *window;



};

#endif // MOKUJIN_H
