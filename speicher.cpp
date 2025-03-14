#include "speicher.h"
#include <fstream>
#include <sstream>
#include <iostream>

void speichereTermine(const std::vector<Termin>& termine) {
    std::ofstream datei("termine.csv");
    for (const auto& termin : termine) {
        datei << termin.datum << "," << termin.uhrzeit;
        for (const auto& person : termin.belegtePlaetze) {
            datei << "," << person;
        }
        datei << "\n";
    }
    datei.close();
}

void ladeTermine(std::vector<Termin>& termine) {
    std::ifstream datei("termine.csv");
    std::string zeile;
    while (getline(datei, zeile)) {
        std::stringstream ss(zeile);
        std::string datum, uhrzeit, person;
        getline(ss, datum, ',');
        getline(ss, uhrzeit, ',');

        Termin t = {datum, uhrzeit, {}};
        while (getline(ss, person, ',')) {
            t.belegtePlaetze.push_back(person);
        }
        termine.push_back(t);
    }
    datei.close();
}
