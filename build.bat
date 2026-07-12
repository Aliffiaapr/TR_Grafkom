@echo off
echo Building TR_Grafkom...
C:\msys64\ucrt64\bin\g++.exe -g -Wall -I"C:\msys64\ucrt64\include" main.cpp gedungMuseum.cpp balok.cpp cagarBudaya.cpp gazeboKiri.cpp halaman.cpp objekBangku.cpp objekBangkuMeja.cpp objekBunga.cpp objekGanesha.cpp objekPembatas.cpp objekPohon.cpp objekRumahPutih.cpp objekSemak.cpp objekTaman.cpp -L"C:\msys64\ucrt64\lib" -lglfw3 -lopengl32 -lglu32 -lgdi32 -lwinmm -o main.exe 2>&1
if %ERRORLEVEL% EQU 0 (
    echo BUILD SUCCESS!
) else (
    echo BUILD FAILED with error code %ERRORLEVEL%
)
