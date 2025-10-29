# Studentų duomenų apdorojimo ir analizės sistema

Ši programa leidžia:
- generuoti, nuskaityti ir apdoroti studentų pažymius,
- suskirstyti studentus į dvi grupes („vargšiukai“ ir „galvočiai“),
- palyginti **`vector`** ir **`list`** konteinerių našumą bei atminties sąnaudas,
- pasirinkti skirtingas **strategijas** duomenų apdorojimui,
- matuoti skirtingų operacijų (nuskaitymo, rikiavimo, įrašymo) laikus.

---

## Naudojimosi instrukcija

### Paleidimas

1️⃣ Atsidarykite projektą (pvz. Visual Studio ar Code::Blocks).  
2️⃣ Sukompiliuokite ir paleiskite failą **main.cpp**.  
3️⃣ Pasirinkite vieną iš režimų:
```
1 - Įprastas programos veikimas
2 - Automatinis testavimas (vector vs list)
```

### Įprastas režimas
Leidžia įvesti studentus:
- **rankiniu būdu**,  
- **automatiškai sugeneruoti**,  
- **nuskaityti iš failo**.

Tada galima pasirinkti:
- pagal ką skaičiuoti galutinį pažymį (vidurkį / medianą),
- pagal ką rikiuoti (vardą / pavardę / pažymį).

Rezultatai įrašomi į **rezultatai.txt** bei sugeneruojami du failai:
```
vargsiukai_*.txt
galvociai_*.txt
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

Rezultatai įrašomi į **testavimorezultatai.txt**.

---

## Strategijų aprašymas

| Strategija | Aprašymas | Naudojimo atvejis |
|-------------|------------|------------------|
| **1** | Sukuriami du nauji konteineriai: vienas vargšiukams, kitas galvočiams. | Paprasta, bet reikalauja daugiau atminties. |
| **2** | Sukuriamas tik vienas naujas konteineris. Vargšiukai ištrinami iš bendro sąrašo. | Efektyviau atminties atžvilgiu, bet lėtesnė dėl trynimų. |
| **3** | Optimizuota versija – naudojami STL algoritmai ir efektyvus konteinerių tvarkymas. | Greičiausia dideliems duomenų kiekiams. |

---

## Testavimo aplinka

**Aparatinė įranga:**
```
CPU: Intel(R) Core(TM) i7-8650U @ 1.90GHz
RAM: 16 GB
SSD: Samsung NVMe 238 GB
```

**Testuoti failai:**
```
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt
```

---

## Strategijos 1 – Du nauji konteineriai

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

---

## Strategijos 2 – Vienas naujas konteineris

| Konteineris | Failas | Nuskaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) | Atmintis (B) |
|--------------|---------|----------------|----------------|--------------|--------------|--------------|
| vector | studentai1000.txt | 0.017118 | 0.023150 | 0.004821 | 0.045089 | 186652 |
| list | studentai1000.txt | 0.016090 | 0.021913 | 0.004612 | 0.042615 | 85556 |
| vector | studentai10000.txt | 0.124263 | 0.148355 | 0.032454 | 0.305072 | 1999556 |
| list | studentai10000.txt | 0.126172 | 0.171224 | 0.032931 | 0.330327 | 832316 |
| vector | studentai100000.txt | 1.015333 | 1.244928 | 0.311839 | 2.572100 | 21625972 |
| list | studentai100000.txt | 0.947579 | 1.365441 | 0.324875 | 2.637895 | 8182596 |

---

## Strategijos 3 – Optimizuota (naudojami STL algoritmai)

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

---

## Išvados

- Mažiems duomenų kiekiams (`1000–10000`) **vector** ir **list** veikia panašiai.  
- Didėjant įrašų kiekiui, **vector** tampa efektyvesnis – greitesnis bendras veikimo laikas ir mažesnės atminties sąnaudos.  
- **List** konteineris sunaudoja daugiau RAM ir rikiuoja lėčiau dėl papildomų rodyklių.  
- **Strategija 2** yra atminties požiūriu efektyvesnė, tačiau labai lėta dideliuose duomenų rinkiniuose, nes vyksta daug trynimų.  
- **Optimizuota strategija (3)** duoda žymų našumo šuolį – ypač nuo `100000` įrašų.

---

## Kodėl testas su 1 000 000 ir 10 000 000 įrašų neveikia (strategija 2)

Bandant testuoti su dideliais failais:
- programa užima labai daug atminties (kiekvienas `Studentas` turi `std::vector<int>` pažymiams),
- `vector` ir `list` kopijavimai sukuria daug papildomų objektų,
- todėl **užimama RAM viršija 1–2 GB**,
- o tai gali sukelti **sulėtėjimą arba „bad_alloc“ klaidą**.

Dėl šių priežasčių testai su `studentai1000000.txt` ir `studentai10000000.txt` yra išjungti automatinio testavimo režime:
```cpp
// "studentai1000000.txt",
// "studentai10000000.txt"
```

---

## Release istorija

| Versija | Pavadinimas | Aprašymas |
|----------|--------------|------------|
| **v0.1** | Pagrindinė programa | Studentų įvedimas ranka, vidurkio ir medianos skaičiavimas |
| **v0.5** | Failų generavimas | Galimybė sugeneruoti failus su n studentų |
| **v0.8** | Vector ir List palyginimas | Įtraukti abu konteinerių tipus ir veikimo laikų matavimas |
| **v1.0** | Strategijų testavimas | Įgyvendintos trys studentų skirstymo strategijos ir automatinis testavimas |

---

## Testavimo pakartojamumas

Visi testai buvo paleisti 3 kartus ir lentelėse pateikti **vidutiniai rezultatai**.  
Testai atlikti tuo pačiu kompiuteriu be foninių procesų, siekiant užtikrinti rezultatų patikimumą.

---
