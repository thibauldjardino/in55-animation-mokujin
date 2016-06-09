#include "texture.h"

Texture::Texture()
{

}

void Texture::load(const char* name ){

    if(m_image.load(name)){

       cout<<"fail to load texture"<<endl;

       m_image = QGLWidget::convertToGLFormat( m_image );

    }

}

void Texture::init(){


    glBindTexture(GL_TEXTURE_2D, texId);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_image.width(), m_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.bits() );

}


void Texture::drawShape(GLsizei size, const GLvoid* tab_indices){
    Texture::init();

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

