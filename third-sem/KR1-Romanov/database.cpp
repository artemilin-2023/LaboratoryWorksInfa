#include "database.h"

#include <fstream>

namespace db {

    std::string format_status(const car_status &status) {
        switch (status) {
            case free:
                return "свободна";
            case has_order:
                return "есть заказ";
            case fulfilling_order:
                return "исполняет заказ";
            case in_repair:
                return "в ремонте";
            case MAX:
                return "неизвестно";
            default:
                return "неизвестно";
        }
    }

    std::string format_row(const car_row &car) {
        std::ostringstream out{};
        out
                << car.car_type << ';'
                << car.car_model << ';'
                << car.car_plate << ';'
                << car.car_capacity << ';'
                << std::put_time(std::localtime(&car.next_inspection_date), "%d/%m/%Y") << ';'
                << format_status(car.car_status) << ';'
                << std::put_time(std::localtime(&car.order_date), "%d/%m/%Y");

        return out.str();
    }

    int row_count(database *db) {
        return db->_list.size();
    }

    void add_row(database *db, const car_row &new_row) {
        db->_list.push_back(new_row); // copied inside
    }

#pragma region parsing

    void print_err(size_t line_num, const std::string &reason) {
        std::cout << "!Ошибка! Строка:" << std::setw(4) << line_num << ". " << reason << "\n";
    }

    bool check_fail(
            std::istream &stream, size_t line_num,
            const std::string &reason = "Недостаточно данных: преждевременно достигнут конец строки.") {
        if (stream.fail()) {
            std::cout << '\n';
            print_err(line_num, reason);
            return true;
        }
        return false;
    }

    bool check_eof(
            std::istream &stream, size_t line_num,
            const std::string &reason = "Недостаточно данных: преждевременно достигнут конец строки.") {
        if (stream.eof()) {
            std::cout << '\n';
            print_err(line_num, reason);
            return true;
        }
        return false;
    }

    void read_from_file(database *db, const std::filesystem::path &input_path) {
        std::ifstream in_file(input_path);
        int total_lines{}, parsed_lines{};
        std::string line;
        while (std::getline(in_file, line, '\n')) {
            total_lines++;
            std::cout << "\n──────────" << '\n';
            // print the line without any changes
            std::cout << "Строка" << std::setw(4) << total_lines << ": [" << line << "]\n";

            car_row new_car;
            std::istringstream line_stream(line);

            std::getline(line_stream, new_car.car_type, ';');
            if (check_fail(line_stream, total_lines,
                           "Недостаточно данных: пустая строка.")) // no data, extracted nothing
                continue;
            std::cout << "Тип машины: [" << new_car.car_type << "] ";
            if (check_eof(line_stream, total_lines)) // no more data, extracted something
                continue;

            std::getline(line_stream, new_car.car_model, ';');
            if (check_fail(line_stream, total_lines)) // no more data, extracted nothing
                continue;
            std::cout << "Модель машины: [" << new_car.car_model << "] ";
            if (check_eof(line_stream, total_lines)) // no more data, extracted something
                continue;

            std::getline(line_stream, new_car.car_plate, ';');
            if (check_fail(line_stream, total_lines)) // no more data, extracted nothing
                continue;
            std::cout << "Номер машины: [" << new_car.car_plate << "] ";
            if (check_eof(line_stream, total_lines)) // no more data, extracted something
                continue;

            std::getline(line_stream, new_car.car_capacity, ';');
            if (check_fail(line_stream, total_lines)) // no more data, extracted nothing
                continue;
            std::cout << "Вместимость машины: [" << new_car.car_capacity << "] ";
            if (check_eof(line_stream, total_lines)) // no more data, extracted something
                continue;

            line_stream >> new_car.next_inspection_date >> std::ws;
            line_stream.ignore(1, ';');
            if (check_fail(line_stream, total_lines)) // no more data, extracted nothing
                continue;
            std::cout << "Дата следующей инспекции: ["
                      << std::put_time(std::localtime(&new_car.next_inspection_date), "%m/%d/%Y") << "] ";
            if (check_eof(line_stream, total_lines)) // no more data, extracted something
                continue;

            int car_status;
            line_stream >> car_status >> std::ws;
            line_stream.ignore(1, ';');
            new_car.car_status = static_cast<db::car_status>(car_status);
            if (check_fail(line_stream, total_lines)) // no more data, extracted nothing
                continue;
            std::cout << "Состояние машины: [" << format_status(new_car.car_status) << "] ";
            if (check_eof(line_stream, total_lines)) // no more data, extracted something
                continue;

            line_stream >> new_car.order_date;
            if (check_fail(line_stream, total_lines)) // no more data, extracted nothing
                continue;
            std::cout << "Дата заказа: [" << std::put_time(std::localtime(&new_car.order_date), "%m/%d/%Y")
                      << "] ";
            // ignoring trailing whitespace, try to get one more character to check for eof
            (line_stream >> std::ws).get();


            bool any_error = false;
            if (!line_stream.eof()) { // non-empty input, BUT still more data
                print_err(total_lines, "Избыток данных: не достигнут конец строки.");
                any_error = true;
            }
            // next: validate actual data
            if (car_status < 1 || car_status >= db::car_status::MAX) {
                print_err(total_lines, "Некорректные данные: неверное состояние машины");
                any_error = true;
            }
            if (any_error)
                continue;

            parsed_lines++;
            add_row(db, new_car);
        }
        std::cout << "\nВсего строк в файле: " << total_lines << ". Успешно считано: " << parsed_lines << '\n';
        if (parsed_lines < total_lines) {
            std::cout << "Внимание! Некоторые строки были считаны неверно. "
                         "Проверьте ошибки в выводе выше и исправьте данные\n";
        }
    }

#pragma endregion // parsing

    void print(database *db) {
        auto current = db->_list.begin();
        int i = 1;
        while (current != nullptr) {
            std::cout << " - " << i++ << " - " << format_row(current->data) << '\n';
            current = current->next;
        }
    }

    void save_to_file(database *db, const std::filesystem::path &output_path) {
        std::ofstream out_file(output_path);
        auto current = db->_list.begin();
        while (current != nullptr) {
            out_file
                    << current->data.car_type << ';'
                    << current->data.car_model << ';'
                    << current->data.car_plate << ';'
                    << current->data.car_capacity << ';'
                    << current->data.next_inspection_date << ';'
                    << current->data.car_status << ';'
                    << current->data.order_date << '\n';
            current = current->next;
        }
    }

    void erase(database *db, int index) {
        db->_list.erase(index);
    }

    void clear(database *db) {
        db->_list.clear();
    }

} // db