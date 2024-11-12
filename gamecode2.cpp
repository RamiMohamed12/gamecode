#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   
#include <fstream> 

using namespace std;

class Creature {
private:
    int pv;
    int pa;
    int niveau;
    static int cpt; // Static variable for counting creatures

public:
    Creature() : pv(100), pa(20), niveau(1) { cpt++; }
    Creature(int pv, int pa, int niveau) : pv(pv), pa(pa), niveau(niveau) { cpt++; }
    ~Creature() { cpt--; }

    static int getCount() { return cpt; }

    void affiche() {
        cout << "\n===== CREATURE =====" << endl;
        cout << "PV : " << pv << "\nPA : " << pa << "\nNiveau : " << niveau << endl;
        cout << "Nombre total de créatures : " << cpt << endl;
        cout << "====================\n" << endl;
    }

    int attack() {
        int alea = rand() % 10 + 1;
        int degats = (this->pa * this->niveau * alea) / 10;
        cout << "La créature attaque et inflige " << degats << " dégâts !" << endl;
        return degats;
    }

    void subitdegat(int degats) {
        this->pv -= degats;
        cout << "La créature subit " << degats << " dégâts !" << endl;
    }

    bool estvivant() {
        return this->pv > 0;
    }
};

int Creature::cpt = 0; // Initialize static variable

class Hero {
private:
    string nom;
    int pv;
    int pa;
    int niveau;
    int arme;
    int potions;

public:
    Hero() : nom("jijli"), pv(100), pa(20), niveau(1), arme(0), potions(3) {}
    Hero(string nom, int pv, int pa, int niveau) : nom(nom), pv(pv), pa(pa), niveau(niveau), arme(0), potions(3) {}
    ~Hero() {}

    void affiche() {
        cout << "\n====== HERO ======" << endl;
        cout << "Nom    : " << nom << "\nPV     : " << pv << "\nPA     : " << pa 
             << "\nNiveau : " << niveau << "\nArme   : +" << arme 
             << "\nPotions: " << potions << endl;
        cout << "==================\n" << endl;
    }

    int attack() {
        int alea = rand() % 10 + 1;
        int degats = ((this->pa + this->arme) * this->niveau * alea) / 10;
        cout << nom << " attaque et inflige " << degats << " dégâts !" << endl;
        return degats;
    }

    void subitdegat(int degats) {
        this->pv -= degats;
        cout << nom << " subit " << degats << " dégâts !" << endl;
    }

    bool estvivant() {
        return this->pv > 0;
    }

    void utiliserPotion() {
        if (potions > 0) {
            pv += 20; 
            potions--;
            cout << nom << " utilise une potion et récupère 20 PV. PV actuels : " << pv << endl;
        } else {
            cout << "Vous n'avez plus de potions !" << endl;
        }
    }

    void equiperArme(int puissance) {
        arme = puissance;
        cout << nom << " équipe une arme avec +" << arme << " points d'attaque !" << endl;
    }

    void sauvegarder(const string& nomFichier) {
        ofstream fichier(nomFichier);
        if (fichier) {
            fichier << nom << " " << pv << " " << pa << " " << niveau << " " << arme << " " << potions << endl;
            cout << "\nPartie sauvegardée dans " << nomFichier << " !" << endl;
        } else {
            cout << "Erreur de sauvegarde !" << endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Hero hero("demy", 100, 10, 5);
    Creature creature(50, 10, 2);

    hero.affiche();
    creature.affiche();

    while (hero.estvivant() && creature.estvivant()) {
        cout << "\n===== MENU =====" << endl;
        cout << "1. Attaquer" << endl;
        cout << "2. Utiliser une potion" << endl;
        cout << "3. Equiper une arme (+5 PA)" << endl;
        cout << "4. Sauvegarder et quitter" << endl;
        cout << "================" << endl;
        cout << "Choisissez une action : ";
        int choix;
        cin >> choix;

        cout << "\n--------------------\n";

        switch (choix) {
            case 1: { 
                int degats = hero.attack();
                creature.subitdegat(degats);
                break;
            }
            case 2: 
                hero.utiliserPotion();
                break;
            case 3: 
                hero.equiperArme(5); // Arme +5 aux PA
                break;
            case 4: 
                hero.sauvegarder("sauvegarde.txt");
                cout << "Merci d'avoir joué ! À bientôt !" << endl;
                return 0;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
                continue;
        }

        // Creature's turn
        if (creature.estvivant()) {
            int degats = creature.attack();
            hero.subitdegat(degats);
        } else {
            cout << "Bravo ! La créature est vaincue !" << endl;
        }

        cout << "\n===== ETAT =====" << endl;
        hero.affiche();
        creature.affiche();
        cout << "================\n";

        if (!hero.estvivant()) {
            cout << "Le héros est vaincu ! Game Over." << endl;
            break;
        }
    }

    return 0;
}

