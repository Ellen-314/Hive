#include <iostream>
using namespace std;

// BY EVAN

// Codes d’échappement ANSI.
// Définition de plusieurs caractères de couleur comme des macros
// qui seviront de caractères d'échappement pour changer de couleur.
//
// Exemple : pour avoir des lettres noires sur un fond blanc on utilisera \e[30;47m
//
// Lien pour les codes : https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#define NB "\e[0;40m"          // terminal normal
#define RED "\e[0;31m"      // rouge
#define GRN "\e[0;32m"      // vert
#define CYAN "\e[0;36m"     // bleu clair
#define TITRE "\e[30;47m"   // noir fond blanc
// le \e est un caractère d’échappement ASCII. un caractère de parenthèse suivis de paramètres



int main()
{
    printf(RED "BY EVAN - Note" NB
               ": Mine de rien ca va quand meme etre galere, je pense que pour faciliter le placement des pieces dans le termminal, il vaudra mieux qu'elles aient toutes des coordonnees, comme ca on print d'abord celles qui sont le plus en haut etc.\n");
    cout << TITRE "eho\n" NB "yo\n" RED "ca dit quoi\n" GRN "MAIS NAN\n" CYAN "chokbar\n" NB;
    cout << NB "\n-----------\n\n" TITRE "VERSION GRAND (1 piece fait 10 caracteres de large et 5 lignes)" NB "\n";
    cout << "  ______          ______\n";
    cout << " /      \\        /      \\\n";
    cout << "/   " CYAN "S1" NB "   \\______/   A2   \\\n";
    cout << "\\        /      \\        /\n";
    cout << " \\______/   QU   \\" CYAN "______" NB "/\n";
    cout << "        \\        " CYAN "/      \\" NB "\n";
    cout << "         \\______" CYAN "/   qu   \\" NB "\n";
    cout << "                " CYAN "\\   1    /" NB "\n";
    cout << "                 " CYAN "\\______/" NB "\n";

    cout << TITRE "eho\n" NB "yo\n" RED "ca dit quoi\n" GRN "MAIS NAN\n" CYAN "chokbar\n" NB;
    cout << NB "\n-----------\n\n" TITRE "VERSION PETIT (1 piece fait 6 caracteres de large et 3 lignes)" NB "\n";
    cout << " ____      ____\n";
    cout << "/ " CYAN "S1" NB " \\____/ A2 \\\n";
    cout << "\\____/ QU \\" CYAN "____" NB "/\n";
    cout << "     \\____" CYAN "/ qu \\" NB "\n";
    cout << "          " CYAN "\\_1__/" NB "\n";

    return 0;
}
