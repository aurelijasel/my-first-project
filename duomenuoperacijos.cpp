#include "duomenuoperacijos.h"
#include "pagalbinesfunkcijos.h"
#include "laikas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;

std::vector<Studentas> nuskaityti(std::string failas) {
    Laikmatis laikmatis_nuskaitymo;
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
    cout << "Failo nuskaitymas uztruko: " << laikmatis_nuskaitymo.elapsed() << " s" << endl;
    return Grupe;
}

void generuotitxt(const std::string& pavadinimas, int kiekis) {
    Laikmatis laikmatis_generavimo;
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
    cout << "Generavimas uztruko: " << laikmatis_generavimo.elapsed() << " s" << endl;
}

void suskirstyti(const std::vector<Studentas>& Grupe) {
    char pasirinkimas;
    while (true) {
        cout << "Pasirinkite pagal ka suskirstyti studentus:\n a - pagal vidurki\n b - pagal mediana\n"; cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    Laikmatis laikmatis_rusiavimo;
    std::vector<Studentas> vargsiukai;
    std::vector<Studentas> galvociai;
    for (auto& s : Grupe) {
        double galutinisRez = 0.0;
        if (pasirinkimas == 'a') {
            galutinisRez = s.Vidurkiorez;
        }
        else {
            galutinisRez = s.Medianosrez;
        }
        if (galutinisRez < 5.0) {
            vargsiukai.push_back(s);
        }
        else {
            galvociai.push_back(s);
        }
    }
    cout << "Studentu rusiavimas i dvi grupes uztruko: " << laikmatis_rusiavimo.elapsed() << " s" << endl;
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        double galutinisA, galutinisB;
        if (pasirinkimas == 'a') {
            galutinisA = a.Vidurkiorez;
            galutinisB = b.Vidurkiorez;
        }
        else {
            galutinisA = a.Medianosrez;
            galutinisB = b.Medianosrez;
        }
        return galutinisA < galutinisB;
        };
    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);
    Laikmatis laikmatis_failu_rasymo;
    std::ofstream foutvargsiukai("vargsiukai.txt");
    std::ofstream foutgalvociai("galvociai.txt");
    if (!foutvargsiukai || !foutgalvociai) {
        cout << "Nepavyko sukurti failu vargsiukams arba galvociams" << endl;
        return;
    }
    for (auto& s : vargsiukai) {
        if (pasirinkimas == 'a') {
            double galutinisVid = s.Vidurkiorez;
            foutvargsiukai << s.pav << " " << s.vard
                << " Galutinis (Vid.): " << std::fixed << std::setprecision(2) << galutinisVid << "\n";
        }
        else {
            double galutinisMed = s.Medianosrez;
            foutvargsiukai << s.pav << " " << s.vard
                << " Galutinis (Med.): " << std::fixed << std::setprecision(2) << galutinisMed << "\n";
        }
    }
    for (auto& s : galvociai) {
        if (pasirinkimas == 'a') {
            double galutinisVid = s.Vidurkiorez;
            foutgalvociai << s.pav << " " << s.vard
                << " Galutinis (Vid.): " << std::fixed << std::setprecision(2) << galutinisVid << "\n";
        }
        else {
            double galutinisMed = s.Medianosrez;
            foutgalvociai << s.pav << " " << s.vard
                << " Galutinis (Med.): " << std::fixed << std::setprecision(2) << galutinisMed << "\n";
        }
    }
    foutvargsiukai.close();
    foutgalvociai.close();
    cout << "Studentu isvedimas i suskirstymo failus uztruko: " << laikmatis_failu_rasymo.elapsed() << " s" << endl;
    cout << "Sukurti 'vargsiukai.txt' ir 'galvociai.txt'" << endl;
}
