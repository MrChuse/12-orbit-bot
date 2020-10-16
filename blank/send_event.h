#ifndef SEND_EVENT_H
#define SEND_EVENT_H

#include <windows.h>

void lmb_down()
{
    INPUT i;
    i.type = INPUT_MOUSE;
    i.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &i, sizeof(i));
}

void lmb_up()
{
    INPUT i;
    i.type = INPUT_MOUSE;
    i.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &i, sizeof(i));
}

void lmb_click()
{
    lmb_down();
    lmb_up();
}

void move_mouse(long x, long y)
{
    INPUT i;
    i.type = INPUT_MOUSE;
    i.mi.dx = x * 65535 / 1920; // winapi is stupid
    i.mi.dy = y * 65535 / 1080;
    i.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &i, sizeof(i));
}

void lmb_click_xy(long x, long y)
{
    move_mouse(x, y);
    lmb_down();
    lmb_up();
}

void lmb_drag(long x1, long y1, long x2, long y2)
{
    move_mouse(x1, y1);
    Sleep(200);
    lmb_down();

    INPUT i;
    i.type = INPUT_MOUSE;
    i.mi.dx = x2 * 65535 / 1920; // winapi is stupid
    i.mi.dy = y2 * 65535 / 1080;
    i.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &i, sizeof(i));

    lmb_up();
}

void key_down(char c)
{
    INPUT i;
    ZeroMemory(&i, sizeof(i));
    i.type = INPUT_KEYBOARD;
    i.ki.wVk = 0;
    i.ki.wScan = c;
    i.ki.dwFlags = KEYEVENTF_SCANCODE;
    SendInput(1, &i, sizeof(i));
}

void key_up(char c) {
    INPUT i;
    ZeroMemory(&i, sizeof(i));
    i.type = INPUT_KEYBOARD;
    i.ki.wVk = 0;
    i.ki.wScan = c;
    i.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &i, sizeof(i));
}

void key_press(char c) {
    key_down(c);
    Sleep(5);
    key_up(c);
    Sleep(5);
}

#endif // SEND_EVENT_H