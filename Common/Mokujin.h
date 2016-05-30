#ifndef MOKUJIN_H
#define MOKUJIN_H

#include "Shapes/Shape.h"
#include "ModelLoader.h"


class Mokujin : public Shape
{
public:
    Mokujin();
protected:
    void drawShape( const char* shader_name );
    void drawNode(const QMatrix4x4& model, const Node *node, QMatrix4x4 parent);
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

};

#endif // MOKUJIN_H
