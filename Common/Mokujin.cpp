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

    wood = new Texture();
       wood->loadSOIL("../release/texture/ecorse-textures.jpg");

       metal = new Texture();
       metal->load("../release/texture/metal-textures.jpg");

       eye = new Texture();
       eye->load("../release/texture/yeux-textures.jpg");


       nose = new Texture();
       nose->load("../release/texture/nez-textures.jpg");


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



    if(this->currentAnimation=="1") {
        this->animation1(node);
    } else if(this->currentAnimation=="2") {
        this->animation2(node);
    } else if(this->currentAnimation=="3") {
        this->animation3(node);
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

    this->drawNode(*(this->m_loader.m_rootNode.data()));

}

void Mokujin::drawMesh( const Mesh *mesh) {

    QVector<unsigned int> tmp;
        if(!strcmp(mesh->name.toStdString().c_str(), "Cylinder.025") || !strcmp(mesh->name.toStdString().c_str(), "Cylinder.028")
            ||!strcmp(mesh->name.toStdString().c_str(), "Sphere.006") || !strcmp(mesh->name.toStdString().c_str(), "Sphere.007")){

            //this->m_Framework->createTexture("wood");

            glEnableVertexAttribArray( 0 );

            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mesh->m_vertices.data() );
            //glDrawElements( GL_TRIANGLES, 588, GL_UNSIGNED_INT, mesh->m_indices.data() );

            wood->drawShape(588, mesh->m_indices.data());



            for(int i =588;i<mesh->m_indices.size();i++){
                tmp.push_back(mesh->m_indices[i]);
            }


            //this->m_Framework->createTexture("metal");


            //glDrawElements( GL_TRIANGLES, tmp.size(), GL_UNSIGNED_INT, tmp.data() );
            metal->drawShape(tmp.size(), tmp.data());

            glDisableVertexAttribArray( 0 );


        }else if(!strcmp(mesh->name.toStdString().c_str(), "Sphere.023")|| !strcmp(mesh->name.toStdString().c_str(), "Sphere.022")
                 ||!strcmp(mesh->name.toStdString().c_str(), "Sphere.002") || !strcmp(mesh->name.toStdString().c_str(), "Sphere.003")
                 ){

            //this->m_Framework->createTexture("metal");

            glEnableVertexAttribArray( 0 );

            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mesh->m_vertices.data() );
            //glDrawElements( GL_TRIANGLES, 14702, GL_UNSIGNED_INT, mesh->m_indices.data() );
            metal->drawShape(14702,  mesh->m_indices.data());

            for(int i =14701;i<mesh->m_indices.size();i++){
                tmp.push_back(mesh->m_indices[i]);
            }

            //this->m_Framework->createTexture("wood");


            //glDrawElements( GL_TRIANGLES, tmp.size(), GL_UNSIGNED_INT, tmp.data() );
             wood->drawShape(tmp.size(), tmp.data());
            glDisableVertexAttribArray( 0 );


        }
        else if(!strcmp(mesh->name.toStdString().c_str(), "Cylinder.006")||!strcmp(mesh->name.toStdString().c_str(), "Cylinder.005") ){

                this->m_Framework->createTexture("wood");

                glEnableVertexAttribArray( 0 );

                glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mesh->m_vertices.data() );
                //glDrawElements( GL_TRIANGLES,  mesh->m_indices.size(), GL_UNSIGNED_INT, mesh->m_indices.data() );
                wood->drawShape( mesh->m_indices.size(), mesh->m_indices.data());
                glDisableVertexAttribArray( 0 );


            }
        else if(!strcmp(mesh->name.toStdString().c_str(), "Sphere.013")){

                QVector<unsigned int> tmp2;
                int corps;

                //this->m_Framework->createTexture("metal");

                glEnableVertexAttribArray( 0 );

                glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mesh->m_vertices.data() );
                //glDrawElements( GL_TRIANGLES,  4*14700, GL_UNSIGNED_INT, mesh->m_indices.data() );
                metal->drawShape( 4*14700, mesh->m_indices.data());

                //this->m_Framework->createTexture("wood");
                corps = 4*14700;
                for(int i =corps;i<(corps + 588);i++){
                    tmp.push_back(mesh->m_indices[i]);
                }

                //glDrawElements( GL_TRIANGLES, tmp.size(), GL_UNSIGNED_INT, tmp.data() );
                wood->drawShape( tmp.size(), tmp.data());

               // this->m_Framework->createTexture("metal");

              for(int i =corps + 588;i<mesh->m_indices.size();i++){
                    tmp2.push_back(mesh->m_indices[i]);
                }

               // glDrawElements( GL_TRIANGLES, tmp2.size(), GL_UNSIGNED_INT, tmp2.data() );
                metal->drawShape( tmp2.size(), tmp2.data());
                glDisableVertexAttribArray( 0 );


                tmp2.clear();
            }
        else if(!strcmp(mesh->name.toStdString().c_str(), "Cone.005")){


            //this->m_Framework->createTexture("metal");

            glEnableVertexAttribArray( 0 );

            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mesh->m_vertices.data() );
            //glDrawElements( GL_TRIANGLES,  38, GL_UNSIGNED_INT, mesh->m_indices.data() );
            metal->drawShape( 38, mesh->m_indices.data());
            //this->m_Framework->createTexture("metal");

            for(int i =39;i<332;i++){
                tmp.push_back(mesh->m_indices[i]);
            }


           //glDrawElements( GL_TRIANGLES, tmp.size(), GL_UNSIGNED_INT, tmp.data() );
           metal->drawShape( tmp.size(), tmp.data());

           tmp.clear();
           for(int i =331;i<906;i++){
               tmp.push_back(mesh->m_indices[i]);
           }

          //glDrawElements( GL_TRIANGLES, tmp.size(), GL_UNSIGNED_INT, tmp.data() );
          nose->drawShape( tmp.size(), tmp.data());
          tmp.clear();
          for(int i =905;i<30307;i++){
              tmp.push_back(mesh->m_indices[i]);
          }
          //glDrawElements( GL_TRIANGLES, tmp.size(), GL_UNSIGNED_INT, tmp.data() );
          eye->drawShape( tmp.size(), tmp.data());
          tmp.clear();
          for(int i =30306;i<mesh->m_indices.size();i++){
              tmp.push_back(mesh->m_indices[i]);
          }
           //this->m_Framework->createTexture("wood");
           //glDrawElements( GL_TRIANGLES, tmp.size(), GL_UNSIGNED_INT, tmp.data() );
           wood->drawShape( tmp.size(), tmp.data());

            glDisableVertexAttribArray( 0 );



        }

        tmp.clear();

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

