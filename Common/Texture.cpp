#include "Texture.h"

Texture::Texture()
{
    soil_Load = false;
}
// charge la texture
void Texture::load(const char* name ){

    if(!m_image.load(name))
    {

        cout<<"fail to load texture"<<endl;

    }
    else
    {
        m_image = QGLWidget::convertToGLFormat( m_image );
    }

}
// charge une image en utilisant soil
void Texture::loadSOIL(const char* name ){

    image = SOIL_load_image(name,
                            &imageWidth,
                            &imageHeight,
                            0,
                            SOIL_LOAD_RGBA);
    soil_Load = true;

}

//instancier la texture dans OpenGL
void Texture::init(){


    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.bits() );

}

//instancier l'image dans OpenGL
void Texture::initSOIL(){


    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 imageWidth,
                 imageHeight,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image);
}
//construit la texture ou l'image sur les triangles d'un objet passé en paramètre
void Texture::drawShape(GLsizei size, const GLvoid* tab_indices){

    if(soil_Load)
    {
        Texture::initSOIL();
    }
    else
    {

        Texture::init();
    }


    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT,tab_indices);
    Texture::close();
}

void
Texture::close(){
    glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::~Texture()
{

}

