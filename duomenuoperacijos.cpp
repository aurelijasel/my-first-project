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
        cout << "Nepavyko atidaryti failo: " << failas << endl;
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
    cout << std::fixed << std::setprecision(6) << "Failo nuskaitymas uztruko: " << laikmatis_nuskaitymo.elapsed() << " s" << endl;
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
    cout << std::fixed << std::setprecision(6)
        << "Generavimas uztruko: " << laikmatis_generavimo.elapsed() << " s" << endl;
}

void suskirstyti(const std::vector<Studentas>& Grupe) {
    char pasirinkimas;
    while (true) {
        cout << "Pasirinkite pagal ka suskirstyti studentus:\n" << " a - pagal vidurki\n b - pagal mediana\n"; cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    Laikmatis laikmatis_rusiavimo;
    std::vector<Studentas> vargsiukai;
    std::vector<Studentas> galvociai;
    for (auto& s : Grupe) {
        double galutinisRez = (pasirinkimas == 'a') ? s.Vidurkiorez : s.Medianosrez;
        if (galutinisRez < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }
    cout << std::fixed << std::setprecision(6) << "Studentu rusiavimas i dvi grupes (vector) uztruko: " << laikmatis_rusiavimo.elapsed() << " s" << endl;
    char rikiavimas_pasirinkimas;
    while (true) {
        cout << "Pagal ka rikiuoti studentus faile?\n" << " a - pagal pavarde\n" << " b - pagal varda\n" << " c - pagal galutini pazymi\n"; cin >> rikiavimas_pasirinkimas;
        if (rikiavimas_pasirinkimas == 'a' || rikiavimas_pasirinkimas == 'b' || rikiavimas_pasirinkimas == 'c') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (rikiavimas_pasirinkimas == 'a') return a.pav < b.pav;
        else if (rikiavimas_pasirinkimas == 'b') return a.vard < b.vard;
        else {
            double galutinisA = (pasirinkimas == 'a') ? a.Vidurkiorez : a.Medianosrez;
            double galutinisB = (pasirinkimas == 'a') ? b.Vidurkiorez : b.Medianosrez;
            return galutinisA < galutinisB;
        }
    };
    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);
    Laikmatis laikmatis_failu_rasymo;
    std::ofstream foutvargsiukai("vargsiukai_vector_strat1.txt");
    std::ofstream foutgalvociai("galvociai_vector_strat1.txt");
    if (!foutvargsiukai || !foutgalvociai) {
        cout << "Nepavyko sukurti failu vargsiukams arba galvociams" << endl;
        return;
    }
    for (auto& s : vargsiukai) {
        double galutinis = (pasirinkimas == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutvargsiukai << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
    for (auto& s : galvociai) {
        double galutinis = (pasirinkimas == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutgalvociai << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
    foutvargsiukai.close();
    foutgalvociai.close();
    cout << std::fixed << std::setprecision(6) << "Studentu isvedimas i failus uztruko: " << laikmatis_failu_rasymo.elapsed() << " s" << endl;
    cout << "Sukurti failai: 'vargsiukai_vector_strat1.txt' ir 'galvociai_vector_strat1.txt'" << endl;
}

void suskirstyti(const std::list<Studentas>& Grupe) {
    char pasirinkimas;
    while (true) {
        cout << "Pasirinkite pagal ka suskirstyti studentus:\n" << " a - pagal vidurki\n b - pagal mediana\n"; cin >> pasirinkimas;
        if (pasirinkimas == 'a' || pasirinkimas == 'b') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    Laikmatis laikmatis_rusiavimo;
    std::list<Studentas> vargsiukai;
    std::list<Studentas> galvociai;
    for (auto& s : Grupe) {
        double galutinisRez = (pasirinkimas == 'a') ? s.Vidurkiorez : s.Medianosrez;
        if (galutinisRez < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }
    cout << std::fixed << std::setprecision(6) << "Studentu rusiavimas i dvi grupes (list) uztruko: " << laikmatis_rusiavimo.elapsed() << " s" << endl;
    char rikiavimas_pasirinkimas;
    while (true) {
        cout << "Pagal ka rikiuoti studentus faile?\n" << " a - pagal pavarde\n" << " b - pagal varda\n" << " c - pagal galutini pazymi\n"; cin >> rikiavimas_pasirinkimas;
        if (rikiavimas_pasirinkimas == 'a' || rikiavimas_pasirinkimas == 'b' || rikiavimas_pasirinkimas == 'c') break;
        else cout << "Ivesta neteisingai. Bandykite dar karta." << endl;
    }
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (rikiavimas_pasirinkimas == 'a') return a.pav < b.pav;
        else if (rikiavimas_pasirinkimas == 'b') return a.vard < b.vard;
        else {
            double galutinisA = (pasirinkimas == 'a') ? a.Vidurkiorez : a.Medianosrez;
            double galutinisB = (pasirinkimas == 'a') ? b.Vidurkiorez : b.Medianosrez;
            return galutinisA < galutinisB;
        }
    };
    vargsiukai.sort(rikiavimas);
    galvociai.sort(rikiavimas);
    Laikmatis laikmatis_failu_rasymo;
    std::ofstream foutv("vargsiukai_list_strat1.txt");
    std::ofstream foutg("galvociai_list_strat1.txt");
    for (auto& s : vargsiukai) {
        double galutinis = (pasirinkimas == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutv << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
    for (auto& s : galvociai) {
        double galutinis = (pasirinkimas == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutg << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
    foutv.close();
    foutg.close();
    cout << std::fixed << std::setprecision(6) << "Studentu isvedimas i failus uztruko: " << laikmatis_failu_rasymo.elapsed() << " s" << endl;
    cout << "Sukurti failai: 'vargsiukai_list_strat1.txt' ir 'galvociai_list_strat1.txt'" << endl;
}

void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    Laikmatis laikmatis_rusiavimo;
    std::vector<Studentas> vargsiukai, galvociai;
    for (auto& s : grupe) {
        double galutinis = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        if (galutinis < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.pav < b.pav;
        else if (pagalkarikiuoti == 'b') return a.vard < b.vard;
        else {
            double galutinisA = (pagalkaskirstyti == 'a') ? a.Vidurkiorez : a.Medianosrez;
            double galutinisB = (pagalkaskirstyti == 'a') ? b.Vidurkiorez : b.Medianosrez;
            return galutinisA < galutinisB;
        }
    };
    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);
    std::ofstream foutv("vargsiukai_vector_strat1.txt"), foutg("galvociai_vector_strat1.txt");
    for (auto& s : vargsiukai) {
        double galutinis = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutv << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
    for (auto& s : galvociai) {
        double galutinis = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutg << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
}

void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    Laikmatis laikmatis_rusiavimo;
    std::list<Studentas> vargsiukai, galvociai;
    for (auto& s : grupe) {
        double galutinis = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        if (galutinis < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.pav < b.pav;
        else if (pagalkarikiuoti == 'b') return a.vard < b.vard;
        else {
            double galutinisA = (pagalkaskirstyti == 'a') ? a.Vidurkiorez : a.Medianosrez;
            double galutinisB = (pagalkaskirstyti == 'a') ? b.Vidurkiorez : b.Medianosrez;
            return galutinisA < galutinisB;
        }
    };
    vargsiukai.sort(rikiavimas);
    galvociai.sort(rikiavimas);
    std::ofstream foutv("vargsiukai_list.txt"), foutg("galvociai_list.txt");
    for (auto& s : vargsiukai) {
        double galutinis = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutv << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
    for (auto& s : galvociai) {
        double galutinis = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutg << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << galutinis << "\n";
    }
}

void suskirstyti(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija) {
    Laikmatis laikmatis;
    if (strategija == 1) {
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti);
        return;
    }
    std::vector<Studentas> vargsiukai;
    for (auto it = grupe.begin(); it != grupe.end();) {
        double galutinis = (pagalkaskirstyti == 'a') ? it->Vidurkiorez : it->Medianosrez;
        if (galutinis < 5.0) {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        }
        else {
            ++it;
        }
    }
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.pav < b.pav;
        else if (pagalkarikiuoti == 'b') return a.vard < b.vard;
        else {
            double galA = (pagalkaskirstyti == 'a') ? a.Vidurkiorez : a.Medianosrez;
            double galB = (pagalkaskirstyti == 'a') ? b.Vidurkiorez : b.Medianosrez;
            return galA < galB;
        }
    };
    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(grupe.begin(), grupe.end(), rikiavimas);
    std::ofstream foutv("vargsiukai_vector_strat2.txt"), foutg("galvociai_vector_strat2.txt");
    for (auto& s : vargsiukai) {
        double gal = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutv << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gal << "\n";
    }
    for (auto& s : grupe) {
        double gal = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutg << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gal << "\n";
    }
}

void suskirstyti(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti, int strategija) {
    Laikmatis laikmatis;
    if (strategija == 1) {
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti);
        return;
    }
    std::list<Studentas> vargsiukai;
    for (auto it = grupe.begin(); it != grupe.end();) {
        double galutinis = (pagalkaskirstyti == 'a') ? it->Vidurkiorez : it->Medianosrez;
        if (galutinis < 5.0) {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        }
        else {
            ++it;
        }
    }
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.pav < b.pav;
        else if (pagalkarikiuoti == 'b') return a.vard < b.vard;
        else {
            double galA = (pagalkaskirstyti == 'a') ? a.Vidurkiorez : a.Medianosrez;
            double galB = (pagalkaskirstyti == 'a') ? b.Vidurkiorez : b.Medianosrez;
            return galA < galB;
        }
    };
    vargsiukai.sort(rikiavimas);
    grupe.sort(rikiavimas);
    std::ofstream foutv("vargsiukai_list_strat2.txt"), foutg("galvociai_list_strat2.txt");
    for (auto& s : vargsiukai) {
        double gal = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutv << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gal << "\n";
    }
    for (auto& s : grupe) {
        double gal = (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
        foutg << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gal << "\n";
    }
}

void suskirstyti_optimizuota(std::list<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    auto kopija1 = grupe;
    auto kopija2 = grupe;
    Laikmatis t1;
    suskirstyti(kopija1, pagalkaskirstyti, pagalkarikiuoti, 1);
    double laikas1 = t1.elapsed();
    Laikmatis t2;
    suskirstyti(kopija2, pagalkaskirstyti, pagalkarikiuoti, 2);
    double laikas2 = t2.elapsed();
    if (laikas1 <= laikas2) {
        cout << "List (strategija 3): greitesne buvo strategija 1, ji ir panaudota.\n";
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, 1);
    }
    else {
        cout << "List (strategija 3): greitesne buvo strategija 2, ji ir panaudota.\n";
        suskirstyti(grupe, pagalkaskirstyti, pagalkarikiuoti, 2);
    }
}

void suskirstyti_optimizuota_pirma(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    Laikmatis t;
    auto gauti_galutini = [&](const Studentas& s) {
        return (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
    };
    auto yra_vargsiukas = [&](const Studentas& s) { return gauti_galutini(s) < 5.0; };
    std::vector<Studentas> vargsiukai;
    std::remove_copy_if(grupe.begin(), grupe.end(), std::back_inserter(vargsiukai),
        [&](const Studentas& s) { return !yra_vargsiukas(s); });
    std::vector<Studentas> galvociai;
    std::remove_copy_if(grupe.begin(), grupe.end(), std::back_inserter(galvociai),
        [&](const Studentas& s) { return yra_vargsiukas(s); });
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.pav < b.pav;
        if (pagalkarikiuoti == 'b') return a.vard < b.vard;
        return gauti_galutini(a) < gauti_galutini(b);
    };
    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);
    std::ofstream fv("vargsiukai_vector_strat3.txt");
    std::ofstream fg("galvociai_vector_strat3.txt");
    std::for_each(vargsiukai.begin(), vargsiukai.end(), [&](const Studentas& s) {
        fv << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gauti_galutini(s) << "\n";
    });
    std::for_each(galvociai.begin(), galvociai.end(), [&](const Studentas& s) {
        fg << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gauti_galutini(s) << "\n";
    });
}

void suskirstyti_stl_antros_logika(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    Laikmatis t;
    auto gauti_galutini = [&](const Studentas& s) {
        return (pagalkaskirstyti == 'a') ? s.Vidurkiorez : s.Medianosrez;
    };
    auto yra_vargsiukas = [&](const Studentas& s) { return gauti_galutini(s) < 5.0; };
    auto partition_point = std::partition(grupe.begin(), grupe.end(), yra_vargsiukas);
    std::vector<Studentas> vargsiukai(grupe.begin(), partition_point);
    std::vector<Studentas> galvociai(partition_point, grupe.end());
    auto rikiavimas = [&](const Studentas& a, const Studentas& b) {
        if (pagalkarikiuoti == 'a') return a.pav < b.pav;
        if (pagalkarikiuoti == 'b') return a.vard < b.vard;
        return gauti_galutini(a) < gauti_galutini(b);
};
    std::sort(vargsiukai.begin(), vargsiukai.end(), rikiavimas);
    std::sort(galvociai.begin(), galvociai.end(), rikiavimas);
    std::ofstream fv("vargsiukai_vector_strat3.txt");
    std::ofstream fg("galvociai_vector_strat3.txt");
    std::for_each(vargsiukai.begin(), vargsiukai.end(), [&](const Studentas& s) {
        fv << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gauti_galutini(s) << "\n";
    });
    std::for_each(galvociai.begin(), galvociai.end(), [&](const Studentas& s) {
        fg << s.pav << " " << s.vard << " Galutinis: " << std::fixed << std::setprecision(2) << gauti_galutini(s) << "\n";
    });

}

void suskirstyti_optimizuota(std::vector<Studentas>& grupe, char pagalkaskirstyti, char pagalkarikiuoti) {
    auto kopija1 = grupe;
    auto kopija2 = grupe;
    Laikmatis t1;
    suskirstyti_optimizuota_pirma(kopija1, pagalkaskirstyti, pagalkarikiuoti);
    double laikas1 = t1.elapsed();
    Laikmatis t2;
    suskirstyti_stl_antros_logika(kopija2, pagalkaskirstyti, pagalkarikiuoti);
    double laikas2 = t2.elapsed();
    if (laikas1 <= laikas2) {
        cout << "Vector (strategija 3): greitesne buvo strategija 1, ji ir panaudota.\n";
        suskirstyti_optimizuota_pirma(grupe, pagalkaskirstyti, pagalkarikiuoti);
    }
    else {
        cout << "Vector (strategija 3): greitesne buvo strategija 2, ji ir panaudota.\n";
        suskirstyti_stl_antros_logika(grupe, pagalkaskirstyti, pagalkarikiuoti);
    }
}