//Marche
void Mokujin::animation1(const Node &node) {

    //Tout le corps
    if(node.name.toStdString()=="Armature") {
        if(this->currentTime>=0 && this->currentTime<0.5) {
            this->m_Framework->translate(0,12*this->currentTime,this->currentTime);
        } else {
            this->m_Framework->translate(0,12*this->currentTime,0.5-(this->currentTime-0.5));
        }
    }
    //Bras droit
    else if(node.name.toStdString()=="Bone.020") {
        this->m_Framework->rotate(-200,0,1,0);
        if(this->currentTime>=0 && this->currentTime<0.5) {
            this->m_Framework->rotate(-240*this->currentTime,0,1,0);


        } else {

            this->m_Framework->rotate(-120,0,1,0);
            this->m_Framework->rotate(240*(this->currentTime-0.5),0,1,0);
        }

    }
    //Bras gauche
    else if(node.name.toStdString()=="Bone.017") {
        this->m_Framework->rotate(-200,0,1,0);
        if(this->currentTime>=0 && this->currentTime<0.5) {

            this->m_Framework->rotate(120,0,1,0);
            this->m_Framework->rotate(-240*this->currentTime,0,1,0);
            // this->m_Framework->rotate(240*this->currentTime,0,1,0);
            // this->m_Framework->translate(0,-this->currentTime*5,this->currentTime*7);
        } else {

            this->m_Framework->rotate(240*(this->currentTime-0.5),0,1,0);

            /* this->m_Framework->rotate(120,1,1,1);
            this->m_Framework->translate(0,-2.5,3.5);
            this->m_Framework->translate(0,(this->currentTime-0.5)*5,-(this->currentTime-0.5)*7);
            this->m_Framework->rotate(-240*(this->currentTime-0.5),1,-1,1);*/
        }
    }
    //Jambe droite
    else if(node.name.toStdString()=="Bone.002") {
        if(this->currentTime>=0 && this->currentTime<0.5) {
            this->m_Framework->rotate(-40,0,1,0);
            this->m_Framework->rotate(100*this->currentTime,0,1,0);
        } else {
            this->m_Framework->rotate(10,0,1,0);
            this->m_Framework->rotate(-100*(this->currentTime-0.5),0,1,0);
        }

    }
    //Jambe gauche
    else if(node.name.toStdString()=="Bone.003") {

        if(this->currentTime>=0 && this->currentTime<0.5) {
            this->m_Framework->rotate(-10,0,1,0);
            this->m_Framework->rotate(100*this->currentTime,0,1,0);
        } else {
            this->m_Framework->rotate(40,0,1,0);
            this->m_Framework->rotate(-100*(this->currentTime-0.5),0,1,0);
        }
    }
    //Tibia gauche
    else if(node.name.toStdString()=="Bone.014") {
         if(this->currentTime>=0 && this->currentTime<0.5) {
             this->m_Framework->rotate(40,1,0,0);
             this->m_Framework->rotate(-60*this->currentTime,1,0,0);
         } else {
             this->m_Framework->rotate(10,1,0,0);
             this->m_Framework->rotate(60*(this->currentTime-0.5),1,0,0);
         }
    }
    //Tibia droite
    else if(node.name.toStdString()=="Bone.011") {
         if(this->currentTime>=0 && this->currentTime<0.5) {
             this->m_Framework->rotate(10,1,0,0);
             this->m_Framework->rotate(60*this->currentTime,1,0,0);
         } else {
             this->m_Framework->rotate(40,1,0,0);
             this->m_Framework->rotate(-60*(this->currentTime-0.5),1,0,0);
         }
    }

}

