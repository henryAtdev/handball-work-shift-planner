#include "termin.h"
#include "speicher.h"
#include <iostream>

void menue() {
    int auswahl;
    do {
        std::cout << "\n1. Termin hinzufügen\n2. Termine anzeigen\n3. Eintragen\n4. Austragen\n5. Beenden\n";
        std::cin >> auswahl;

        switch (auswahl) {
            case 1: terminHinzufuegen(); break;
            case 2: termineAnzeigen(); break;
            case 3: eintragen(); break;
            case 4: austragen(); break;
            case 5: std::cout << "Programm beendet.\n"; break;
            default: std::cout << "Ungültige Eingabe!\n";
        }
    } while (auswahl != 5);
}

int main() {
    ladeTermine(termine);
    menue();
    return 0;
}
