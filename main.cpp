#include <iostream>
#include<stdio.h>
#include <tuple>
#include <unordered_map>
#include <functional> // for std::hash

using namespace std;

// Code Téo
#define MAX 7

// Custom hash function for tuple<int, int>
struct tuple_hash {
    template <class T1, class T2>
    size_t operator() (const tuple<T1, T2>& t) const {
        auto h1 = hash<T1>{}(get<0>(t));
        auto h2 = hash<T2>{}(get<1>(t));
        return h1 ^ h2; // Combine the hash values
    }
};

class Case {
public:
    tuple <int, int> position;
    tuple <int, int> voisins[4];
    bool libre = true;
    bool estlibre() {  // Method/function defined inside the class
        return this->libre;
    }
    void setOccupation(bool valeur){
        this->libre = valeur;
    }
    void getvoisin() {
        if (get<0>(position) == 0 || get<0>(position) == MAX || get<1>(position) == 0 || get<1>(position) == MAX) {
            cout << "Erreur de Position";
        }
        int x = get<0>(this->position); int y = get<1>(this->position);
        // TODO
    }
};

class Plateau {
private:
    void createGrid() {
        Case case_tmp;
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                case_tmp.position = make_tuple(i, j);
                this->grid[make_tuple(i, j)] = case_tmp;
            }
        }
    }
public:
    unordered_map<tuple<int, int>, Case, tuple_hash> grid;  // Use custom hash for unordered_map
    void afficher_tableau() {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if(this ->grid[make_tuple(i,j)].estlibre()){
                    cout << "_";
                }
                else {
                    cout << "X";
                }

            }
            cout << endl;
        }
    }
    Plateau() { createGrid(); }
};


// Fin code Téo

class Insect
{   public:
    int id;
    tuple<int, int> position;

    public:

    void set_position(tuple<int,int> new_pos, Plateau& plateau)  // Pass by reference to modify the original plateau
{
    Case& c = plateau.grid[new_pos];  // Use reference instead of copying the Case object
    if (c.estlibre())
    {
        plateau.grid[new_pos].setOccupation(false);
         // This will now modify the original Case object
         this->position = new_pos;
    }
}


};

class Fourmi : public Insect
{
    public: bool pose;

public:
    void bouger(tuple<int,int> nouvelle_position, Plateau& plateau) {  // Pass plateau by reference
    Case& nouvelle_c = plateau.grid[nouvelle_position];
    Case& ancienne = plateau.grid[this->position];  // Use reference to modify the original object
    if (nouvelle_c.estlibre() == true) {
        nouvelle_c.position = nouvelle_position;
        nouvelle_c.libre = false;
        ancienne.libre = true;
        this->position = nouvelle_position;
    }
    else{
        cout<<"Sortie du plateau"<<endl;
    }
}

};

class Pion {
public:
    Fourmi liste_fourmis[22];
    int compteur = 0;

    void poser(Fourmi& fourmi, tuple<int, int> position, Plateau& plateau) {
        if (compteur < 22) {
            if (plateau.grid[position].estlibre()) {

                fourmi.set_position(position, plateau);

                liste_fourmis[compteur] = fourmi;
                compteur++;
            } else {
                cout << "Position deja occupée." << endl;
            }
        } else {
            cout << "Limite de Fourmis atteinte." << endl;
        }
    }

    // Méthode pour afficher toutes les Fourmis
    void afficher_fourmis() {
        for (int i = 0; i < compteur; i++) {
            cout << "Fourmi " << i << " a la position: " << get<0>(liste_fourmis[i].position) << ", " << get<1>(liste_fourmis[i].position) << endl;
        }
    }
};



int main()
{
    Plateau plateau;
    plateau.afficher_tableau();

    /*Fourmi fourmi1;
    tuple<int,int> pos_fourmi1 = make_tuple(5,5);
    fourmi1.id=1;

    Fourmi fourmi2;
    tuple<int,int> pos_fourmi2 = make_tuple(4,4);
    fourmi1.id=1;

    fourmi1.set_position(pos_fourmi1, plateau);
    fourmi2.set_position(pos_fourmi2, plateau);

    fourmi1.pose = true;
    fourmi2.pose = true;
    cout << endl;
    plateau.afficher_tableau();
    cout << endl;
    fourmi1.bouger(make_tuple(1,1),plateau);
    fourmi2.bouger(make_tuple(0,0),plateau);
    plateau.afficher_tableau();
    cout << endl;
    fourmi1.bouger(make_tuple(0,3),plateau);
    plateau.afficher_tableau(); */

    Pion pion; // Créez un objet Pion

    Fourmi fourmi1, fourmi2; // Créez des Fourmis

    // Essayez de poser les Fourmis sur le plateau
    pion.poser(fourmi1, make_tuple(2, 2), plateau);
    pion.poser(fourmi2, make_tuple(5, 5), plateau);

    // Affichez le tableau du plateau
    plateau.afficher_tableau();
    cout<<endl;

    // Affichez toutes les Fourmis
    pion.afficher_fourmis();
    return 0;
}
