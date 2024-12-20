#include "Jeu.h"
#include "Controleur.h"
#include <cstdio>
#include <windows.h>

#pragma execution_character_set("utf-8")

int main() {
    SetConsoleOutputCP( 65001 );

    Controleur controleur;
    controleur.demarrage();

    return 0;
}
