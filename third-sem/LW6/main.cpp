/******************************************************************
*                     КАФЕДРА № 304 2 КУРС                        *
*-----------------------------------------------------------------*
* Project Type  : Win32 Console Application                       *
* Project Name  : BinarySearchTrees                               *
* File Name     : main.cpp                                        *
* Language      : C/C++                                           *
* Programmer(s) : Романов Д.И., Ильин А.А                         *
* Modified By   :                                                 *
* Created       : 20/09/2024                                      *
* Last Revision : 15/11/2024                                      *
* Comment(s)    : Бинарные деревья поиска                         *
******************************************************************/

#include <iostream>

#include "binary_tree.h"
#include "helpers.h"
#include "random_tree.h"

const int ARR_LEN = 24;
const int ARR_MIN = 1;
const int ARR_MAX = 90;

int main() {
    std::cout << "Лабораторная работа №2 - Бинарные деревья поиска\n";
    std::cout << "    Вариант №9\n";

    btree::node *binary_tree{nullptr};
    rtree::node *random_tree{nullptr};
    std::cout << "Созданы пустые деревья\n";
    bool exit = false;
    while (!exit) {
        if(std::cin.fail()) {
            std::cout << "Ошибка ввода. Ввод должен быть целым числом\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cout << "1: " << binary_tree << '\n';
        std::cout << "2: " << random_tree << '\n';
        std::cout << "\nВыберите операцию:\n";
        std::cout << "-1) выйти из программы\n";
        std::cout << "1) вставить элемент в деревья\n";
        std::cout << "2) удалить элемент из деревьев\n";
        std::cout << "3) очистить деревья\n";
        std::cout << "4) вывести высоты деревьев\n";
        std::cout << "5) вывести количество узлов в деревьях\n";
        std::cout << "6) прямой обход деревьев\n";
        std::cout << "7) центрированный обход деревьев\n";
        std::cout << "8) обратный обход деревьев\n";
        std::cout << "9) обход деревьев в ширину\n";
        std::cout << "10) вывести деревья\n";
        std::cout << "11) найти два минимальных и два максимальных элемента\n";
        std::cout << "12) случайно заполнить деревья\n";

        std::cout << "Из них по заданию варианта:\n";
        std::cout << "4) вывести высоты деревьев\n";
        std::cout << "11) найти два минимальных и два максимальных элемента\n";
        std::cout << "12) случайно заполнить деревья\n";

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
                int new_el;
                std::cin >> new_el;
                std::cout << "Вставляем " << new_el << " в деревья\n> ";
                binary_tree = btree::insert(binary_tree, new_el);
                random_tree = rtree::insert(random_tree, new_el);
            }
                break;
            case 2: {
                std::cout << "Введите значение удаляемого элемента\n> ";
                int el;
                std::cin >> el;
                std::cout << "Удаляем " << el << " из деревьев\n";
                binary_tree = btree::erase(binary_tree, el);
                std::cout << "Удаление элемента из случайного дерева не реализовано!\n";
                //random_tree = rtree::erase(random_tree, el);
            }
                break;
            case 3: {
                std::cout << "Очищаем деревья\n";
                binary_tree = btree::clear(binary_tree);
                random_tree = rtree::clear(random_tree);
            }
                break;
            case 4: {
                std::cout << "Высота бинарного дерева: " << btree::height(binary_tree) << '\n';
                std::cout << "Высота случайного дерева: " << rtree::height(random_tree) << '\n';
            }
                break;
            case 5: {
                std::cout << "Количество элементов в бинарном дереве: " << btree::node_count(binary_tree) << '\n';
                std::cout << "Количество элементов в случайном дереве: " << rtree::node_count(random_tree) << '\n';
            }
                break;
            case 6: {
                std::cout << "Прямой обход бинарного дерева: ";
                btree::print_preorder(binary_tree);
                std::cout << "Прямой обход случайного дерева: ";
                rtree::print_preorder(random_tree);
            }
                break;
            case 7: {
                std::cout << "Центрированный обход бинарного дерева: ";
                btree::print_inorder(binary_tree);
                std::cout << "Центрированный обход случайного дерева: ";
                rtree::print_inorder(random_tree);
            }
                break;
            case 8: {
                std::cout << "Обратный обход бинарного дерева: ";
                btree::print_postorder(binary_tree);
                std::cout << "Обратный обход случайного дерева: ";
                rtree::print_postorder(random_tree);
            }
                break;
            case 9: {
                std::cout << "Обход бинарного дерева в ширину: ";
                btree::print_levelorder(binary_tree);
                std::cout << "Обход случайного дерева в ширину: ";
                rtree::print_levelorder(random_tree);
            }
                break;
            case 10: {
                std::cout << "Бинарное дерево:\n";
                btree::print_tree(binary_tree);
                std::cout << "Случайное дерево:\n";
                rtree::print_tree(random_tree);
            }
                break;
            case 11: {
                std::cout << "Бинарное дерево:\n";
                {
                    auto [min, min_2, max_2, max] = btree::min_max_2(binary_tree);
                    std::cout << "Самый минимальный элемент: " << min->key << '\n';
                    std::cout << "Второй минимальный элемент: " << min_2->key << '\n';
                    std::cout << "Второй максимальный элемент: " << max_2->key << '\n';
                    std::cout << "Самый максимальный элемент: " << max->key << '\n';
                }
                std::cout << "Случайное дерево:\n";
                {
                    auto [min, min_2, max_2, max] = btree::min_max_2(binary_tree);
                    std::cout << "Самый минимальный элемент: " << min->key << '\n';
                    std::cout << "Второй минимальный элемент: " << min_2->key << '\n';
                    std::cout << "Второй максимальный элемент: " << max_2->key << '\n';
                    std::cout << "Самый максимальный элемент: " << max->key << '\n';
                }
            }
                break;
            
            case 12: {
                std::cout << "Добавляем в дерево " << ARR_LEN << " случайных элементов в интервале " << ARR_MIN << " - " << ARR_MAX << "\n";
                auto vec = generate_array(ARR_LEN, ARR_MIN, ARR_MAX);

                std::cout << "Сгенерированный массив: ";

                for (auto val: vec) {
                    std::cout << val << ' ';
                }
                std::cout << '\n';


                srand(1);
                for (auto val: vec) {
                    binary_tree = btree::insert(binary_tree, val);
                }
                
                std::cout << "Бинарное дерево поиска. Высота: " << btree::height(binary_tree) << "\n";
                btree::print_tree(binary_tree);

                srand(1);
                rtree::node *random_tree{nullptr};
                for (auto val: vec) {
                    random_tree = rtree::insert(random_tree, val);
                }

                std::cout << "Случайное бинарное дерево поиска. Высота: " << rtree::height(random_tree) << "\n";
                rtree::print_tree(random_tree);
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
