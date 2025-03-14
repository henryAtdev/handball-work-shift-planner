#include "termin.h"
#include "speicher.h"
#include <iostream>
#include <algorithm>

std::vector<Termin> termine;  // Liste der Termine

void terminHinzufuegen() {
    Termin t;
    std::cout << "Datum (TT.MM.JJJJ): ";
    std::cin >> t.datum;
    std::cout << "Uhrzeit (HH:MM): ";
    std::cin >> t.uhrzeit;
    termine.push_back(t);
    speichereTermine(termine);
}

void termineAnzeigen() {
    if (termine.empty()) {
        std::cout << "Keine Termine vorhanden.\n";
        return;
    }
    for (size_t i = 0; i < termine.size(); ++i) {
        std::cout << i+1 << ". " << termine[i].datum << " um " << termine[i].uhrzeit
                  << " | Belegt: " << termine[i].belegtePlaetze.size() << "/4\n";
        if (!termine[i].belegtePlaetze.empty()) {
            std::cout << "   Teilnehmer: ";
            for (const auto& person : termine[i].belegtePlaetze) {
                std::cout << person << " ";
            }
            std::cout << "\n";
        }
    }
}

void eintragen() {
    termineAnzeigen();
    if (termine.empty()) return;

    int auswahl;
    std::cout << "Nummer des Termins wählen: ";
    std::cin >> auswahl;
    
    if (auswahl < 1 || auswahl > (int)termine.size()) {
        std::cout << "Ungültige Auswahl!\n";
        return;
    }
    
    if (termine[auswahl - 1].belegtePlaetze.size() >= 4) {
        std::cout << "Termin ist bereits voll!\n";
        return;
    }

    std::string name;
    std::cout << "Dein Name: ";
    std::cin >> name;
    
    termine[auswahl - 1].belegtePlaetze.push_back(name);
    speichereTermine(termine);
}

void austragen() {
    termineAnzeigen();
    if (termine.empty()) return;

    int auswahl;
    std::cout << "Nummer des Termins wählen: ";
    std::cin >> auswahl;

    if (auswahl < 1 || auswahl > (int)termine.size()) {
        std::cout << "Ungültige Auswahl!\n";
        return;
    }

    std::string name;
    std::cout << "Dein Name: ";
    std::cin >> name;

    auto& teilnehmerListe = termine[auswahl - 1].belegtePlaetze;
    auto it = std::find(teilnehmerListe.begin(), teilnehmerListe.end(), name);

    if (it != teilnehmerListe.end()) {
        teilnehmerListe.erase(it);
        std::cout << "Du wurdest erfolgreich ausgetragen.\n";
        speichereTermine(termine);
    } else {
        std::cout << "Du bist nicht für diesen Termin eingetragen!\n";
    }
}