//Rotation du buste
void Mokujin::animation2(const Node &node) {

    if(node.name.toStdString()=="Armature") {
        this->m_Framework->rotate(360*this->currentTime,0,0,1);
    } else if(node.name.toStdString()=="Bone.001") {
        this->m_Framework->rotate(-360*this->currentTime,0,0,1);
    }

}


//Saut groupé
void Mokujin::animation3(const Node &node) {

     //Tout le corps
    if(node.name.toStdString()=="Armature") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
             this->m_Framework->translate(0,0,18*this->currentTime);
        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }

    }
    //Bras droit
    else if(node.name.toStdString()=="Bone.020") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {

        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }

    }
    //Bras gauche
    else if(node.name.toStdString()=="Bone.017") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
            this->m_Framework->translate(1*this->currentTime,1*6*this->currentTime,-3*6*this->currentTime);
            this->m_Framework->rotate(300*this->currentTime,1,0,0);

        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }
    }
    //Jambe gauche
    else if(node.name.toStdString()=="Bone.003") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
            this->m_Framework->rotate(300*this->currentTime,0,1,0);
        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }
    }
    //Jambe droite
    else if(node.name.toStdString()=="Bone.002") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
            this->m_Framework->rotate(-300*this->currentTime,0,1,0);
        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }
    }
    //Tibia gauche
    else if(node.name.toStdString()=="Bone.014") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
            this->m_Framework->rotate(600*this->currentTime,1,0,0);
        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }
    }
    //Tibia droite
    else if(node.name.toStdString()=="Bone.011") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
            this->m_Framework->rotate(600*this->currentTime,1,0,0);
        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }
    }
    //Pied droit
    else if(node.name.toStdString()=="Bone.012") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
            this->m_Framework->rotate(-300*this->currentTime,1,0,0);
        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }
    }
    //Pied gauche
    else if(node.name.toStdString()=="Bone.015") {
        //Phase de flexion
        if(this->currentTime>=0 && this->currentTime<0.166) {
            this->m_Framework->rotate(-300*this->currentTime,1,0,0);
        }
        //Phase d'extension
        else if (this->currentTime>=0.166 && this->currentTime<0.322) {

        }
        //Phase de saut
        else if (this->currentTime>=0.322 && this->currentTime<0.498) {

        }
        //Phase de retombée
        else if (this->currentTime>=0.498 && this->currentTime<0.664) {

        }
        //Phase d'amortissement
        else if (this->currentTime>=0.664 && this->currentTime<0.83) {

        }
        //Phase de retour à la postion debout
        else {

        }
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
