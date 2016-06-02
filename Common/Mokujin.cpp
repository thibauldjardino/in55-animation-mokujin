#include "Mokujin.h"
#include <iostream>
#include <qthread.h>
Mokujin::Mokujin():Shape{}
{
    if (!this->m_loader.Load("../release/Mokujin/mokujin_squelette_bound.fbx"))
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

    for (int i=1; i<nbMeshes; i++) {

        std::cout << "Mesh numero " << i << " : " << tabMeshes[i].data()->name.toStdString() << ", Indexes : " << tabMeshes[i].data()->indexCount << " " << tabMeshes[i].data()->indexOffset << std::endl;
        qDebug()<<tabMeshes[i].data()->m_indices;
        QThread::sleep(1000);
    }

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
        const Mesh& m = *node->meshes[i];
        qDebug()<<m.indexCount;
        qDebug()<<m.indexOffset;
        qDebug()<<"passe";
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glDrawElements(GL_TRIANGLES, m.indexCount, GL_UNSIGNED_INT, (const GLvoid*)(m.indexOffset * sizeof(GLuint)));
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
    }

    // Recursively draw this nodes children nodes
    for(int i = 0; i < node->nodes.size(); ++i)
        drawNode(model, &node->nodes[i], local);
}

void Mokujin::drawShape( const char* shader_name )
{

    // A RETRAVAILLER POUR AFFICHER TOUS LES MESHES
   /*


    QMatrix4x4 *model = new QMatrix4x4();
    this->drawNode(*model,,*model);*/

    const GLfloat *tabVertices = this->vertices->constData();

    const GLuint *tabIndices = this->indices->constData();

    /*for (int i=0; i<this->indices->size(); i+=3) {

        std::cout << tab2[i] << " " << tab2[i+1] << " " << tab2[i+2] << std::endl;
    }*/

    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, tabVertices );
    glDrawElements( GL_LINES, this->indices->size(), GL_UNSIGNED_INT, tabIndices );

    glDisableVertexAttribArray( 0 );

    /*GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, tab );
    glDrawElements( GL_TRIANGLES, 150, GL_UNSIGNED_INT, this->indices->data() );
    glDisableVertexAttribArray( var1 );*/
}

void Mokujin::drawMesh( const Mesh *mesh) {

    //TODO
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
