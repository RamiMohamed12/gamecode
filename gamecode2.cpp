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
};

int Creature::cpt = 0; // Initialize static variable

void foo() {
    Creature temp(20, 10, 1); // Temporary creature
    cout << "Inside foo(), Nombre de créatures : " << Creature::getCount() << endl;
} // temp is destroyed here

void test1() {
    cout << "Test 1: \n";

    Creature c1; // Default creature
    Creature c2(10, 2, 2); // Custom creature

    cout << "Nombre de créatures: " << Creature::getCount() << endl;

    foo(); // Call foo to create and destroy a creature

    cout << "Nombre de créatures après appel de foo : " << Creature::getCount() << endl;
}

void bar(Creature c1) {
    Creature c2; // Another creature inside bar
    cout << "Inside bar(), Nombre de créatures: " << Creature::getCount() << endl;
} // c2 is destroyed here

void test2() {
    cout << "Test 2: \n";

    Creature c1; // Default creature
    Creature c2(10, 2, 2); // Custom creature

    cout << "Nombre de créatures: " << Creature::getCount() << endl;

    bar(c2); // Pass c2 by value to bar

    cout << "Nombre de créatures après appel de bar : " << Creature::getCount() << endl;
}

int main() {
    // Uncomment to test the main gameplay
    /*
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
    */

    // Run the tests
    test1();
    test2();

    return 0;
}

