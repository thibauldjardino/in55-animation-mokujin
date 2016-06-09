#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <GL/glew.h>
#include <iostream>
#include <QGLWidget>
#include <SOIL.h>

using namespace std;
class Texture
{
public:
    Texture();
    ~Texture();
    void load(const char* name );
    void loadSOIL(const char* name );
    void init();
    void initSOIL();
    void close();
    void drawShape(GLsizei size, const GLvoid* tab_indices);
    GLuint texId;
    QImage m_image;
    unsigned char * image;
    int imageWidth;
    int imageHeight;
    bool soil_Load;

};

#endif // TEXTURE_H
