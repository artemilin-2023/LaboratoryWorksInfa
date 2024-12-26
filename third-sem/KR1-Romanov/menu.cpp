#include "menu.h"

#include "database.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <array>
#include <filesystem>

typedef void (*menu_entry_function)(db::database *);

namespace menu {
    struct MenuEntry {
        std::string name;
        menu_entry_function function;
    };

    bool extract_date(const std::string& date_string, time_t& out_time) {
        std::istringstream date_stream(date_string);
        std::tm input_time = {};
        date_stream >> std::get_time(&input_time, "%d/%m/%Y");
        if(date_stream.fail()) {
            return false;
        }
        input_time.tm_isdst = -1;
        // normalize: 29/02/2013 would become 01/03/2013 (not a leap year)
        std::tm normalized_time = input_time;
        out_time = mktime(&normalized_time);
        // validate (is the normalized date still the same?):
        return (input_time.tm_mday == normalized_time.tm_mday &&
                input_time.tm_mon == normalized_time.tm_mon &&
                input_time.tm_year == normalized_time.tm_year);

    }

    // returns true if there is no delimeter in input
    bool check_delimeter(const std::string& str) {
        if(str.find(';') != std::string::npos) {
            // found
            return false;
        }
        return true;
    }

    void add_row_from_terminal(db::database *db) {
        db::car_row car;
        std::cout << "Введите тип машины\n> ";
        std::getline(std::cin >> std::ws, car.car_type);
        if(!check_delimeter(car.car_type)) {
            std::cout << "Ввод не должен содержать знак ';'! Ничего не произошло\n";
            return;
        }
        std::cout << "Введите модель машины\n> ";
        std::getline(std::cin >> std::ws, car.car_model);
        if(!check_delimeter(car.car_model)) {
            std::cout << "Ввод не должен содержать знак ';'! Ничего не произошло\n";
            return;
        }
        std::cout << "Введите номер машины\n> ";
        std::getline(std::cin >> std::ws, car.car_plate);
        if(!check_delimeter(car.car_plate)) {
            std::cout << "Ввод не должен содержать знак ';'! Ничего не произошло\n";
            return;
        }
        std::cout << "Введите пассажиро/грузоподъемность машины\n> ";

        std::getline(std::cin >> std::ws, car.car_capacity);
        if(!check_delimeter(car.car_capacity)) {
            std::cout << "Ввод не должен содержать знак ';'! Ничего не произошло\n";
            return;
        }

        std::cout << "Введите дату следующего техосмотра в формате dd/mm/yyyy\n> ";
        std::string temp_date;
        std::getline(std::cin >> std::ws, temp_date);
        if(!extract_date(temp_date, car.next_inspection_date)) {
            std::cout << "Введена некорректная дата. Ничего не произошло\n";
            return;
        }

        std::cout << "Введите статус машины (1 - свободна, 2 - есть заказ, 3 - исполняет заказ, 4 - в ремонте)\n> ";
        int car_status;
        std::cin >> car_status;
        if(car_status < 1 || car_status >= db::car_status::MAX) {
            std::cout << "Неверный статус машины. Ничего не произошло\n";
            return;
        }
        car.car_status = static_cast<db::car_status>(car_status);

        std::cout << "Введите дату заказа в формате dd/mm/yyyy\n> ";
        std::getline(std::cin >> std::ws, temp_date);
        if(!extract_date(temp_date, car.order_date)) {
            std::cout << "Введена некорректная дата. Ничего не произошло\n";
            return;
        }
        std::cout << "Добавляем строку [" << db::format_row(car) << "] в базу данных\n";
        db::add_row(db, car);
    }

    void add_rows_from_file(db::database *db) {
        std::cout << "Введите путь до файла\n> ";
        std::string file_path;
        std::getline(std::cin >> std::ws, file_path, '\n');
        if(file_path.empty()) {
            std::cout << "Вы ввели пустой путь. Ничего не произошло\n";
            return;
        }

        std::filesystem::path output_path = file_path;
        if(!std::filesystem::exists(output_path)) {
            std::cout << "Путь не существует. Ничего не произошло\n";
            return;
        }
        std::cout << "Добавляем в базу строки из файла " << std::filesystem::absolute(output_path) << '\n';
        db::read_from_file(db, output_path);
    }

    void print_to_terminal(db::database *db) {
        db::print(db);
    }

    void save_to_file(db::database *db) {
        std::cout << "Введите путь до файла\n> ";
        std::string file_path;
        std::getline(std::cin >> std::ws, file_path, '\n');
        if(file_path.empty()) {
            std::cout << "Вы ввели пустой путь. Ничего не произошло\n";
            return;
        }
        auto output_path = std::filesystem::absolute(std::filesystem::path(file_path).lexically_normal());
        std::filesystem::create_directories(output_path.parent_path());
        std::cout << "Сохраняем базу в файл " << output_path << '\n';
        db::save_to_file(db, output_path);
    }

