# PBA_Labs
Лабораторные работы по курсу "Программирование и основы алгоритмизации" (КНИТУ-КАИ, ИКТЗИ, ПМИ, 01.03.02)

Всё, что связано с задачами и требованиями, можно найти в [отчёте](Report.pdf)
# Сборка лабораторных работ
Я использую систему сборки ninja и компилятор clang++, тестов пока нет.
Используя данные команды, вы можете собрать проект (компилятор и сборщик в CmakeLists.txt я не изменял):
```sh
mkdir build
cd build/
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -G "Ninja" ..
cmake --build .
```
Также проект собирается и с помощью VS 17 (MSVC):
```sh
mkdir build
cd build/
cmake -G "Visual Studio 17 2022" ..
cmake --build . 
```