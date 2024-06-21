#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Flight {
    char model[20];
    char boardNumber[10];
    char landingTime[6];
    char airport[4];
};

struct IndFlight {
    int id;
    char landingTime[6];
};

// Функция для проверки корректности бортового номера, времени посадки и номера аэродрома
bool isValidFlight(const Flight& flight) {
    // Проверка бортового номера 
    int length = 0;
    while (flight.boardNumber[length] != '\0') {
        if (!((flight.boardNumber[length] >= '0' && flight.boardNumber[length] <= '9') ||
            (flight.boardNumber[length] >= 'A' && flight.boardNumber[length] <= 'Z') ||
            (flight.boardNumber[length] >= 'a' && flight.boardNumber[length] <= 'z'))) {
            return false;
        }
        length++;
    }
    if (length < 6) return false;

    // Проверка времени посадки (формат HH:MM)
    if (flight.landingTime[2] != ':' ||
        !(flight.landingTime[0] >= '0' && flight.landingTime[0] <= '9') ||
        !(flight.landingTime[1] >= '0' && flight.landingTime[1] <= '9') ||
        !(flight.landingTime[3] >= '0' && flight.landingTime[3] <= '9') ||
        !(flight.landingTime[4] >= '0' && flight.landingTime[4] <= '9')) {
        return false;
    }
    int hour = (flight.landingTime[0] - '0') * 10 + (flight.landingTime[1] - '0');
    int minute = (flight.landingTime[3] - '0') * 10 + (flight.landingTime[4] - '0');
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) return false;

    // Проверка номера аэродрома (АП1, АП2, АП3)
    if (strcmp(flight.airport, "АП1") != 0 && strcmp(flight.airport, "АП2") != 0 && strcmp(flight.airport, "АП3") != 0) return false;

    return true;
}

// Функция для сортировки методом пузырька
void bubbleSort2(IndFlight indFlights[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (strcmp(indFlights[j].landingTime, indFlights[j + 1].landingTime) > 0) {
                IndFlight temp = indFlights[j];
                indFlights[j] = indFlights[j + 1];
                indFlights[j + 1] = temp;
            }
        }
    }
}

// Функция для печати строки с нужным количеством пробелов
void printPaddedString(const char* str, int width) {
    cout << left << setw(width) << str;
}

// Функция для печати таблицы посадок
void printFlights(const Flight flights[], const IndFlight indFlights[], int n) {
    const int modelWidth = 20;
    const int boardNumberWidth = 15;
    const int landingTimeWidth = 12;
    const int airportWidth = 5;

    // Печать заголовка таблицы
    cout << "+" << string(modelWidth + 1, '-') << "+"
        << string(boardNumberWidth + 1, '-') << "+"
        << string(landingTimeWidth + 1, '-') << "+"
        << string(airportWidth + 1, '-') << "+" << endl;

    cout << "| ";
    printPaddedString("Марка ЛА", modelWidth);
    cout << "| ";
    printPaddedString("Бортовой номер", boardNumberWidth);
    cout << "| ";
    printPaddedString("Время посадки", landingTimeWidth);
    cout << "| ";
    printPaddedString("АП", airportWidth);
    cout << "|" << endl;

    cout << "+" << string(modelWidth + 1, '-') << "+"
        << string(boardNumberWidth + 1, '-') << "+"
        << string(landingTimeWidth + 1, '-') << "+"
        << string(airportWidth + 1, '-') << "+" << endl;

    // Печать данных
    for (int i = 0; i < n; ++i) {
        int idx = indFlights[i].id;
        cout << "| ";
        printPaddedString(flights[idx].model, modelWidth);
        cout << "| ";
        printPaddedString(flights[idx].boardNumber, boardNumberWidth);
        cout << "| ";
        printPaddedString(flights[idx].landingTime, landingTimeWidth);
        cout << "| ";
        printPaddedString(flights[idx].airport, airportWidth);
        cout << "|" << endl;
    }

    cout << "+" << string(modelWidth + 1, '-') << "+"
        << string(boardNumberWidth + 1, '-') << "+"
        << string(landingTimeWidth + 1, '-') << "+"
        << string(airportWidth + 1, '-') << "+" << endl;
}


void InpData(const char* FNAME, Flight* flights, int& flightCount, int& ErrCode) {
    // Чтение данных из файла
    ifstream inputFile(FNAME);
    if (!inputFile) {
        cerr << "Ошибка открытия файла." << endl;
        ErrCode = 1;
        return;
    }
    while (!inputFile.eof()) {
        inputFile >> flights[flightCount].model;
        inputFile >> flights[flightCount].boardNumber;
        inputFile >> flights[flightCount].landingTime;
        inputFile >> flights[flightCount].airport;
        if (isValidFlight(flights[flightCount])) {
            ++flightCount;
        }
        else {
            cerr << "Ошибка в данных: " << flights[flightCount].model << " " << flights[flightCount].boardNumber << " " << flights[flightCount].landingTime << " " << flights[flightCount].airport << endl;
        }
    }
    inputFile.close();
}

int main() {
    const int MAX_FLIGHTS = 20;
    Flight flights[MAX_FLIGHTS];
    IndFlight indFlights[MAX_FLIGHTS];

    int flightCount = 0;
    int ErrCode = 0;
    // поддержка кириллицы
    setlocale(0, ".1251");

    InpData("flights.txt", flights, flightCount, ErrCode);

    // Заполнение массива indFlights
    for (int i = 0; i < flightCount; ++i) {
        indFlights[i].id = i;
        strcpy_s(indFlights[i].landingTime, flights[i].landingTime);
    }

    // Сортировка данных
    bubbleSort2(indFlights, flightCount);

    // Печать отсортированных данных
    printFlights(flights, indFlights, flightCount);

    return 0;
}