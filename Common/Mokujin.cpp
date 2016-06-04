#include "Mokujin.h"

using namespace std;

Mokujin::Mokujin(TP01 *win):Object3D{}
{
    if (!this->m_loader.Load("../release/Mokujin/mokujin_squelette_bound.fbx"))
    {
        std::cout << "NOT Good!" << std::endl;
    }
    else {
        std::cout << "MOKUJIN Loaded" << std::endl;
    }

    this->window = win;
    this->m_loader.getBufferData(&vertices, &normals, &indices);

    std::cout << "Size vertices array : " << this->vertices->size() << std::endl;

    std::cout << "Size normals array : " << this->normals->size() << std::endl;

    std::cout << "Size indices array : " << this->indices->size() << std::endl;
    const QSharedPointer<Mesh> *tabMeshes = this->m_loader.m_meshes.constData();
    int nbMeshes = this->m_loader.m_meshes.size();

    /*for (int i=0; i<nbMeshes; i++) {

        std::cout << "Mesh numero " << i << " : " << tabMeshes[i].data()->name.toStdString() << ", Indexes : " << tabMeshes[i].data()->indexCount << " " << tabMeshes[i].data()->indexOffset << std::endl;
        //this->drawMesh(tabMeshes[i]);
        //qDebug()<<tabMeshes[i].data()->m_indices;
        //QThread::sleep(1000);
    }
    cout << "Name mesh : " << tabMeshes[3].data()->name.toStdString() << endl;
    */

    Node& rootNode = *(this->m_loader.m_rootNode.data());

    QVector<Node> *tabNodes = new QVector<Node>();

    buildNodeList(rootNode,tabNodes);

    /*for (int i=0; i<tabNodes->size(); i++) {

        std::cout << "Node numero " << i << " : " << tabNodes->at(i).name.toStdString() << std::endl;
    }*/
}


void Mokujin::drawNode(const Node &node)
{



   // cout << "-------- DEBUGG NODE ---------" << endl;

    m_Framework->pushMatrix();
this->m_Framework->createTexture("../release/texture/tex2d_wood-textures-2.jpg");

  //  cout << "-------- DEBUGG NODE apres PUSH ---------" << endl;

    this->m_Framework->applyMatrix(node.transformation);

    if(node.name.toStdString()=="Bone.018") {
        this->m_Framework->applyMatrix(QMatrix4x4(cos(3.14159/3),-sin(3.14159/3),0,0,sin(3.14159/3),cos(3.14159/3),0,0,0,0,1,0,0,0,0,1));
    }


    m_Framework->computeAncillaryMatrices();
    GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
    m_Framework->transmitMVP( var_id );


//    cout << "-------- DEBUGG ---------" << endl;

  //  cout << "-------- DEBUGG NODE apres APPLY ---------" << endl;

  //  cout << "MESH SIZE : " << root.nbMeshes << endl;

    if(!node.meshes.empty()) {
    //    cout << "-------- DEBUGG NODE lance MESH ---------" << endl;
        for (int i=0; i<node.meshes.size(); i++) {
            this->drawMesh(node.meshes.at(i).data());
        }
    }
    else {
       // cout << "-------- DEBUGG NODE ne lance pas MESH ---------" << endl;
    }



    if(!node.nodes.empty()) {
        for(int i=0; i<node.nodes.size(); i++) {

         //   cout << "-------- DEBUGG NODE lance NODE ---------" << endl;
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
    glDrawElements( GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, mesh->m_indices.data() );

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
