//by raduminecraft

#include <windows.h>
#include <math.h>

COLORREF COLORHSL(int length) {
    double h = fmod(length, 360.0);
    double s = 1.0;
    double l = 0.5;

    double c = (1.0 - fabs(2.0 * l - 1.0)) * s;
    double x = c * (1.0 - fabs(fmod(h / 60.0, 2.0) - 1.0));
    double m = l - c / 2.0;

    double r1, g1, b1;
    if (h < 60) {
        r1 = c;
        g1 = x;
        b1 = 0;
    }
    else if (h < 120) {
        r1 = x;
        g1 = c;
        b1 = 0;
    }
    else if (h < 180) {
        r1 = 0;
        g1 = c;
        b1 = x;
    }
    else if (h < 240) {
        r1 = 0;
        g1 = x;
        b1 = c;
    }
    else if (h < 300) {
        r1 = x;
        g1 = 0;
        b1 = c;
    }
    else {
        r1 = c;
        g1 = 0;
        b1 = x;
    }

    int red = static_cast<int>((r1 + m) * 255);
    int green = static_cast<int>((g1 + m) * 255);
    int blue = static_cast<int>((b1 + m) * 255);

    return RGB(red, green, blue);
}

int mandelbrot(float real, float imag, float maxiter, float shape) {
    int n = 0;

    float zr = 0.0;
    float zi = 0.0;

    while (n < maxiter && zr * zr + zi * zi <= 4.0) {
        float temp = zr * zr - zi * zi + real;

        zi = shape * zr * zi + imag;
        zr = temp;
        n++;
    }

    return n;
}

//i commented sections of code to show where customizations can be made.

int main() {
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    int c = 0;
    int p = 3; //set pixelation (best from 1 to 5)
    float shape = 2.0;
    //shape = 1.0 - depends of what you see
    //shape = 2.0 - perfectly normal mandelbrot
    //shape = 3.0 - strinked mandelbrot
    //shape = 4.0 - more strinked mandelbrot
    //shape = ... - keeps strinking
    int maxiter = 50; //50 is right
    float angle = 0.0;

    DWORD* data = new DWORD[4 * x * y];
    HDC hdc = GetDC(0);
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateBitmap(x, y, 1, 32, data);
    SelectObject(mdc, bmp);

    while (true) {
        StretchBlt(mdc, 0, 0, x / p, y / p, hdc, 0, 0, x, y, SRCCOPY);
        GetBitmapBits(bmp, 4 * x * y, data);

        for (int x2 = 0; x2 < x / p; x2++) {
            for (int y2 = 0; y2 < y / p; y2++) {
                int cx = x2 - (x / (2 * p));
                int cy = y2 - (y / (2 * p));

                int zx = (int)((cx * cos(angle) - cy * sin(angle)));
                int zy = (int)((cx * sin(angle) + cy * cos(angle)));

                int x3 = cx + (sin(angle * 100) * 10);
                int y3 = cy + (cos(angle * 100) * 10);

                //0.002 is the size so you can change it
                int n = mandelbrot(zx * (0.002 * p), zy * (0.002 * p), maxiter, shape);

                //here is the main part
                int wave = (c + (c * sin(sqrt((x2 * x2) + (y2 * y2)) / 64))) + (c + (c * (sqrt((x2 * x2) + (cy * cy)) / 64))) + (c + (c * (sqrt((zx * zx) ^ (zy * zy)) / 64))) + ((n == maxiter) ? 0 : n * 255 / maxiter);// +sqrt(x2 * y2);

                data[y2 * x + x2] = COLORHSL((x * y) + wave);
            }
        }

        SetBitmapBits(bmp, 4 * x * y, data);
        StretchBlt(hdc, 0, 0, x, y, mdc, 0, 0, x / p, y / p, SRCCOPY);

        Sleep(10);

        angle += 0.01;
        c++;
    }

    return 0;
}