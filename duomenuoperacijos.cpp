#include "duomenuoperacijos.h"
#include "pagalbinesfunkcijos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;

std::vector<Studentas> nuskaityti(std::string failas) {
    std::vector<Studentas> Grupe;
    std::ifstream fd(failas);
    if (!fd) {
        cout << "Nepavyko atidaryti failo";
        return Grupe;
    }
    std::string antraste;
    getline(fd, antraste);
    std::string eilute;
    while (getline(fd, eilute)) {
        std::istringstream ss(eilute);
        Studentas Laik;
        ss >> Laik.vard >> Laik.pav;
        Laik.paz.clear();
        int skaicius;
        std::vector<int> laikini;
        while (ss >> skaicius) {
            laikini.push_back(skaicius);
        }
        if (laikini.empty()) continue;
        Laik.egzas = laikini.back();
        laikini.pop_back();
        int sum = 0;
        for (int p : laikini) {
            Laik.paz.push_back(p);
            sum += p;
        }
        if (!Laik.paz.empty()) {
            Laik.Vidurkiorez = Laik.egzas * 0.6 + double(sum) / Laik.paz.size() * 0.4;
            Laik.Medianosrez = Laik.egzas * 0.6 + median(Laik.paz) * 0.4;
        }
        else {
            Laik.Vidurkiorez = Laik.Medianosrez = Laik.egzas * 0.6;
        }
        Grupe.push_back(Laik);
    }
    return Grupe;
}

void generuotitxt(const std::string& pavadinimas, int kiekis) {
    std::ofstream fout(pavadinimas);
    if (!fout) {
        cout << "Nepavyko sukurti failo: " << pavadinimas << endl;
        return;
    }
    fout << "Vardas Pavarde ";
    for (int i = 1; i <= 5; i++) fout << "ND" << i << " ";
    fout << "Egzaminas\n";
    for (int i = 1; i <= kiekis; i++) {
        Studentas s = generuotistudenta(i, 5);
        fout << s.vard << " " << s.pav << " ";
        for (int paz : s.paz) fout << paz << " ";
        fout << s.egzas << "\n";
    }
    fout.close();
    cout << "Failas " << pavadinimas << " sukurtas" << endl;
}

void suskirstyti(const std::vector<Studentas>& Grupe) {
    char pasirinkimas;
    while (true) {
        cout << "Pasirinkite pagal ka suskirstyti studentus:\n a - pagal vidurki\n b - pagal mediana\n"; std::cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    std::ofstream foutvargsiukai("vargsiukai.txt");
    std::ofstream foutgalvociai("galvociai.txt");
    if (!foutvargsiukai || !foutgalvociai) {
        cout << "Nepavyko sukurti failu vargsiukams arba galvociams" << endl;
        return;
    }
    for (auto& s : Grupe) {
        double galutinis = (pasirinkimas == 'a') ? s.Vidurkiorez : s.Medianosrez;
        if (galutinis < 5.0) {
            foutvargsiukai << s.pav << " " << s.vard << endl;
        }
        else {
            foutgalvociai << s.pav << " " << s.vard << endl;
        }
    }
    foutvargsiukai.close();
    foutgalvociai.close();
    cout << "Sukurti 'vargsiukai.txt' ir 'galvociai.txt'" << endl;
}