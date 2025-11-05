# Studentų duomenų apdorojimo ir analizės programa

Ši programa leidžia:
- įvesti, generuoti, nuskaityti ir apdoroti studentų pažymius,
- suskirstyti studentus į dvi grupes (vargsiukai ir galvociai),
- pasirinkti skirtingas vieną iš trijų strategijų duomenų apdorojimui,
- palyginti vector ir list konteinerių veikimo spartą ir atminties panaudojimą,
- matuoti skirtingų operacijų (nuskaitymo, įrašymo) laikus.


## Naudojimosi instrukcija

### Programos atsisiuntimas
1. Parsisiųsti cmake zip programą (ne ankstesnę, nei 3.25.0 versiją): https://cmake.org/download/
2. Zip failą išskleisti savo kompiuteryje. Rasti jame aplanką pavadinimu "bin" ir iš to aplanko išsisaugoti failą cmake.exe.
3. Atsisiųsti CMakeLists.txt, run.bat, .cpp ir .h failus iš GitHub.
4. Kompiuteryje sukurti aplanką pavadintą "cmaketest". Į jį įkelti CMakeLists.txt, run.bat, cmake.exe failus.
5. "cmaketest" aplanke sukurti du aplankus: "src", "include". Į "src" aplanką įkelti .cpp failus, o į "include" - .h failus.
6. Programą paleisti naudojant terminalą, įvedant komandas:
```
cmake .\CMakeLists.txt
```
```
cmake --build .
```
```
cd Debug
```
```
.\Studentu_rusiavimo_programa.exe
``` 

### Paleidimas
1. Atsidarykite projektą.  
2. Sukompiliuokite ir paleiskite failą v1.0.cpp.  
3. Pasirinkite vieną iš režimų:
```
1 - Iprastas programos veikimas
2 - Automatinis testavimas (vector vs list)
```

### Įprastas režimas
Leidžia įvesti studentus:
- rankiniu būdu,  
- automatiškai sugeneruoti,  
- nuskaityti iš failo.

Tada galima pasirinkti:
- su kokiu konteineriu rūšiuoti studentas (vector / list),
- pagal ką skaičiuoti galutinį pažymį (vidurkį / medianą / abu),
- pagal ką rikiuoti (vardą / pavardę / pažymį).

Rezultatai įrašomi į rezultatai.txt bei sugeneruojami du failai:
```
vargsiukai_*_strat1.txt
galvociai_*_strat1.txt
```

### Automatinis testavimas
Šiuo režimu programa automatiškai paleidžia našumo testus su skirtingais failais:
```
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt
```
Galima pasirinkti:
- pagal kokią strategiją vykdyti testavimą,
- pagal ką suskirstyti (vidurkį / medianą),
- pagal ką rikiuoti (vardą / pavardę / pažymį),

Rezultatai įrašomi į testavimorezultatai.txt.


## Strategijų aprašymas

| Strategija | Aprašymas |
|-------------|------------|
| **1** | Sukuriami du nauji konteineriai: vienas vargšiukams, kitas galvočiams. |
| **2** | Sukuriamas tik vienas naujas konteineris. Vargšiukai ištrinami iš bendro sąrašo. |
| **3** | Optimizuota versija – naudojami STL algoritmai ir efektyvus konteinerių tvarkymas. |

## Testavimo aplinka

**Testavimo sistema:**
```
CPU: Intel(R) Core(TM) i7-8650U CPU @ 1.90GHz 2.11 GHz
RAM: 16,0 GB (15,9 GB usable)
HDD: 238 GB SSD SAMSUNG MZVLW256HEHP-000L7
```

**Testuoti failai:**
```
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt
```


**Strategija 1 – Du nauji konteineriai**

| Konteineris | Failas | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.015827 | 0.013010 | 0.004352 | 0.033189 | 188412 |
| list | studentai1000.txt | 0.016332 | 0.015271 | 0.004227 | 0.035830 | 87256 |
| vector | studentai10000.txt | 0.126357 | 0.058128 | 0.031747 | 0.216232 | 1998444 |
| list | studentai10000.txt | 0.126573 | 0.062002 | 0.032832 | 0.221407 | 832056 |
| vector | studentai100000.txt | 0.957551 | 0.415778 | 0.328320 | 1.701649 | 21620012 |
| list | studentai100000.txt | 0.942920 | 0.501871 | 0.340209 | 1.785000 | 8182204 |
| vector | studentai1000000.txt | 6.804002 | 1.842711 | 1.954002 | 10.600715 | 216012312 |
| list | studentai1000000.txt | 6.201284 | 2.701446 | 2.874028 | 11.776758 | 81817132 |
| vector | studentai10000000.txt | 54.182993 | 19.913085 | 20.829315 | 94.925393 | 2160000120 |
| list | studentai10000000.txt | 53.942888 | 30.774006 | 30.003270 | 114.720164 | 818177624 |

