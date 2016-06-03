#include "Mokujin.h"

using namespace std;

Mokujin::Mokujin():Object3D{}
{
    if (!this->m_loader.Load("../release/Mokujin/mokujin_squelette_bound.fbx"))
    {
        std::cout << "NOT Good!" << std::endl;
    }
    else {
        std::cout << "MOKUJIN Loaded" << std::endl;
    }

    this->m_loader.getBufferData(&vertices, &normals, &indices);

}


void Mokujin::drawNode(const Node &node)
{

    m_Framework->pushMatrix();

    this->m_Framework->applyMatrix(node.transformation);

    m_Framework->computeAncillaryMatrices();
    GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
    m_Framework->transmitMVP( var_id );

    if(!node.meshes.empty()) {
        for (int i=0; i<node.meshes.size(); i++) {
            this->drawMesh(node.meshes.at(i).data());
        }
    }

    if(!node.nodes.empty()) {
        for(int i=0; i<node.nodes.size(); i++) {
            this->drawNode(node.nodes.at(i));
        }
    }

    m_Framework->popMatrix();
}

void Mokujin::drawShape( const char* shader_name )
{

    Node& rootNode = *(this->m_loader.m_rootNode.data());

    QVector<Node> *tabNodes = new QVector<Node>();

    buildNodeList(rootNode,tabNodes);

    this->drawNode(tabNodes->at(0));

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
}
