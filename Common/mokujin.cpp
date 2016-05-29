#include "mokujin.h"
#include <iostream>
Mokujin::Mokujin():ParametricShape{168268}
{
    if (!this->m_loader.Load("C:/Users/Tiboty/Documents/GitHub/in55-animation-mokujin/TP01/release/Mokujin/mokujin_squelette_bound.dae"))
    {
        std::cout << "NOT Good!" << std::endl;
    }

    this->m_loader.getBufferData(&vertices, &normals, &indices);

    this->m_rootNode = this->m_loader.getNodeData();
    //qDebug()<<this->vertices->size()/3;
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
        QMatrix4x4 model;
        model.translate(-0.2f, 0.0f, .5f);
        model.rotate(55.0f, 0.0f, 1.0f, 0.0f);

        drawNode(model, this->m_loader.getNodeData().data(), QMatrix4x4());
    }
