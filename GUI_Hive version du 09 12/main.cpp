#include <QApplication>
#include "N_game.h"
#include "Jeu.h"
#include "Controleur.h"
#include <cstdio>
#include <windows.h>
#pragma execution_character_set("utf-8")

Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->displayMainMenu();

    ///Main du terminal
    //SetConsoleOutputCP( 65001 );
    //Controleur controleur;
    //controleur.demarrage();

    return a.exec();

}

