// -*- coding: cp866 -*-
/****************************************************************
 *                     ������� ? 304 1 ����                      *
 *---------------------------------------------------------------*
 * Project Type  : Win32 Console Application                     *
 * Project Name  : LW1                                           *
 * File Name     : LW1.cpp                                       *
 * Language      : C/C++                                         *
 * Programmer(s) : ������� �.�., ��쨭 �.�                       *
 * Created at    : 01/06/24                                      *
 * Last Revision : 05/06/24                                      *
 * Comment(s)    : ��ப��� �����                              *
 ****************************************************************/

#define _USE_MATH_DEFINES

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

const size_t MAX_FLIGHTS_LEN = 50;
const size_t CELL_WIDTH = 10;

struct Flight {
    std::string model;
    std::string board_number;
    std::string landing_time;
    std::string airport;
};

size_t parse_input_destructive(std::ifstream &stream, Flight *flights, size_t max_flights);
void print_flights(Flight *flights, int n, int *ix);
void reset_stream(std::ifstream &stream, const std::streampos start_pos);

void bubble_sort_i(Flight *flights, int n, int *ix) {
    bool is_unsorted;
    do { // if we can't find any unsorted elements, the array is sorted
        is_unsorted = false;
        for (int i = 0; i < (n - 1); i++) { // iterate until we find the first unsorted element
            if (flights[ix[i]].landing_time > flights[ix[i + 1]].landing_time) {
                is_unsorted = true;
                for (; i < (n - 1); i++) {
                    if (flights[ix[i]].landing_time > flights[ix[i + 1]].landing_time) {
                        std::swap(ix[i], ix[i + 1]);
                    }
                }
            }
        }
    } while (is_unsorted);
}

int main(int argc, char **argv) {
    // if(argc == 1) {
    //     std::cout << "�ᯮ�짮�����: " << argv[0] << " test_file" << '\n';
    //     return 0;
    // }

    std::ifstream input_file(argc == 1 ? "tests/test0.txt" : argv[1]); // ��⮪ �⥭�� �� 䠩��

    if (!input_file.is_open()) {
        std::cerr << "�訡�� ������ 䠩��. ��������, �� �� 㪠������� ��� ������� 䠩�: "
                  << argv[1] << '\n';
        return -1;
    }

    if (input_file.peek() == EOF) {
        std::cerr << "���� ����.\n";
        return -2;
    }

    std::cout << "��室�� 䠩�:\n\"\"\"\n";
    std::cout << input_file.rdbuf();
    std::cout << "\"\"\"\n";
    reset_stream(input_file, std::ios_base::beg);

    Flight *flights = new Flight[MAX_FLIGHTS_LEN];
    size_t parsed_flights_len = parse_input_destructive(input_file, flights, MAX_FLIGHTS_LEN);

    int *ix = new int[parsed_flights_len];
    for (size_t i = 0; i < parsed_flights_len; i++)
        ix[i] = i;

    std::cout << "\n����� �� ���஢��\n";
    print_flights(flights, parsed_flights_len, ix);

    bubble_sort_i(flights, parsed_flights_len, ix);

    std::cout << "\n����� ��᫥ ���஢��\n";
    print_flights(flights, parsed_flights_len, ix);
}

inline void print_err(size_t line_num, std::string reason) {
    std::cerr << "�訡��! ��ப�:" << std::setw(4) << line_num << ". " << reason << "\n";
}

inline bool check_fail(
    std::istream &stream, size_t line_num,
    const std::string &reason = "�������筮 ������: �०���६���� ���⨣��� ����� ��ப�.") {
    if (stream.fail()) {
        std::cerr << '\n';
        print_err(line_num, reason);
        return true;
    }
    return false;
}

inline bool check_eof(
    std::istream &stream, size_t line_num,
    const std::string &reason = "�������筮 ������: �०���६���� ���⨣��� ����� ��ப�.") {
    if (stream.eof()) {
        std::cerr << '\n';
        print_err(line_num, reason);
        return true;
    }
    return false;
}

inline bool check_bad_board_number(const std::string &board_number) {
    return board_number.length() != 6 ||
           board_number[0] < '�' || '�' < board_number[0] || // capital letter
           board_number[1] != '-' ||
           board_number[2] < '0' || '9' < board_number[2] || // digit
           board_number[3] < '0' || '9' < board_number[3] || // digit
           board_number[4] < '0' || '9' < board_number[4] || // digit
           board_number[5] < '0' || '9' < board_number[5]    // digit
        ;
}

