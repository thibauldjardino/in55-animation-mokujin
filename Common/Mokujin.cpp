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

    this->nbFrames = 60;
    this->currentAnimation = "";
    this->currentTime = -1;
    this->timeStep = 1/(1.0f*this->nbFrames);

    this->window = win;
    this->m_loader.getBufferData(&vertices, &normals, &indices);

    std::cout << "Size vertices array : " << this->vertices->size() << std::endl;

    std::cout << "Size normals array : " << this->normals->size() << std::endl;

    std::cout << "Size indices array : " << this->indices->size() << std::endl;
    const QSharedPointer<Mesh> *tabMeshes = this->m_loader.m_meshes.constData();
    int nbMeshes = this->m_loader.m_meshes.size();

    //for (int i=0; i<nbMeshes; i++) {

        //std::cout << "Mesh numero " << i << " : " << tabMeshes[i].data()->name.toStdString() << ", Indexes : " << tabMeshes[i].data()->indexCount << " " << tabMeshes[i].data()->indexOffset << std::endl;
        //this->drawMesh(tabMeshes[i]);
        //qDebug()<<tabMeshes[i].data()->m_indices;
        //QThread::sleep(1000);
   // }
    //cout << "Name mesh : " << tabMeshes[3].data()->name.toStdString() << endl;


    Node& rootNode = *(this->m_loader.m_rootNode.data());

    QVector<Node> *tabNodes = new QVector<Node>();

    buildNodeList(rootNode,tabNodes);

    /*for (int i=0; i<tabNodes->size(); i++) {

        std::cout << "Node numero " << i << " : " << tabNodes->at(i).name.toStdString() << std::endl;
    }*/
}


void Mokujin::drawNode(const Node &node)
{

    this->m_Framework->createTexture("");

   // cout << "-------- DEBUGG NODE ---------" << endl;

    m_Framework->pushMatrix();

  //  cout << "-------- DEBUGG NODE apres PUSH ---------" << endl;

    this->m_Framework->applyMatrix(node.transformation);

    if(this->currentAnimation=="2") {
        this->animation2(node);
    } else if(this->currentAnimation=="4") {
        this->animation4(node);
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
          // qDebug() << node.meshes.at(i).data()->name;
           //QThread::sleep(1);
           if(!strcmp(node.meshes.at(i).data()->name.toStdString().c_str(), "Sphere.022")){
               this->m_Framework->createTexture("../release/texture/tex2d_wood-textures-2.jpg");
           }else if (!strcmp(node.meshes.at(i).data()->name.toStdString().c_str(), "Cylinder.006")){
               this->m_Framework->createTexture("../release/texture/metal-textures.jpg");
           }

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

void Mokujin::animation2(const Node &node) {

   if(node.name.toStdString()=="Armature") {
        this->m_Framework->rotate(360*this->currentTime,0,0,1);
   }

}

//Grand écart
void Mokujin::animation4(const Node &node) {

    //Tout le corps
    if(node.name.toStdString()=="Armature") {
        this->m_Framework->translate(0,0,this->currentTime*6);
    }
    //Jambe gauche
    else if(node.name.toStdString()=="Bone.003") {
        this->m_Framework->translate(0,this->currentTime/2.0,this->currentTime*2.4);
        this->m_Framework->rotate(-this->currentTime*75,1,0,0);
    }
    //Jambe droite
    else if(node.name.toStdString()=="Bone.002") {
        this->m_Framework->translate(0,-this->currentTime/2.0,this->currentTime*2.4);
        this->m_Framework->rotate(-this->currentTime*75,1,0,0);
    }
    //Pied droit
    else if(node.name.toStdString()=="Bone.012") {
        this->m_Framework->rotate(-this->currentTime*90,0,0.258819,0.965929);
    }
    //Pied gauche
    else if(node.name.toStdString()=="Bone.015") {
        this->m_Framework->rotate(this->currentTime*90,0,0.258819,0.965929);
    }
    //Bras droit
    else if(node.name.toStdString()=="Bone.020") {

        QMatrix4x4 inverse = node.transformation.inverted();

        this->m_Framework->applyMatrix(inverse);

        this->m_Framework->rotate(-this->currentTime*100,0,1,0);
        this->m_Framework->rotate(-this->currentTime*30,0,0,1);
        this->m_Framework->translate(-this->currentTime*5.3,-this->currentTime*0.9,-this->currentTime*2.5);
        this->m_Framework->applyMatrix(node.transformation);

    }
    //Bras gauche
    else if(node.name.toStdString()=="Bone.017") {
        QMatrix4x4 inverse = node.transformation.inverted();

        this->m_Framework->applyMatrix(inverse);

        this->m_Framework->rotate(this->currentTime*100,0,1,0);
        this->m_Framework->translate(this->currentTime*3.5,0,-this->currentTime*2.5);
        this->m_Framework->applyMatrix(node.transformation);
    }
    //Main droite
    else if(node.name.toStdString()=="Bone.022") {

        QMatrix4x4 inverse = node.transformation.inverted();

        this->m_Framework->applyMatrix(inverse);

        this->m_Framework->rotate(-this->currentTime*70,1,0,0);
        this->m_Framework->translate(this->currentTime*0.0,-this->currentTime*2.4,this->currentTime*3);
        this->m_Framework->applyMatrix(node.transformation);

    }
    //Main gauche
    else if(node.name.toStdString()=="Bone.019") {

        QMatrix4x4 inverse = node.transformation.inverted();

        this->m_Framework->applyMatrix(inverse);

        this->m_Framework->rotate(-this->currentTime*70,1,0,0);
        this->m_Framework->translate(this->currentTime*0.0,-this->currentTime*2.4,this->currentTime*3);
        this->m_Framework->applyMatrix(node.transformation);

    }



}
