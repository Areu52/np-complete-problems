#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


#include <windows.h>
void f()
{
    SetConsoleOutputCP(65001);
}

struct Answer
{
    int Total_weight, Total_value;

    Answer(int a, int b) : Total_weight(a), Total_value(b) {}
};

struct knapsack_element
{
    int id, value, weight;
    double ratio;
};

bool sortik(const knapsack_element& a, const knapsack_element& b)
{
    return a.ratio > b.ratio;
}


Answer Knapsack(int W, vector<knapsack_element>& items)
{
    int total_weight = 0, total_value = 0, i;

    sort(items.begin(), items.end(), sortik); // Сортируем массив по эвриситике ratio

    for (i = 0; i < items.size(); i++)
    {
        knapsack_element elem = items[i];
        if (total_weight + elem.weight <= W)
        {
            total_value  += elem.value;
            total_weight += elem.weight;
        }
    }

    Answer answer(total_weight, total_value);

    return answer;
}

int main()
{
    f();

    // Открываем файл
    ifstream File("ks_50_0");

    int N, W, i;
    File >> N >> W; // Считываем данные с первой строчки N - число следующих строчек, W - максимальный вес рюкзака

    vector<knapsack_element> items(N);

    // Заполняем данные об каждом элементе
    for (i = 0; i < N; i++)
    {
        File >> items[i].value >> items[i].weight;
        items[i].id = i + 1;
        items[i].ratio = static_cast<double>(items[i].value) / W;
    }

    // Закрываем файл
    File.close();

    // Запускаем алгоритм, который сортирует по убыванию эвристики value/weight и отбирает пока элементы, пока их можно засунуть в рюкзак
    Answer answer = Knapsack(W, items);

    cout << "Максимальная стоимость: " << answer.Total_value << endl;
    cout << "Общий вес: " << answer.Total_weight << "/" << W << endl;
    cout << endl;

    return 0;
}