    void remove_one_row(db::database *db) {
        std::cout << "Введите номер удаляемого элемента (его можно узнать, выведя базу на экран)\n> ";
        int index;
        std::cin >> index;
        index--; // fix index
        if(index < 0 || index >= db::row_count(db)) {
            std::cout << "Такого номера в базе нет! Ничего не произошло\n";
            return;
        }
        db::erase(db, index);
    }

    void remove_all_rows(db::database *db) {
        std::cout << "Вы уверен, что хотите удалить всю базу из памяти? Проверьте, что она была сохранена на диск\n"
                     "Для подтверждения действия введите 1\n> ";
        int input;
        std::cin >> input;
        if(input != 1) {
            std::cout << "Ничего не произошло\n";
            return;
        }
        db::clear(db);
    }

    void sort_all_rows(db::database *db) {
        std::cout << "Введите поле для сортировки (1 - тип, 2 - марка, 3 - номер, 4 - вместимость, 5 - дата следующего техосмотра, 6 - состояние, 7 - дата заказа)\n> ";
        int sort_field;
        std::cin >> sort_field;
        using comp = bool(*)(const db::car_row &, const db::car_row &);
        comp comparison_function;
        switch (sort_field) {
            case 1: // type
            {
                comparison_function = [](const db::car_row& a, const db::car_row& b) {
                    return a.car_type < b.car_type;
                };
            }
                break;
            case 2: // model
            {
                comparison_function = [](const db::car_row& a, const db::car_row& b) {
                    return a.car_model < b.car_model;
                };
            }
                break;
            case 3: // plate
            {
                comparison_function = [](const db::car_row& a, const db::car_row& b) {
                    return a.car_plate < b.car_plate;
                };
            }
                break;
            case 4: // capacity
            {
                comparison_function = [](const db::car_row& a, const db::car_row& b) {
                    return a.car_capacity < b.car_capacity;
                };
            }
                break;
            case 5: // next_inspection_date
            {
                comparison_function = [](const db::car_row& a, const db::car_row& b) {
                    return a.next_inspection_date < b.next_inspection_date;
                };
            }
                break;
            case 6: // status
            {
                comparison_function = [](const db::car_row& a, const db::car_row& b) {
                    return a.car_status < b.car_status;
                };
            }
                break;
            case 7: // order_date
            {
                comparison_function = [](const db::car_row& a, const db::car_row& b) {
                    return a.order_date < b.order_date;
                };
            }
                break;
            default:
                std::cout << "Неверное поле для сортировки. Ничего не произошло\n";
                return;
        }
        db::sort(db, comparison_function);
    }

