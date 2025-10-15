Testavimo sistema:
CPU: Intel(R) Core(TM) i7-8650U CPU @ 1.90GHz 2.11 GHz
RAM: 16,0 GB (15,9 GB usable)
HDD (magnetinis, SSD): 238 GB SSD SAMSUNG MZVLW256HEHP-000L7

Testavimo failai:
studentai1000.txt
studentai10000.txt
studentai100000.txt
studentai1000000.txt
studentai10000000.txt

Testavimo rezultatai:
Konteineris  Failas                 Nuskaitymas (s)   Rusiavimas (s)  Irasymas (s)  Bendras (s)  
------------------------------------------------------------------------------------------------
vector       studentai1000.txt      0.009215          0.063107        0.003423      0.075745     
list         studentai1000.txt      0.007791          0.056000        0.003753      0.067545     
vector       studentai10000.txt     0.056328          0.028248        0.024242      0.108818     
list         studentai10000.txt     0.061698          0.022587        0.023189      0.107475     
vector       studentai100000.txt    0.449331          0.187792        0.162255      0.799378     
list         studentai100000.txt    0.482868          0.218402        0.212199      0.913468     
vector       studentai1000000.txt   6.390637          1.855994        2.054081      10.300712    
list         studentai1000000.txt   5.495589          2.771440        2.771307      11.038336    
vector       studentai10000000.txt  51.483759         19.294265       20.425165     91.203189    
list         studentai10000000.txt  52.409604         31.105185       30.783026     114.297815   
