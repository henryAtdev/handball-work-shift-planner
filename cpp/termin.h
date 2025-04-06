#ifndef TERMIN_H
#define TERMIN_H

#include <vector>
#include <string>

struct Termin {
    std::string datum;
    std::string uhrzeit;
    std::vector<std::string> belegtePlaetze;
};


void terminHinzufuegen();
void termineAnzeigen();
void eintragen();
void austragen();

#endif
