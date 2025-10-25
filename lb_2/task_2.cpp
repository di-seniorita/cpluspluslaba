// task_2_autodetect.cpp
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

// ------------ UTF-8 <-> UTF-16 helpers ------------
wstring utf8_to_wstring(const string& s) {
    if (s.empty()) return L"";
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0);
    wstring ws(len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &ws[0], len);
    return ws;
}
string wstring_to_utf8(const wstring& ws) {
    if (ws.empty()) return "";
    int len = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), (int)ws.size(), nullptr, 0, nullptr, nullptr);
    string s(len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), (int)ws.size(), &s[0], len, nullptr, nullptr);
    return s;
}

// ------------ Строковые утилиты на wchar_t* ------------
int wlen(const wchar_t* p) { int n = 0; while (p[n] != L'\0') ++n; return n; }

void wreverse(wchar_t* p) {
    int n = wlen(p);
    for (int i = 0; i < n / 2; ++i) {
        wchar_t t = p[i];
        p[i] = p[n - 1 - i];
        p[n - 1 - i] = t;
    }
}

int wcount(const wchar_t* p, wchar_t ch) {
    int c = 0; for (int i = 0; p[i] != L'\0'; ++i) if (p[i] == ch) ++c; return c;
}

// ------------ Авто-настройка консоли ------------
struct ConsoleMode {
    bool wide = false;  // true -> используем wcin/wcout (UTF-16)
};

ConsoleMode init_console_auto() {
    ConsoleMode m;

    // Если stdout действительно консоль (а не редирект в файл)
    DWORD type = GetFileType(GetStdHandle(STD_OUTPUT_HANDLE));
    bool isConsole = (type == FILE_TYPE_CHAR);

    UINT cpOut = GetConsoleOutputCP(); // текущая кодовая страница
    // Heuristics:
    // - если консоль есть и НЕ UTF-8 -> включаем wide-режим (надёжно для cmd)
    // - иначе оставляем UTF-8 (для VS Code / PowerShell / Windows Terminal)
    if (isConsole && cpOut != 65001) {
        _setmode(_fileno(stdout), _O_U16TEXT);
        _setmode(_fileno(stdin),  _O_U16TEXT);
        _setmode(_fileno(stderr), _O_U16TEXT);
        m.wide = true;
    } else {
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
        // можно ещё: std::ios_base::sync_with_stdio(false);
    }
    return m;
}

int main() {
    ConsoleMode mode = init_console_auto();   // авто-определение

    const int SIZE = 256;

    wstring ws;

    if (mode.wide) {
        // -------- РЕЖИМ UTF-16: wcin/wcout --------
        wcout << L"Введите строку: ";
        getline(wcin, ws);
    } else {
        // -------- РЕЖИМ UTF-8: cin/cout + конвертация --------
        cout << "Введите строку: ";
        string s_utf8;
        getline(cin, s_utf8);
        ws = utf8_to_wstring(s_utf8);
    }

    if ((int)ws.size() >= SIZE) ws.resize(SIZE - 1);

    // Работаем в wchar_t
    vector<wchar_t> buf(ws.begin(), ws.end());
    buf.push_back(L'\0');

    int length = wlen(buf.data());

    if (mode.wide) {
        wcout << L"Длина строки: " << length << L"\n";
    } else {
        cout << "Длина строки: " << length << "\n";
    }

    wreverse(buf.data());

    if (mode.wide) {
        wcout << L"Перевернутая строка: " << buf.data() << L"\n";
        wcout << L"Введите символ для подсчёта: ";
        wstring ch_w;
        if (!getline(wcin, ch_w) || ch_w.empty()) {
            wcout << L"Некорректный ввод символа.\n"; return 0;
        }
        wchar_t target = ch_w[0];
        int cnt = wcount(buf.data(), target);
        wcout << L"Символ '" << ch_w << L"' встречается " << cnt << L" раз(а).\n";
    } else {
        string reversed_utf8 = wstring_to_utf8(wstring(buf.data()));
        cout << "Перевернутая строка: " << reversed_utf8 << "\n";

        cout << "Введите символ для подсчёта: ";
        string ch_utf8;
        if (!getline(cin, ch_utf8) || ch_utf8.empty()) {
            cout << "Некорректный ввод символа.\n"; return 0;
        }
        wstring ch_w = utf8_to_wstring(ch_utf8);
        wchar_t target = ch_w[0];
        int cnt = wcount(buf.data(), target);
        cout << "Символ '" << ch_utf8 << "' встречается " << cnt << " раз(а).\n";
    }

    return 0;
}
