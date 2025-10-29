#include "studentas.h"
#include "pagalbinesfunkcijos.h"
#include "duomenuoperacijos.h"
#include "laikas.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <list>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;

int main() {
    srand(time(0));
    std::string veiksmas;
    cout << "Pasirinkite rezima:\n" << "1 - Iprastas programos veikimas\n" << "2 - Automatinis testavimas (vector vs list)\n"; cin >> veiksmas;
    if (veiksmas == "2") {
        std::vector<std::string> test_failai = {
            "studentai1000.txt",
            "studentai10000.txt",
            "studentai100000.txt",
            "studentai1000000.txt",
            "studentai10000000.txt"
        };
        std::ofstream fout("testavimorezultatai.txt");
        if (!fout) {
            cout << "Nepavyko sukurti testavimorezultatai.txt" << endl;
            return 1;
        }
        char pagalkaskirstyti, pagalkarikiuoti;
        cout << "Pasirinkite pagal ka suskirstyti studentus:\n" << "a - pagal vidurki\n" << "b - pagal mediana\n"; cin >> pagalkaskirstyti;
        cout << "\nPagal ka rikiuoti studentus faile?\n" << "a - pagal pavarde\n" << "b - pagal varda\n" << "c - pagal galutini pazymi\n"; cin >> pagalkarikiuoti;
        int strategija;
        cout << "\nPasirinkite strategija:\n" << "1 - Du nauji konteineriai (vargsiukams ir galvociams)\n" << "2 - Vienas naujas konteineris (vargsiukai traukiami ir trinami is bendro)\n" << "3 - Optimizuota (naudojami darbo su konteineriais algoritmai)\n";; cin >> strategija;
        if (strategija == 1)
            fout << "Naudota STRATEGIJA 1: Du nauji konteineriai (vargsiukams ir galvociams).\n" << endl;
        else if (strategija == 2)
            fout << "Naudota STRATEGIJA 2: Vienas naujas konteineris (vargsiukai traukiami ir trinami is bendro).\n" << endl;
        else if (strategija == 3)
            fout << "Naudota STRATEGIJA 3 - Optimizuota (naudojami darbo su konteineriais algoritmai)\n";
        fout << left << setw(13) << "Konteineris" << setw(23) << "Failas" << setw(18) << "Nuskaitymas (s)" << setw(16) << "Rusiavimas (s)" << setw(14) << "Irasymas (s)" << setw(13) << "Bendras (s)" << setw(15) << "Atmintis (B)" << "\n";
        fout << std::string(109, '-') << "\n";
        for (auto& failopavadinimas : test_failai) {
            cout << "\nTestuojamas failas: " << failopavadinimas << endl;
            {
                Laikmatis bendra, t1;
                t1.reset();
                std::vector<Studentas> grupe = nuskaityti(failopavadinimas);
                double t_nuskaitymas = t1.elapsed();
                t1.reset();
                suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, strategija);
                double t_rusiavimas = t1.elapsed();
                Laikmatis t_irasyti_timer;
                suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, strategija);
                double t_irasyti = t_irasyti_timer.elapsed();
                double t_bendras = bendra.elapsed();
                size_t atminties_vector = sizeof(grupe) + grupe.capacity() * sizeof(Studentas);
                for (auto& s : grupe)
                    atminties_vector += sizeof(Studentas) + s.paz.capacity() * sizeof(int);
                cout << "Vector (strategija " << strategija << ") atminties uzimtis: " << atminties_vector << " bitai" << endl;
                fout << left << setw(13) << "vector" << setw(23) << failopavadinimas << setw(18) << std::fixed << std::setprecision(6) << t_nuskaitymas << setw(16) << t_rusiavimas << setw(14) << t_irasyti << setw(13) << t_bendras << setw(15) << atminties_vector << "\n";
            }
            {
                Laikmatis bendra, t1;
                t1.reset();
                std::vector<Studentas> laikini = nuskaityti(failopavadinimas);
                std::list<Studentas> grupe(laikini.begin(), laikini.end());
                double t_nuskaitymas = t1.elapsed();
                t1.reset();
                suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, strategija);
                double t_rusiavimas = t1.elapsed();
                Laikmatis t_irasyti_timer;
                suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, strategija);
                double t_irasyti = t_irasyti_timer.elapsed();
                double t_bendras = bendra.elapsed();
                size_t atminties_list = sizeof(grupe);
                for (auto& s : grupe)
                    atminties_list += sizeof(s) + sizeof(void*) * 2 + s.paz.capacity() * sizeof(int);
                cout << "List (strategija " << strategija << ") atminties uzimtis: " << atminties_list << " bitai" << endl;
                fout << left << setw(13) << "list" << setw(23) << failopavadinimas << setw(18) << std::fixed << std::setprecision(6) << t_nuskaitymas << setw(16) << t_rusiavimas << setw(14) << t_irasyti << setw(13) << t_bendras << setw(15) << atminties_list << "\n";
            }
        }
        fout.close();
        return 0;
    }
    std::string konteineriotipas;
    bool naudotivector = true;
    while (true) {
        cout << "Pasirinkite konteinerio tipa (vector/list): "; cin >> konteineriotipas;
        if (konteineriotipas == "vector") { naudotivector = true; break; }
        else if (konteineriotipas == "list") { naudotivector = false; break; }
        else cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
    }
    std::vector<std::pair<std::string, int>> failai = {
        //{"studentai1000.txt", 1000},
        //{"studentai10000.txt", 10000},
        //{"studentai100000.txt", 100000},
        //{"studentai1000000.txt", 1000000},
        //{"studentai10000000.txt", 10000000}
    };
    for (auto& f : failai) {
        generuotitxt(f.first, f.second);
    }
    std::vector<Studentas> GrupeVector;
    std::list<Studentas> GrupeList;
    char pasirinkimas;
    std::string pasirinkimas2;
    std::ofstream fout("rezultatai.txt");
    if (!fout) {
        cout << "Nepavyko sukurti rezultatu failo" << endl;
        return 1;
    }
    while (true) {
        cout << "Ar norite duomenis ivesti ranka, generuoti ar nuskaityti is failo? (ranka/generuoti/failas): "; cin >> pasirinkimas2;
        if (pasirinkimas2 == "ranka" || pasirinkimas2 == "generuoti" || pasirinkimas2 == "failas") break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    if (pasirinkimas2 == "failas") {
        std::string failopavadinimas;
        while (true) {
            cout << "Iveskite failo pavadinima: "; cin >> failopavadinimas;
            std::ifstream fd(failopavadinimas);
            if (!fd) {
                cout << "Nepavyko atidaryti failo. Bandykite dar karta." << endl;
                continue;
            }
            fd.close();
            break;
        }
        if (naudotivector) GrupeVector = nuskaityti(failopavadinimas);
        else {
            auto laikinas = nuskaityti(failopavadinimas);
            GrupeList.assign(laikinas.begin(), laikinas.end());
        }
    }
    else {
        int kiekis;
        while (true) {
            cout << "Kiek studentu norite prideti? ";
            cin >> kiekis;
            if (!cin || kiekis <= 0) {
                cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            break;
        }
        for (int j = 0; j < kiekis; j++) {
            std::string vard, pav;
            cout << "Iveskite " << j + 1 << " studenta" << endl;
            cout << "Iveskite pavarde: "; cin >> pav;
            cout << "Iveskite varda: "; cin >> vard;
            if (pasirinkimas2 == "ranka") {
                if (naudotivector) {
                    GrupeVector.push_back(ivesk(vard, pav));
                    cout << "Studento objektas saugomas adresu: " << &GrupeVector.back() << endl;
                }
                else {
                    GrupeList.push_back(ivesk(vard, pav));
                    auto it = GrupeList.end();
                    --it;
                    cout << "Studento objektas saugomas adresu: " << &(*it) << endl;
                }
            }
            else if (pasirinkimas2 == "generuoti") {
                int ndskaicius = 5;
                if (naudotivector) GrupeVector.push_back(generuoti(vard, pav, ndskaicius));
                else GrupeList.push_back(generuoti(vard, pav, ndskaicius));
            }
        }
    }
    while (true) {
        cout << "Pasirinkite koki galutini pazymi rodyti:\na - tik vidurki\nb - tik mediana\nc - vidurki ir mediana\n"; cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b' || pasirinkimas == 'c') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    Laikmatis laikmatis_rezultatu_rasymo;
    if (pasirinkimas == 'a') {
        fout << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas" << setw(15) << left << "Galutinis (Vid.)" << endl;
        fout << "------------------------------------------------------" << endl;
        if (naudotivector) for (auto temp : GrupeVector) fout << setw(15) << left << temp.pav << setw(15) << left << temp.vard << setw(15) << left << std::fixed << std::setprecision(2) << temp.Vidurkiorez << endl;
        else for (auto temp : GrupeList) fout << setw(15) << left << temp.pav << setw(15) << left << temp.vard << setw(15) << left << std::fixed << std::setprecision(2) << temp.Vidurkiorez << endl;
    }
    else if (pasirinkimas == 'b') {
        fout << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas" << setw(15) << left << "Galutinis (Med.)" << endl;
        fout << "------------------------------------------------------------" << endl;
        if (naudotivector) for (auto temp : GrupeVector) fout << setw(15) << left << temp.pav << setw(15) << left << temp.vard << setw(15) << left << std::fixed << std::setprecision(2) << temp.Medianosrez << endl;
        else for (auto temp : GrupeList) fout << setw(15) << left << temp.pav << setw(15) << left << temp.vard << setw(15) << left << std::fixed << std::setprecision(2) << temp.Medianosrez << endl;
    }
    else if (pasirinkimas == 'c') {
        fout << setw(15) << left << "Pavarde" << setw(15) << left << "Vardas" << setw(20) << left << "Galutinis (Vid.) / " << setw(15) << left << "Galutinis (Med.)" << endl;
        fout << "--------------------------------------------------------------------------------" << endl;
        if (naudotivector) for (auto temp : GrupeVector) fout << setw(15) << left << temp.pav << setw(15) << left << temp.vard << setw(20) << left << std::fixed << std::setprecision(2) << temp.Vidurkiorez << setw(15) << left << std::fixed << std::setprecision(2) << temp.Medianosrez << endl;
        else for (auto temp : GrupeList) fout << setw(15) << left << temp.pav << setw(15) << left << temp.vard << setw(20) << left << std::fixed << std::setprecision(2) << temp.Vidurkiorez << setw(15) << left << std::fixed << std::setprecision(2) << temp.Medianosrez << endl;
    }
    cout << "Irasymas i rezultatu faila truko: " << std::fixed << std::setprecision(6) << laikmatis_rezultatu_rasymo.elapsed() << " s" << endl;
    if (naudotivector) suskirstyti(GrupeVector);
    else suskirstyti(GrupeList);
}
