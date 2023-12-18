#include <iostream>
#include <random>

using namespace std;

// ��������� ��������� �����
random_device rd;
mt19937 gen(rd());

// ������� ��� ��������� ���������� ������� ����� ���������
int generateTime(double mean) {
    exponential_distribution<> dist(1.0 / mean);
    return dist(gen);
}

// ������� ��� ��������� ���������� ����� ��������� ���� � ���������
int generateFreeSeats() {
    uniform_int_distribution<> dist(0, 10);
    return dist(gen);
}

// ������� ��� ������������� ��������� ���������� �����
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
                cout << "����������� ��������: " << currentTime << endl;
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

    cout << "������� ����� ����������: " << avgStayTimeOnStop << endl;
}

int main() 
{
    setlocale(LC_ALL, "");
    double passengerArrivalTime, taxiArrivalTime, avgStayTime;
    bool isEndpoint;
    int maxPeople;

    // ���� ���������� ������
    cout << "������� ����� ����� ���������� ���������� �� ���������: ";
    cin >> passengerArrivalTime;
    cout << "������� ����� ����� ������������� ��������� �� ���������: ";
    cin >> taxiArrivalTime;
    cout << "���������� ��������� (0 - �� ��������, 1 - ��������): ";
    cin >> isEndpoint;
    cout << "������� ����� ���������� �������� �� ���������: ";
    cin >> avgStayTime;
    cout << "����������� ���������� ����� �� ���������: ";
    cin >> maxPeople;

    // ������ �������������
    simulateStop(passengerArrivalTime, taxiArrivalTime, isEndpoint, avgStayTime, maxPeople);

    return 0;
}