    void filter_rows(db::database *db) {
        std::cout << "Фильтрация удалит несоответствующие строки из памяти. Проверьте, что база была сохранена на диск\n";
        std::cout << "Выберите тип фильтрации:\n"
                     "1) содержится в строке\n"
                     "2) после даты\n"
                     "3) до даты\n"
                     "4) соответствует состоянию\n";

        int filter_type{};
        std::cin >> filter_type;
        switch (filter_type) {
            case 1: // string search
            {
                std::cout << "Выберите поле, в котором будет искаться подстрока:\n"
                             "1) тип машины\n"
                             "2) модель машины\n"
                             "3) номер машины\n"
                             "4) вместимость машины\n> ";
                int field_num{};
                std::cin >> field_num;
                if (field_num < 1 || field_num > 4) {
                    std::cout << "Некорректное поле. Ничего не произошло\n";
                    return;
                }
                std::cout << "Введите подстроку для поиска\n> ";
                std::string search_string;
                std::getline(std::cin >> std::ws, search_string, '\n');
                if (search_string == "") {
                    std::cout << "Подстрока не должна быть пустой!\n";
                    return;
                }
                switch (field_num) {
                    case 1: { // type
                        db::filter(db, [search_string](const db::car_row& row) -> bool {
                            return row.car_type.find(search_string) != std::string::npos;
                        });
                    }
                        break;
                    case 2: { // model
                        db::filter(db, [search_string](const db::car_row& row) -> bool {
                            return row.car_model.find(search_string) != std::string::npos;
                        });
                    }
                        break;
                    case 3: { // plates
                        db::filter(db, [search_string](const db::car_row& row) -> bool {
                            return row.car_plate.find(search_string) != std::string::npos;
                        });
                    }
                        break;
                    case 4: { // capacity
                        db::filter(db, [search_string](const db::car_row& row) -> bool {
                            return row.car_capacity.find(search_string) != std::string::npos;
                        });
                    }
                        break;
                    default: {
                        std::cout << "Некорректное поле. Ничего не произошло\n";
                        return;
                    }
                }
            }
                break;
            case 2: // after date
            {
                std::cout << "Выберите поле, по которому будет производиться фильтрация:\n"
                             "1) дата следующей инспекции\n"
                             "2) дата заказа\n> ";
                int field_num{};
                std::cin >> field_num;
                if (field_num < 1 || field_num > 2) {
                    std::cout << "Некорректное поле. Ничего не произошло\n";
                    return;
                }
                std::cout << "Введите дату в формате dd/mm/yyyy\n> ";
                std::string temp_date;
                std::getline(std::cin >> std::ws, temp_date);
                time_t filter_date;
                if(!extract_date(temp_date, filter_date)) {
                    std::cout << "Введена некорректная дата. Ничего не произошло\n";
                    return;
                }
                switch (field_num) {
                    case 1: { // inspection date
                        db::filter(db, [filter_date](const db::car_row& row) -> bool {
                            return std::difftime(row.next_inspection_date, filter_date) > 0;
                        });
                    }
                        break;
                    case 2: { // order date
                        db::filter(db, [filter_date](const db::car_row& row) -> bool {
                            return std::difftime(row.order_date, filter_date) > 0;
                        });
                    }
                        break;
                    default: {
                        std::cout << "Некорректное поле. Ничего не произошло\n";
                        return;
                    }
                }
            }
                break;
            case 3: // before date
            {
                std::cout << "Выберите поле, по которому будет производиться фильтрация:\n"
                             "1) дата следующей инспекции\n"
                             "2) дата заказа\n> ";
                int field_num{};
                std::cin >> field_num;
                if (field_num < 1 || field_num > 2) {
                    std::cout << "Некорректное поле. Ничего не произошло\n";
                    return;
                }
                std::cout << "Введите дату в формате dd/mm/yyyy\n> ";
                std::string temp_date;
                std::getline(std::cin >> std::ws, temp_date);
                time_t filter_date;
                if(!extract_date(temp_date, filter_date)) {
                    std::cout << "Введена некорректная дата. Ничего не произошло\n";
                    return;
                }
                switch (field_num) {
                    case 1: { // inspection date
                        db::filter(db, [filter_date](const db::car_row& row) -> bool {
                            return std::difftime(row.next_inspection_date, filter_date) < 0;
                        });
                    }
                        break;
                    case 2: { // order date
                        db::filter(db, [filter_date](const db::car_row& row) -> bool {
                            return std::difftime(row.order_date, filter_date) < 0;
                        });
                    }
                        break;
                    default: {
                        std::cout << "Некорректное поле. Ничего не произошло\n";
                        return;
                    }
                }
            }
                break;
            case 4: // status
            {
                std::cout << "Введите статус машины (1 - свободна, 2 - есть заказ, 3 - исполняет заказ, 4 - в ремонте)\n> ";
                int car_status;
                std::cin >> car_status;
                if(car_status < 1 || car_status >= db::car_status::MAX) {
                    std::cout << "Неверный статус машины. Ничего не произошло\n";
                    return;
                }
                db::car_status filter_status = static_cast<db::car_status>(car_status);

                db::filter(db, [filter_status](const db::car_row& row) -> bool {
                    return row.car_status == filter_status;
                });
            }
                break;
        }
    }

    void use_main_menu(db::database *db) {
        static std::array<MenuEntry, 8> entries {{
             {"добавить в базу одну строку из терминала", add_row_from_terminal},
             {"добавить в базу все строки из файла", add_rows_from_file},
             {"вывести базу на экран", print_to_terminal},
             {"сохранить базу в файл", save_to_file},
             {"удалить из базы одну строку", remove_one_row},
             {"очистить базу из памяти", remove_all_rows},
             {"отсортировать базу", sort_all_rows},
             {"найти строки", filter_rows},
        }};

        while (true) {
            if(std::cin.fail()) { // couldn't parse the data into an int
                std::cout << "Ошибка ввода. Ввод должен быть целым числом\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cout << "\nТекущий размер базы данных: " << db::row_count(db) << '\n';
            std::cout << "Выберите операцию:\n";
            std::cout << "-1) выйти из программы\n";
            // print all possible operations
            for (int i = 0; i < entries.size(); ++i) {
                std::cout << i+1 << ") " << entries[i].name << '\n';
            }
            std::cout << "> ";

            // 0 is also the default int value, so we can't put any operations on it. it'll get executed if parser fails
            int option = 0;
            std::cin >> option;

            // exit out of the loop
            if(option == -1) {
                std::cout << "Выход...\n";
                break;
            }
            option--; // fix index
            if(option < 0 || option >= entries.size()) {
                std::cout << "Неизвестная операция\n";
                continue;
            }
            // call the function
            entries[option].function(db);
        }
    }

}; // menu
