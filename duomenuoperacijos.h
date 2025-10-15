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

#endif
