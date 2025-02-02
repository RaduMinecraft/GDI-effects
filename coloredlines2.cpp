//by raduminecraft

#include <windows.h>

int main() {
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    int r = 0;
    int time = 0;
    int delay = 0;
    int c = 1;

    //use BYTE 
    BYTE* pixels = new BYTE[4 * x * y]; //lazy method but works
    HDC hdc = GetDC(0);
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateBitmap(x, y, 1, 32, pixels);
    SelectObject(mdc, bmp);

    while (true) {
        BitBlt(mdc, 0, 0, x, y, hdc, 0, 0, SRCCOPY);
        GetBitmapBits(bmp, 4 * x * y, pixels);

        for (int i = 0; i < 4 * x * y; i++) {
            if (!(i % y) && !(rand() % y)) r = rand() % c; //ik is from nikitpad

            pixels[i] = pixels[i + r];
        }

        SetBitmapBits(bmp, 4 * x * y, pixels);
        BitBlt(hdc, 0, 0, x, y, mdc, 0, 0, SRCCOPY);

        delay = 2000 / (time / 10 + 1) + 9;

        Sleep(delay);

        if (delay != 10) {
            time += 5;
        }

        if (c != (x / 4)) {
            c++;
        }
    }

    return 0;
}
