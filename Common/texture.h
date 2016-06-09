#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <GL/glew.h>
#include <iostream>
#include <QGLWidget>

using namespace std;
class Texture
{
public:
    Texture();
    ~Texture();
    void load(const char* name );
    void init();
    void close();
    void drawShape(GLsizei size, const GLvoid* tab_indices);
    GLuint texId;
    QImage m_image;
};

#endif // TEXTURE_H
