# Studentų duomenų apdorojimo ir analizės programa

Ši programa leidžia:
- įvesti, generuoti, nuskaityti ir apdoroti studentų pažymius,
- suskirstyti studentus į dvi grupes (vargsiukai ir galvociai),
- pasirinkti skirtingas vieną iš trijų strategijų duomenų apdorojimui,
- palyginti vector ir list konteinerių veikimo spartą ir atminties panaudojimą,
- matuoti skirtingų operacijų (nuskaitymo, įrašymo) laikus.


## Naudojimosi instrukcija

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

| Konteineris | Failas | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.009201 | 0.005212 | 0.003400 | 0.017813 | 185624 |
| list | studentai1000.txt | 0.007832 | 0.006012 | 0.003853 | 0.017697 | 84512 |
| vector | studentai10000.txt | 0.056382 | 0.028256 | 0.024200 | 0.108838 | 1987452 |
| list | studentai10000.txt | 0.061721 | 0.022647 | 0.023213 | 0.107581 | 829872 |
| vector | studentai100000.txt | 0.449357 | 0.187872 | 0.162341 | 0.799570 | 21608456 |
| list | studentai100000.txt | 0.482937 | 0.218415 | 0.212284 | 0.913636 | 8181776 |
| vector | studentai1000000.txt | 6.390602 | 1.856057 | 2.054183 | 10.300842 | 216012312 |
| list | studentai1000000.txt | 5.495668 | 2.771405 | 2.771391 | 11.038464 | 81817132 |
| vector | studentai10000000.txt | 51.483884 | 19.294318 | 20.425229 | 91.203431 | 2160000120 |
| list | studentai10000000.txt | 52.409655 | 31.105266 | 30.783094 | 114.297015 | 818177624 |

Dažniausiai list buvo greičiau naudoti 2 strategiją.

**Išvados**

- Mažiems duomenų kiekiams (1000–10000) vector ir list veikimas trunka panašiai.  
- Didėjant įrašų kiekiui, vector tampa efektyvesnis – greitesnis bendras veikimo laikas.  
- Vector konteineris sunaudoja daugiau atminties.   
- 2 strategija labai neefektyvi su dideliais duomenų kiekiais (1000000 ir 10000000 įrašų), nes ji kiekvienam vargšiukui naudoja erase() funkciją vector konteineryje. Kiekvienas erase() kvietimas perstumia visus likusius elementus, todėl operacijos sudėtingumas tampa O(n²).
- Optimizuota strategija (3) yra efektyviausia.


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
