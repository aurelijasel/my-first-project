#ifndef PAGALBINESFUNKCIJOS_H
#define PAGALBINESFUNKCIJOS_H

#include "studentas.h"
#include <vector>
#include <string>

Studentas ivesk(std::string vard, std::string pav);
double median(std::vector<int> v);
Studentas generuoti(std::string vard, std::string pav, int ndskaicius);
Studentas generuotistudenta(int id, int ndskaicius = 5);

#endif