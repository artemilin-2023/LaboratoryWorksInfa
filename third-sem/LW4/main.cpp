/******************************************************************
*                     КАФЕДРА № 304 2 КУРС                        *
*-----------------------------------------------------------------*
* Project Type  : Win32 Console Application                       *
* Project Name  : LinkedList                                      *
* File Name     : main.cpp                                        *
* Language      : C/C++                                           *
* Programmer(s) : Романов Д.И., Ильин А.А                         *
* Modified By   :                                                 *
* Created       : 20/09/2024                                      *
* Last Revision : 15/11/2024                                      *
* Comment(s)    : Линейные списки                                 *
******************************************************************/

#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>

#include "linked_list.h"

void fill_linked_list(llist::linked_list& list, int size = 20, float min = -50, float max = 50);

int main() {
    std::cout << "Лабораторная работа №4 - Линейные списки\n";
    std::cout << "    Вариант №8\n";

    llist::linked_list list{};

    std::cout << "Создан пустой список\n";
    bool exit = false;
    while (!exit) {
        if(std::cin.fail()) {
            std::cout << "Ошибка ввода. Ввод должен быть целым числом\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cout << "\nВыберите операцию:\n";
        std::cout << "-1) выйти из программы\n";
        std::cout << "1) вставить элемент в начало списка\n";
        std::cout << "2) вставить элемент в конец списка\n";
        std::cout << "3) вставить элемент в заданную позицию списка\n";
        std::cout << "4) удалить элемент из начала списка\n";
        std::cout << "5) удалить элемент из конца списка\n";
        std::cout << "6) удалить элемент из заданной позиции списка\n";
        std::cout << "7) очистить список\n";
        std::cout << "8) найти максимальный элемент списка\n";
        std::cout << "9) вывести список\n";
        std::cout << "10) случайно заполнить список\n";
        std::cout << "Из них по заданию варианта:\n";
        std::cout << "8) найти максимальный элемент списка\n";
        std::cout << "3) вставить элемент в заданную позицию списка\n";
        std::cout << "5) удалить элемент из конца списка\n";
        std::cout << "> ";
        int option = 0;
        std::cin >> option;
        switch (option) {
            case -1: {
                std::cout << "Выход...\n";
                exit = true;
            }
                break;
            case 1: {
                std::cout << "Введите значение нового элемента\n> ";
                float new_el;
                std::cin >> new_el;
                std::cout << "Вставляем " << new_el << " в начало\n> ";
                list.push_front(new_el);
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            case 2: {
                std::cout << "Введите значение нового элемента\n> ";
                float new_el;
                std::cin >> new_el;
                std::cout << "Вставляем " << new_el << " в конец\n> ";
                list.push_back(new_el);
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            case 3: {
                std::cout << "Введите значение нового элемента\n> ";
                float new_el;
                std::cin >> new_el;
                std::cout << "Введите индекс нового элемента. "
                             "Он будет вставлен перед элементом с соответствующим индексом\n> ";
                int new_index;
                std::cin >> new_index;
                std::cout << "Вставляем " << new_el << " перед " << new_index << "-м \n> ";
                list.insert(new_index, new_el);
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            case 4: {
                std::cout << "Удаляем первый элемент " << list.begin()->data << '\n';
                list.pop_front();
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            case 5: {
                std::cout << "Удаляем последний элемент " << list.end()->data << '\n';
                list.pop_back();
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            case 6: {
                std::cout << "Введите индекс удаляемого элемента\n> ";
                int index;
                std::cin >> index;
                std::cout << "Удаляем " << index << "-й элемент \n";
                list.erase(index-1);
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            case 7: {
                std::cout << "Очищаем список\n";
                list.clear();
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            case 8: {
                std::cout << "Находим максимальный элемент списка\n";
                int max_i;
                llist::node *max_node = list.max(max_i);
                std::cout << "Это " << max_node->data << " на месте " << max_i << '\n';
            }
                break;
            case 9: {
                std::cout << "Введите название файла для сохранения или "
                             "оставьте строку пустой, что бы вывести в консоль\n> ";
                std::string filename;
                std::cin.ignore();
                std::getline(std::cin   , filename);
                if(filename.empty()) {
                    std::cout << "Содержание списка: " << list << '\n';
                } else {
                    auto output_path = std::filesystem::current_path().replace_filename(filename);
                    std::cout << "Сохраняем содержание списка в файл " << output_path << '\n';
                    std::ofstream fout(output_path);
                    fout << list << '\n';
                }
            }
                break;
            case 10: {
                std::cout << "Добавляем в список 20 случайных элементов в интервале -50 - 50\n";
                fill_linked_list(list);
                std::cout << "Содержание списка: " << list << '\n';
            }
                break;
            default: {
                std::cout << "Неизвестная операция\n";
            }
                break;
        }
    }
    return 0;
}

void fill_linked_list(llist::linked_list& list, int size, float min, float max) {
    std::random_device rd;
    auto random_number = rd();
//    unsigned random_number = 150444277;
    std::mt19937 gen(random_number);
    std::uniform_real_distribution<float> dist(min, max);
    for (int i = 0; i < size; ++i) {
        list.push_back(dist(gen));
    }
}
