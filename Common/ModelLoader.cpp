#include "ModelLoader.h"

ModelLoader::ModelLoader()
{

}


bool ModelLoader::Load(QString pathToFile)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pathToFile.toStdString(),
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType |
                                             aiProcess_ConvertToLeftHanded
                                             );

    if (!scene)
    {
        qDebug() << "Error loading file: (assimp:) " << importer.GetErrorString();
        return false;
    }

    if (scene->HasMaterials())
    {
        for (unsigned int ii = 0; ii < scene->mNumMaterials; ++ii)
        {
            QSharedPointer<MaterialInfo> mater = processMaterial(scene->mMaterials[ii]);
            m_materials.push_back(mater);
        }
    }
    else
    {
        qDebug() << "Error: No material found";
        return false;
    }


    if(scene->HasMeshes()){
        for (unsigned int ii = 0; ii < scene->mNumMeshes; ++ii)
        {
            m_meshes.append(processMesh(scene->mMeshes[ii]));
        }
        for (unsigned int ii = 0; ii < scene->mNumMeshes; ++ii)
        {

            qDebug()<<m_meshes[ii].data()->name;
        }
        //qDebug()<<m_vertices.length();
    }
    else
    {
        qDebug() << "Error: No meshes found";
        return false;
    }


    if (scene->mRootNode != NULL)
    {
        Node *rootNode = new Node;
        processNode(scene, scene->mRootNode, 0, *rootNode);
        m_rootNode.reset(rootNode);
    }
    else
    {
        qDebug() << "Error loading model";
        return false;
    }

    return true;
}

void ModelLoader::getBufferData( QVector<float> **vertices, QVector<float> **normals, QVector<unsigned int> **indices)
{
    if(vertices != 0)
        *vertices = &m_vertices;

    if(normals != 0)
        *normals = &m_normals;

    if(indices != 0)
        *indices = &m_indices;
}

QSharedPointer<Mesh> ModelLoader::processMesh(aiMesh *mesh)
{
    QSharedPointer<Mesh> newMesh(new Mesh);
    newMesh->name = mesh->mName.length != 0 ? mesh->mName.C_Str() : "";
    newMesh->indexOffset = m_indices.size();
    unsigned int indexCountBefore = m_indices.size();
    int vertindexoffset = m_vertices.size()/3;

    // Get Vertices
    if (mesh->mNumVertices > 0)
    {
        for (uint ii = 0; ii < mesh->mNumVertices; ++ii)
        {
            aiVector3D &vec = mesh->mVertices[ii];

            m_vertices.push_back(vec.x);
            m_vertices.push_back(vec.y);
            m_vertices.push_back(vec.z);
        }
    }

    // Get Normals
    if (mesh->HasNormals())
    {
        for (uint ii = 0; ii < mesh->mNumVertices; ++ii)
        {
            aiVector3D &vec = mesh->mNormals[ii];
            m_normals.push_back(vec.x);
            m_normals.push_back(vec.y);
            m_normals.push_back(vec.z);
        };
    }

    // Get mesh indexes
    for (uint t = 0; t < mesh->mNumFaces; ++t)
    {
        aiFace* face = &mesh->mFaces[t];
        if (face->mNumIndices != 3)
        {
            qDebug() << "Warning: Mesh face with not exactly 3 indices, ignoring this primitive.";
            continue;
        }

        m_indices.push_back(face->mIndices[0]+vertindexoffset);
        m_indices.push_back(face->mIndices[1]+vertindexoffset);
        m_indices.push_back(face->mIndices[2]+vertindexoffset);
    }

    newMesh->indexCount = m_indices.size() - indexCountBefore;
    newMesh->material = m_materials.at(mesh->mMaterialIndex);

    return newMesh;
}

QSharedPointer<MaterialInfo> ModelLoader::processMaterial(aiMaterial *material)
{
    QSharedPointer<MaterialInfo> mater(new MaterialInfo);

    aiString mname;
    material->Get(AI_MATKEY_NAME, mname);
    if (mname.length > 0)
        mater->Name = mname.C_Str();

    int shadingModel;
    material->Get(AI_MATKEY_SHADING_MODEL, shadingModel);

    if (shadingModel != aiShadingMode_Phong && shadingModel != aiShadingMode_Gouraud)
    {
        qDebug() << "This mesh's shading model is not implemented in this loader, setting to default material";
        mater->Name = "DefaultMaterial";
    }
    else
    {
        aiColor3D dif(0.f,0.f,0.f);
        aiColor3D amb(0.f,0.f,0.f);
        aiColor3D spec(0.f,0.f,0.f);
        float shine = 0.0;

        material->Get(AI_MATKEY_COLOR_AMBIENT, amb);
        material->Get(AI_MATKEY_COLOR_DIFFUSE, dif);
        material->Get(AI_MATKEY_COLOR_SPECULAR, spec);
        material->Get(AI_MATKEY_SHININESS, shine);

        mater->Ambient = QVector3D(amb.r, amb.g, amb.b);
        mater->Diffuse = QVector3D(dif.r, dif.g, dif.b);
        mater->Specular = QVector3D(spec.r, spec.g, spec.b);
        mater->Shininess = shine;

        mater->Ambient *= .2;
        if (mater->Shininess == 0.0)
            mater->Shininess = 30;
    }

    return mater;
}

void ModelLoader::processNode(const aiScene *scene, aiNode *node, Node *parentNode, Node &newNode)
{
    newNode.name = node->mName.length != 0 ? node->mName.C_Str() : "";
    std::cout<< newNode.name.toStdString()<<std::endl;
    QMatrix4x4 tmp = QMatrix4x4(node->mTransformation[0]);

    newNode.transformation = tmp;
    qDebug()<<newNode.transformation;
    std::cout<< newNode.transformation.column(0).z()<<std::endl;
    newNode.meshes.resize(node->mNumMeshes);

    //M_MESH EMPTY
    for (uint imesh = 0; imesh < node->mNumMeshes; ++imesh)
    {
        QSharedPointer<Mesh> mesh = m_meshes[node->mMeshes[imesh]];
        newNode.meshes[imesh] = mesh;
    }

    for (uint ich = 0; ich < node->mNumChildren; ++ich)
    {
        newNode.nodes.push_back(Node());
        processNode(scene, node->mChildren[ich], parentNode, newNode.nodes[ich]);

    }
}
