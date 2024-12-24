#include <windows.h>
#include <ctime>

int WINAPI Right() {
    HDC hdc = GetDC(nullptr);

    int var_a4 = 10;
    int var_98 = 5;
    int var_94 = 0;

    time_t start_time;
    time(&start_time);

    for (int i = 0; i < 15; i++) {
        time_t current_time;
        time(&current_time);

        HWND hWnd = GetDesktopWindow();
        RECT rect;
        GetWindowRect(hWnd, &rect);

        POINT points[3] = {
            { rect.left + var_a4, rect.top - var_a4 },
            { rect.right + var_a4, rect.top + var_a4 },
            { rect.left - var_a4, rect.bottom - var_a4 }
        };

        PlgBlt(hdc, points, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, 0, 0);
    }
    return 0;
}

int WINAPI Left() {
    HDC hdc = GetDC(nullptr);

    int var_a4 = 10;
    int var_98 = 5;
    int var_94 = 0;

    time_t start_time;
    time(&start_time);

    for (int i = 0; i < 15; i++) {
        time_t current_time;
        time(&current_time);

        HWND hWnd = GetDesktopWindow();
        RECT rect;
        GetWindowRect(hWnd, &rect);

        POINT points[3] = {
            { rect.left - var_a4, rect.top + var_a4 },
            { rect.right - var_a4, rect.top - var_a4 },
            { rect.left + var_a4, rect.bottom + var_a4 }
        };

        PlgBlt(hdc, points, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, 0, 0);
    }
    return 0;
}

int main() {
    while (true) {
        Right();
        Left();
    }
    return 0;
}
