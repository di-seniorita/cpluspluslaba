#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int N;
    cout << "Введите количество дней для анализа: ";
    cin >> N;

    if (N <=0) {
        cout << "Не правильное количество дней, (должно быть больше 0) начните сначала." << endl;
        return 1;
    }

    double temp[10000];

    cout << "Введите " << N << " значений температур:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "День " << i + 1 << ": ";
        cin >> temp[i];

        if (cin.fail()) {
            cout << "Ошибка: введено некорректное значение температуры." << endl;
            return 1;
        }
    }

    double sum = 0;
    for (int i = 0; i < N; i++) {
        sum += temp[i];
    }
    double average = sum / N;

    double mintemp = temp[0];
    double maxtemp = temp[0];
    for (int i = 1; i < N; i++) {
        if (temp[i] < mintemp)
            mintemp = temp[i];
        if (temp[i] > maxtemp)
            maxtemp = temp[i];
    }

    int belowaverage = 0;
    for (int i = 0; i < N; i++) {
        if (temp[i] < average)
            belowaverage++;
    }

    cout << "=== Результаты анализа ===\n" << endl;
    cout << "Средняя температура: " << average << endl;
    cout << "Минимальная температура: " << mintemp << endl;
    cout << "Максимальная температура: " << maxtemp << endl;
    cout << "Дней ниже средней: " << belowaverage << endl;

    return 0;
}