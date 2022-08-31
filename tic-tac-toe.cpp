#include <iostream>

#include <windows.h>                                        

#include <conio.h>

#include <time.h>

using namespace std;

char* board;
int i, j, n;
string Name1, Name2;
bool name;

void new_board() {
    board = new char[n * n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[n * i + j] = '-';
        }
    }
}

void show_board() {
    
    cout << "   ";
    for (int j = 1; j <= n; j++) {
        cout << "| " << j << " ";
    }
    cout << "|" << endl;

    
    for (int j = 0; j <= n; j++) {
        cout << "----";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
       
        cout << " " << (i + 1) << " ";

        
        for (int j = 0; j < n; j++) {
            cout << "| " << board[n * i + j] << " ";
        }
        cout << '|' << endl;
    }
    cout << endl;
}

void help() {
    cout << "\t\t" << "Гра 'Хрестики-нулики " << n << "х" << n << "'" << endl << endl;
    cout << "Ігрове поле:" << endl << endl;

    show_board();

    cout << endl;
    cout << "Для початку гри натисніть будь-яку клавішу:" << endl;
    cout << endl;
    _getch();
}

bool step() {
    show_board();

    if (name) {
        cout << "Ходить " << Name1 << " : ";
    }
    else {
        cout << "Ходить " << Name2 << " : ";
    }

    int i, j;

    cin >> i >> j;
    i -= 1;
    j -= 1;

    if (i > n || j > n) {
        return false;
    }

    if (board[n * i + j] == '0' || board[n * i + j] == 'X') {
        return false;
    }

    if (name) {
        board[n * i + j] = 'X';
        name = false;
    }
    else {
        board[n * i + j] = '0';
        name = true;
    }

    return true;
}

bool game_end(char ch) {
    int row = 0;
    int col = 0;
    int d1 = 0;
    int d2 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[n * i + j] == ch)
                row++;

            if (board[n * j + i] == ch)
                col++;

            if (board[n * j + j] == ch)
                d1++;

            if (board[n * (n - 1 - j) + j] == ch)
                d2++;
        }
        if (row == n || col == n || d1 == n || d2 == n) {
            return true;
            break;
        }

        row = 0;
        col = 0;
        d1 = 0;
        d2 = 0;
    }

    return false;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введіть розмір поля: ";
    cin >> n;

    new_board();

    help();

    system("cls");

    cout << "Введіть ім'я першого гравця: ";
    cin >> Name1;
    cout << "Введіть ім'я другого гравця: ";
    cin >> Name2;

    srand(time(NULL));

    if (rand() % 2 == 0) {
        name = true;
    }
    else {
        name = false;
    }

    system("cls");

    while (!game_end('X') && !game_end('O')) {
        if (i == n * n) {
            system("cls");
            cout << "Нічия!";
            break;
        }
        system("cls");
        if (!step()) {
            cout << "Ви ввели неправильні дані!";
            _getch();
        }
        i++;

        if (game_end('X')) {
            system("cls");
            cout << "Виграв гравець: " << Name1 << endl;
            break;
        }

        if (game_end('0')) {
            system("cls");
            cout << "Виграв гравець: " << Name2 << endl;
            break;
        }
    }

    cout << endl << endl;

    system("pause");

    delete board;

    return 0;
}

