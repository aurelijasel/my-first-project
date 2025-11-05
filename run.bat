cmake CmakeLists.txt
cmake --install .
cmake --build .
copy src\studentai*.txt Debug\studentai*.txt
cd Debug\
Studentu_rusiavimo_programa.exe
pause