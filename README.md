# PBA_Labs
Лабораторные работы по курсу "Программирование и основы алгоритмизации" (КНИТУ-КАИ, ИКТЗИ, ПМИ, 01.03.02)

Всё, что связано с задачами и требованиями, можно найти в [отчёте](Report.pdf)
# Сборка лабораторных работ
Я использую систему сборки Ninja и компилятор clang++, тестов пока нет.
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
## Выбор реализации 3-й лабораторной работы
С помощью флага LAB3_IMPL можно выбрать вариант 3-й лабораторной работы (1 $\text{---}$ реализация при помощи написанной структуры Matrix "`USE_ONLY_MATRIX`", 2 $\text{---}$ используется Matrix и std::vector "`USE_VECTOR`", остальное $\text{---}$ ничего не используется, мы самостоятельно выделяем память, освобождаем). По умолчанию значение этого флага определено как 0.

Для того чтобы выбрать реализацию, нужно написать флаг:
```sh
mkdir build
cd build/
cmake -DLAB3_IMPL=1 ..
cmake --build .
```
В данном примере выбрана реализация "`USE_ONLY_MATRIX`", в консоли можно увидеть сообщение о выбранном варианте:
```
-- Collected libs: MIO;MDialogs
-- Using Implementation of Lab3 is USE_ONLY_MATRIX
-- Collected labs: LAB1;LAB2;LAB3;LAB4;LAB5;LAB6
```