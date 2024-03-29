﻿#include <iostream>
#include <clocale>
using namespace std;
const int n = 8;
int board[n][n];

void Board() // Создание массива "доски" и заполнение её нулями
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 0;
        }
    }
}

void Display() // Отображение доски с учётом изменений
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == -1)
            {
                cout << " Q "; // Ферзь
            }
            else if (board[i][j] > 0) {
                cout << " X ";
            }
            else {

                cout << " _ "; // Клетка
            }

        }
        cout << endl;
    }
}

void Substitution(int i, int j) // Постановка ферзя
{
    for (int x = 0; x < n; ++x)
    {
        board[x][j] += 1;
        board[i][x] += 1;

        int d;
        d = j - i + x;
        if (d >= 0 && d < n)
        {
            board[x][d] += 1;
        }

        d = j + i - x;
        if (d >= 0 && d < n) {
            board[x][d] += 1;
        }
    }
    board[i][j] = -1;
    cout << endl;
    Display();
}

void Delete(int i, int j) // Удаление ферзя
{
    for (int x = 0; x < n; ++x) {
        board[x][j] -= 1;
        board[i][x] -= 1;

        int d;
        d = j - i + x;
        if (d >= 0 && d < n) {
            board[x][d] -= 1;
        }

        d = j + i - x;
        if (d >= 0 && d < n) {
            board[x][d] -= 1;
        }
    }
    cout << endl << " Возврат на шаг назад:" << endl;
    Display();
    board[i][j] = 0;
}

bool Solution(int i) // Запуск выполнения алгоритма
{
    bool result = false; // "флаг" - для завершения работы функции

    for (int j = 0; j < n; ++j) // Перебор строк
    {
        if (board[i][j] == 0) // Условие для поиска свободной клетки
        {
            Substitution(i, j); // Фызов функции для постановки в найденую клетку ферзя

            if (i == 7) // Условие для проверки окончания работы функции
            {
                result = true; // смена "флага"
            }
            else if (!(result = Solution(i + 1)))
            {
                Delete(i, j); // Вызов функции для удаления ферзя
            }
        }
        if (result) break;
    }
    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Board();
    cout << endl << " Постановка Первого ферзя";
    Solution(0);
    cout << endl << " Итоговый вариант:" << endl;
    Display();
    return 0;
}