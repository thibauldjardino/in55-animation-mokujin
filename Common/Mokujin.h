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
protected:
    void drawShape( const char* shader_name );
    void drawNode(const Node &node);
    void drawMesh(const Mesh *mesh);

    void buildNodeList (const Node &root, QVector<Node> *list);

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
