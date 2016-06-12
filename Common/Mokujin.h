#ifndef MOKUJIN_H
#define MOKUJIN_H

#include "Shapes/Shape.h"
#include "ModelLoader.h"
#include <iostream>
#include <qthread.h>
#include <Texture.h>
#include "GlWindow.h"
#include "MainWindow.h"

class Mokujin : public Object3D
{
public:
    Mokujin();
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
    void animation1(const Node &node);

    //Rotation du buste
    void animation2(const Node &node);

    //Saut groupé
    void animation3(const Node &node);

    //Grand écart
    void animation4(const Node &node);



protected:
    ModelLoader              m_loader;
    QMatrix4x4 m_projection, m_view;
    GLsizei                  m_cnt;

    QVector<float> *vertices;
    QVector<float> *normals;
    QVector<unsigned int> *indices;
    QSharedPointer<Node> m_rootNode;

    Texture *wood;
    Texture *metal;
    Texture *eye;
    Texture *nose;

};

#endif // MOKUJIN_H
