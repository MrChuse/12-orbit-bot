#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <vector>
using std::vector;
#include <windows.h>

#include <iostream>
using std::cout;
using std::endl;

struct color
{
    int r;
    int g;
    int b;
};

inline int PosB(BYTE* ScreenData, int ScreenX, int x, int y)
{
    return ScreenData[4 * ((y * ScreenX) + x)];
}

inline int PosG(BYTE* ScreenData, int ScreenX, int x, int y)
{
    return ScreenData[4 * ((y * ScreenX) + x) + 1];
}

inline int PosR(BYTE* ScreenData, int ScreenX, int x, int y)
{
    return ScreenData[4 * ((y * ScreenX) + x) + 2];
}

Tensor<Index, 3> ScreenCap(int x1, int y1, int x2, int y2)
{
    
    int ScreenX = 0;
    int ScreenY = 0;
    BYTE* ScreenData = 0;
    
    HDC hScreen = GetDC(NULL);
    ScreenX = GetDeviceCaps(hScreen, HORZRES);
    ScreenY = GetDeviceCaps(hScreen, VERTRES);

    HDC hdcMem = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, ScreenX, ScreenY);
    HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, ScreenX, ScreenY, hScreen, 0, 0, SRCCOPY);
    SelectObject(hdcMem, hOld);
    
    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = ScreenX;
    bmi.biHeight = -ScreenY;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;// 3 * ScreenX * ScreenY;
    
    if (ScreenData)
        free(ScreenData);
    ScreenData = (BYTE*)malloc(4 * ScreenX * ScreenY);

    GetDIBits(hdcMem, hBitmap, 0, ScreenY, ScreenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
    
    ReleaseDC(GetDesktopWindow(), hScreen);
    DeleteDC(hdcMem);
    DeleteObject(hBitmap);
    

    Tensor<Index, 3> matrix(x2 - x1, y2 - y1, 3);
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            matrix(i, j, 0) = PosR(ScreenData, ScreenX, i, j);
            matrix(i, j, 1) = PosG(ScreenData, ScreenX, i, j);
            matrix(i, j, 2) = PosB(ScreenData, ScreenX, i, j);
        }
    }
    free(ScreenData);
    return matrix;
}

#endif //SCREENSHOT_H