inline bool check_bad_landing_time(const std::string &landing_time) {
    return landing_time.length() != 5 ||
           landing_time[0] < '0' || '2' < landing_time[0] ||    // first digit 0-2
           landing_time[1] < '0' || '9' < landing_time[1] ||    // second digit 0-9
           (landing_time[0] == '2' && '4' < landing_time[1]) || // special-case of second digit 0-4
           landing_time[2] != ':' ||
           landing_time[3] < '0' || '6' < landing_time[3] || // third digit 0-6
           landing_time[4] < '0' || '9' < landing_time[4] || // fourth digit 0-9
           (landing_time[3] == '6' && '0' < landing_time[4]) // special-case of fourth digit 0
        ;
}

inline bool check_bad_airport(const std::string &airport) {
    return airport.length() != 3 ||
           airport[0] != '�' ||
           airport[1] != '�' ||
           airport[2] < '1' || '3' < airport[2];
}

// returns number of elements
size_t parse_input_destructive(std::ifstream &stream, Flight *flights, size_t max_flights) {
    size_t i = 0, parsed = 0;
    std::string line;
    while (std::getline(stream, line)) {
        ++i;
        std::cout << "����������" << '\n';
        std::cout << "��ப�" << std::setw(4) << i << ": [" << line << "]\n";
        std::string model, board_number, landing_time, airport;

        std::istringstream iline(line);

        iline >> model;
        if (check_fail(iline, i, "�������筮 ������: ����� ��ப�.")) // empty input
            continue;
        std::cout << "������: [" << model << "] ";
        if (check_eof(iline, i)) // no more data
            continue;

        iline >> board_number;
        if (check_fail(iline, i)) // no more data
            continue;
        std::cout << "���⮢�� �����: [" << board_number << "] ";
        if (check_eof(iline, i)) // no more data
            continue;

        iline >> landing_time;
        if (check_fail(iline, i)) // no more data
            continue;
        std::cout << "�६� ��ᠤ��: [" << landing_time << "] ";
        if (check_eof(iline, i)) // no more data
            continue;

        iline >> airport;
        if (check_fail(iline, i)) // no more data
            continue;
        std::cout << "��ய���: [" << airport << "]\n";
        (iline >> std::ws).get(); // without trailing whitespace

        bool any_error = false;
        if (!iline.eof()) { // non-empty input, BUT still more data
            print_err(i, "����⮪ ������: �� ���⨣��� ����� ��ப�.");
            any_error = true;
        }
        // next: validate actual data
        if (check_bad_board_number(board_number)) {
            print_err(i, "�����४�� �����: �����४�� ���⮢�� �����.");
            any_error = true;
        }
        if (check_bad_landing_time(landing_time)) {
            print_err(i, "�����४�� �����: �����४⭮� �६� ��ᠤ��.");
            any_error = true;
        }
        if (check_bad_airport(airport)) {
            print_err(i, "�����४�� �����: �����४�� ��த஬.");
            any_error = true;
        }
        if (any_error)
            continue;

        flights[parsed++] = {model, board_number, landing_time, airport};
    }
    std::cout << "����������" << '\n';
    return parsed;
}

void print_table_line(std::ostream &output, const std::string &left_border, const std::string &line,
                      const std::string &divider, const std::string &right_border,
                      int cell_amount = 5, int cell_width = CELL_WIDTH) {
    output << left_border;
    for (size_t cell_i = 0; cell_i < cell_amount; ++cell_i) {
        for (size_t i = 0; i < cell_width; ++i)
            std::cout << line;
        if (cell_i < cell_amount - 1)
            output << divider;
    }

    output << right_border << '\n';
}

void print_flights(Flight *flights, int n, int *ix) {
    print_table_line(std::cout, "�", "�", "�", "�");
    std::cout << "�" << std::setw(CELL_WIDTH) << "i" << "�" << std::setw(CELL_WIDTH) << "��ઠ ��"
              << "�" << std::setw(CELL_WIDTH) << "����.�����" << "�" << std::setw(CELL_WIDTH)
              << "��.���." << "�" << std::setw(CELL_WIDTH) << "��த஬" << "�" << '\n';

    print_table_line(std::cout, "�", "�", "�", "�");

    for (size_t i = 0; i < n; ++i) {
        Flight flight = flights[ix[i]];

        if (i % 3 == 0 && i != 0) // ������ ����� ��ப� ⠡���� ����稢����� ������
            print_table_line(std::cout, "�", "�", "�", "�");

        std::cout << "�" << std::setw(CELL_WIDTH) << i << "�" << std::setw(CELL_WIDTH)
                  << flight.model << "�" << std::setw(CELL_WIDTH) << flight.board_number << "�"
                  << std::setw(CELL_WIDTH) << flight.landing_time << "�" << std::setw(CELL_WIDTH)
                  << flight.airport << "�" << '\n';
    }

    print_table_line(std::cout, "�", "�", "�", "�");
}

void reset_stream(std::ifstream &stream, const std::streampos start_pos) {
    stream.clear();
    stream.seekg(start_pos);
}
