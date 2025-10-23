#ifndef DUOMENUOPERACIJOS_H
#define DUOMENUOPERACIJOS_H

#include "studentas.h"
#include <string>
#include <vector>
#include <list>

std::vector<Studentas> nuskaityti(std::string failas);
void generuotitxt(const std::string& pavadinimas, int kiekis);
void suskirstyti(const std::vector<Studentas>& Grupe);
void suskirstyti(const std::list<Studentas>& Grupe);
void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);
void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti);
void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija);
void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija);

#endif