**Strategija 2 – Vienas naujas konteineris**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.008800 | 0.007686 | 0.016487 | 186652 |
| list | studentai1000.txt | 0.009662 | 0.004400 | 0.014062 | 85556 |
| vector | studentai10000.txt | 0.078292 | 0.419455 | 0.497747 | 1999556 |
| list | studentai10000.txt | 0.100894 | 0.043024 | 0.143919 | 832316 |
| vector | studentai100000.txt | 0.955422 | 65.289058 | 66.244481 | 21625972 |
| list | studentai100000.txt | 1.414147 | 0.436104 | 1.850251 | 8182596 |
| vector | studentai1000000.txt | 7.382457 | 90.734936 | 98.117393 | 123318640 |
| list | studentai1000000.txt | 6.611306 | 8.723771 | 15.335077 | 82075436 |
| vector | studentai10000000.txt | 66.730549 | 140.426712 | 207.157261 | 2483700352 |
| list | studentai10000000.txt | 69.522376 | 69.699507 | 139.221883 | 821451136 |

**Strategija 3 – Optimizuota (naudojami STL algoritmai)**

| Konteineris | Failas | Nuskaitymas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.009535 | 0.037019 | 0.046554 | 234888 |
| list | studentai1000.txt | 0.019894 | 0.054275 | 0.074170 | 85556 |
| vector | studentai10000.txt | 0.163339 | 0.153464 | 0.316804 | 2502376 |
| list | studentai10000.txt | 0.136406 | 0.170332 | 0.306738 | 832316 |
| vector | studentai100000.txt | 0.980177 | 1.228347 | 2.208524 | 26778544 |
| list | studentai100000.txt | 0.852115 | 1.642650 | 2.494766 | 14000016 |
| vector | studentai1000000.txt | 13.513278 | 12.871179 | 26.384458 | 233186400 |
| list | studentai1000000.txt | 16.078031 | 19.183705 | 35.261737 | 82075436 |
| vector | studentai10000000.txt | 146.382746 | 167.735478 | 314.118225 | 2483700352 |
| list | studentai10000000.txt | 154.682915 | 218.426093 | 373.109009 | 821451136 |

Dažniausiai buvo greičiau naudoti 2 strategiją.

**Išvados**

- Mažiems duomenų kiekiams (1000–10000) vector ir list veikimas trunka panašiai.  
- Didėjant įrašų kiekiui, vector tampa efektyvesnis – greitesnis bendras veikimo laikas.  
- Vector konteineris sunaudoja daugiau atminties.   
- 2 strategija labai neefektyvi su dideliais duomenų kiekiais (1000000 ir 10000000 įrašų), nes ji kiekvienam vargšiukui naudoja erase() funkciją vector konteineryje. Kiekvienas erase() kvietimas perstumia visus likusius elementus, todėl operacijos sudėtingumas tampa O(n²).


## Rankinis įvedimas

Įvedus studento duomenis rankiniu būdu, ekrane matomas objekto saugojimo atminties adresas:

**Vector atveju:**
```
Iveskite 1 studenta
Iveskite pavarde: Jonaitis
Iveskite varda: Jonas
Iveskite pazymi: 6
Ar norite ivesti dar viena pazymi? (taip/ne): ne
Iveskite egzamina: 7
Studento objektas saugomas adresu: 000002AF25106120
```

**List atveju:**
```
Iveskite 1 studenta
Iveskite pavarde: Jonaitis
Iveskite varda: Jonas
Iveskite pazymi: 6
Ar norite ivesti dar viena pazymi? (taip/ne): ne
Iveskite egzamina: 7
Studento objektas saugomas adresu: 0000022402A862D0
```


## Release istorija

| Versija | Aprašymas |
|----------|------------|
| v.pradinė | Programa leidžia įvesti studentų duomenis, apskaičiuoti galutinį balą pagal vidurkį, medianą arba abu. |
| v0.1 | Pridėta duomenų nuskaitymo iš failo galimybė ir išvedimo formatavimas. |
| v0.2 | Pridėta atsitiktinė duomenų failų generacija ir veikimo trukmės (failų kūrimo, skaitymo, rūšiavimo) matavimas. |
| v0.3 | Pridėtas konteinerių (vector ir list) veikimo trukmės palyginimas. |
| v1.0 | Pridėtas 3 strategijų (rūšiavimo metodų) palyginimas tiek vector, tiek list. |
