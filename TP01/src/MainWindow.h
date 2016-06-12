#ifndef MAINWINDOW_h
#define MAINWINDOW_h


#include "GlWindow.h"


class MainWindow : public GlWindow
{
public:
    MainWindow();
    ~MainWindow();

    /*!
        *\brief Initialization des objets.
        */
    bool initializeObjects();

    /*!
        *\brief Rendu de la scène.
        */
    void render();

    void keyPressEvent(QKeyEvent *);
};


#endif
