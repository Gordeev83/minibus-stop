#include <iostream>
#include <random>

using namespace std;

// Генератор случайных чисел
random_device rd;
mt19937 gen(rd());

// Функция для генерации случайного времени между событиями
int generateTime(double mean) {
    exponential_distribution<> dist(1.0 / mean);
    return dist(gen);
}

// Функция для генерации случайного числа свободных мест в маршрутке
int generateFreeSeats() {
    uniform_int_distribution<> dist(0, 10);
    return dist(gen);
}

// Функция для моделирования остановки маршрутных такси
void simulateStop(double passengerArrivalTime, double taxiArrivalTime, bool isEndpoint, double avgStayTime, int maxPeople) {
    int currentTime = 0;
    int peopleOnStop = 0;
    int totalStayTime = 0;

    while (true) {
        int nextPassengerTime = generateTime(passengerArrivalTime);
        int nextTaxiTime = generateTime(taxiArrivalTime);

        currentTime += min(nextPassengerTime, nextTaxiTime);

        if (nextPassengerTime <= nextTaxiTime) {
            peopleOnStop++;
            totalStayTime += generateTime(avgStayTime);
            if (peopleOnStop > maxPeople) {
                cout << "Достаточный интервал: " << currentTime << endl;
                break;
            }
        }

        if (isEndpoint && nextTaxiTime <= nextPassengerTime) {
            peopleOnStop--;
            if (peopleOnStop < 0) {
                peopleOnStop = 0;
            }
        }
    }

    double avgStayTimeOnStop = static_cast<double>(totalStayTime) / peopleOnStop;

    cout << "Среднее время пребывания: " << avgStayTimeOnStop << endl;
}

int main() 
{
    setlocale(LC_ALL, "");
    double passengerArrivalTime, taxiArrivalTime, avgStayTime;
    bool isEndpoint;
    int maxPeople;

    // Ввод параметров модели
    cout << "Среднее время между прибытиями пассажиров на остановке: ";
    cin >> passengerArrivalTime;
    cout << "Среднее время между отправлениями маршруток на остановке: ";
    cin >> taxiArrivalTime;
    cout << "Назначения остановки (0 - не конечная, 1 - конечная): ";
    cin >> isEndpoint;
    cout << "Среднее время пребывания человека на остановке: ";
    cin >> avgStayTime;
    cout << "Достаточное количество людей на остановке: ";
    cin >> maxPeople;

    // Запуск моделирования
    simulateStop(passengerArrivalTime, taxiArrivalTime, isEndpoint, avgStayTime, maxPeople);

    return 0;
}