#ifndef MATERIALINFO
#define MATERIALINFO

#include <QString>
#include <QSharedPointer>
#include <QVector>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>



struct MaterialInfo
{
    QString Name;
    QVector3D Ambient;
    QVector3D Diffuse;
    QVector3D Specular;
    float Shininess;
};

struct LightInfo
{
    QVector4D Position;
    QVector3D Intensity;
};

struct Mesh
{
    QString name;
    unsigned int indexCount;
    unsigned int indexOffset;
    QSharedPointer<MaterialInfo> material;
};

struct Node
{
    QString name;
    QMatrix4x4 transformation;
    QVector<QSharedPointer<Mesh> > meshes;
    QVector<Node> nodes;
};


#endif // MATERIALINFO

