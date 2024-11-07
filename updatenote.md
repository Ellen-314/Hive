# Modifs apportées par rapport à la dernière version
- **Board.cpp** - *ligne 37* : suppression de la ligne de code `delete board_spots[i]->getInsect(); // Supprime l'insecte de la memoire` -> ==elle n'a pas lieu d'être ? il suffit juste de remplacer le pointeur `insect_pose` par un pointeur nul non ? ou je rate une étape ?==
- **Insect.h** - *ligne 55* : En laissant cette ligne, j'ai l'erreur `invalid new-expression of abstract class type 'Insect'` qui signifie qu'on essaie d'instancier une classe abstraite. C'est la présence de cette méthode virtuelle `moov` qui rend `Insect` abstraite, donc non instanciable directement (les `Insect* insect1 = new Insect();` du **main.cpp** me font donc une erreur). En l'enlevant, la classe Insecte n'est plus abstraite donc on peut l'instancier directement.
- **Board.cpp** - *lignes 29, 42, 46 et 57* : changement des types d'exceptions `std::runtime_error` en `SetException` -> ==c'est ok de faire ça ou bien la classe `SetException` est pas prévue pour ça ?==
- **Board.h** - *ajout ligne 19* : ajout d'un accesseur public pour le `message` d'erreur de `SetException` -> ==pourquoi cette classe s'appelle comme ça ? On l'avait pas appelée comme ça dans le TD par rapport au jeu SET! ? Du coup là on l'appellerait `BoardException` ?== 
- **Board.cpp** - *modification* : ajout d'un retour à la ligne et d'une tabulation juste pour rendre plus lisible dans le cas où on a beaucoup de cases.

# Questions
- **Board.cpp** : *`modifySpot`* : on duplique une case et on supprime l'ancienne là non ? et que fait-on du cas où un insecte vient se placer sur un autre insecte ?
- **Board.cpp** : *`addSpot`* : On ne vérifie pas si le spot qu'on veut ajouter existe déjà ?
