#include "Mokujin.h"
#include <iostream>
#include <qthread.h>
using namespace std;

Mokujin::Mokujin():Shape{}
{
    if (!this->m_loader.Load("../release/Mokujin/mokujin_squelette_bound.dae"))
    {
        std::cout << "NOT Good!" << std::endl;
    }
    else {
        std::cout << "MOKUJIN Loaded" << std::endl;
    }

    this->m_loader.getBufferData(&vertices, &normals, &indices);

    std::cout << "Size vertices array : " << this->vertices->size() << std::endl;

    std::cout << "Size normals array : " << this->normals->size() << std::endl;

    std::cout << "Size indices array : " << this->indices->size() << std::endl;
    const QSharedPointer<Mesh> *tabMeshes = this->m_loader.m_meshes.constData();
    int nbMeshes = this->m_loader.m_meshes.size();

    for (int i=0; i<nbMeshes; i++) {

        std::cout << "Mesh numero " << i << " : " << tabMeshes[i].data()->name.toStdString() << ", Indexes : " << tabMeshes[i].data()->indexCount << " " << tabMeshes[i].data()->indexOffset << std::endl;
        //this->drawMesh(tabMeshes[i]);
        //qDebug()<<tabMeshes[i].data()->m_indices;
        //QThread::sleep(1000);
    }
    cout << "Name mesh : " << tabMeshes[3].data()->name.toStdString() << endl;


    Node& rootNode = *(this->m_loader.m_rootNode.data());

    QVector<Node> *tabNodes = new QVector<Node>();

    buildNodeList(rootNode,tabNodes);

    /*for (int i=0; i<tabNodes->size(); i++) {

        std::cout << "Node numero " << i << " : " << tabNodes->at(i).name.toStdString() << std::endl;
    }*/
}


void Mokujin::drawNode(const QMatrix4x4& model, const Node *node, QMatrix4x4 parent)
{
    // Prepare matrices
    QMatrix4x4 local = parent * node->transformation;

    // Draw each mesh in this node
    for(int i = 0;
        i<this->m_loader.m_meshes.size()
        ; ++i)
    {
        Mesh* m = node->meshes[i].data();
        this->drawMesh(m);
    }

    // Recursively draw this nodes children nodes
    for(int i = 0; i < node->nodes.size(); ++i)
        drawNode(model, &node->nodes[i], local);
}

void Mokujin::drawShape( const char* shader_name )
{

    const QSharedPointer<Mesh> *tabMeshes = this->m_loader.m_meshes.constData();
    int nbMeshes = this->m_loader.m_meshes.size();

//    this->drawNode(this->m_rootNode.data()->transformation,this->m_rootNode.data(),NULL);

    for (int i=0; i<nbMeshes; i++) {
        this->drawMesh(tabMeshes[i].data());
    }

}

void Mokujin::drawMesh( const Mesh *mesh) {

    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mesh->m_vertices.data() );
    glDrawElements( GL_LINES, mesh->m_indices.size(), GL_UNSIGNED_INT, mesh->m_indices.data() );

    glDisableVertexAttribArray( 0 );
}


void Mokujin::buildNodeList (const Node & root, QVector<Node> *list) {

    list->append(root);
    if(!root.nodes.empty()) {
        for(int i=0; i<root.nodes.size(); i++) {
            this->buildNodeList (root.nodes.at(i), list);
        }
    }

   /* for(int i=0; i<root.nodes.size(); i++) {
        std::cout << "Nom : " <<root.nodes.at(i).name.toStdString() << std::endl;
        buildNodeList(root.nodes.at(i));
    }*/
}
