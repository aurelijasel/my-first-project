#include "pagalbinesfunkcijos.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

Studentas ivesk(std::string vard, std::string pav) {
    Studentas Laik;
    Laik.vard = vard;
    Laik.pav = pav;
    int sum = 0, m;
    std::string ats;
    while (true) {
        while (true) {
            cout << "Iveskite pazymi: "; cin >> m;
            if (!cin || m < 1 || m > 10) {
                cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            break;
        }
        Laik.paz.push_back(m);
        sum += m;
        while (true) {
            cout << "Ar norite ivesti dar viena pazymi? (taip/ne): "; cin >> ats;
            if (ats == "taip" || ats == "ne") break;
            else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
        }
        if (ats == "ne") break;
    }
    while (true) {
        cout << "Iveskite egzamina: "; cin >> Laik.egzas;
        if (!cin || Laik.egzas < 1 || Laik.egzas > 10) {
            cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        break;
    }
    if (Laik.paz.empty()) {
        Laik.Vidurkiorez = Laik.Medianosrez = 0;
    }
    else {
        Laik.Vidurkiorez = Laik.egzas * 0.6 + double(sum) / double(Laik.paz.size()) * 0.4;
        Laik.Medianosrez = Laik.egzas * 0.6 + median(Laik.paz) * 0.4;
    }
    return Laik;
}

double median(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    if (v.size() % 2 == 0)
        return ((v[v.size() / 2 - 1] + v[v.size() / 2]) / 2.0);
    else
        return v[v.size() / 2];
}

Studentas generuoti(std::string vard, std::string pav, int ndskaicius) {
    Studentas Laik;
    Laik.vard = vard;
    Laik.pav = pav;
    int sum = 0;
    for (int i = 0; i < ndskaicius; i++) {
        int pazymys = rand() % 10 + 1;
        Laik.paz.push_back(pazymys);
        sum += pazymys;
    }
    Laik.egzas = rand() % 10 + 1;
    Laik.Vidurkiorez = Laik.egzas * 0.6 + double(sum) / double(Laik.paz.size()) * 0.4;
    Laik.Medianosrez = Laik.egzas * 0.6 + median(Laik.paz) * 0.4;
    return Laik;
}

Studentas generuotistudenta(int id, int ndskaicius) {
    Studentas s;
    s.vard = "Vardas" + std::to_string(id);
    s.pav = "Pavarde" + std::to_string(id);
    int sum = 0;
    for (int i = 0; i < ndskaicius; i++) {
        int pazymys = rand() % 10 + 1;
        s.paz.push_back(pazymys);
        sum += pazymys;
    }
    s.egzas = rand() % 10 + 1;
    s.Vidurkiorez = s.egzas * 0.6 + (double)sum / s.paz.size() * 0.4;
    s.Medianosrez = s.egzas * 0.6 + median(s.paz) * 0.4;
    return s;
}
