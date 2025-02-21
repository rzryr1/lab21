#include <windows.h>
#include <string>

HWND hwndEdit1, hwndEdit2;

void CalculateAndShowResult(char op) {
    char buffer1[256], buffer2[256];
    GetWindowText(hwndEdit1, buffer1, 256);
    GetWindowText(hwndEdit2, buffer2, 256);
    
    double num1 = atof(buffer1);
    double num2 = atof(buffer2);
    double result = 0;
    
    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
    }
    
    char resultStr[256];
    sprintf(resultStr, "%f", result);
    MessageBox(NULL, resultStr, "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD, 25, 20, 200, 20, hwnd, NULL, NULL, NULL);
            hwndEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 25, 50, 200, 20, hwnd, NULL, NULL, NULL);
            hwndEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 25, 80, 200, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 30, 120, 40, 30, hwnd, (HMENU) 1, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 80, 120, 40, 30, hwnd, (HMENU) 2, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 120, 40, 30, hwnd, (HMENU) 3, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 180, 120, 40, 30, hwnd, (HMENU) 4, NULL, NULL);
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case 1: CalculateAndShowResult('+'); break;
                case 2: CalculateAndShowResult('-'); break;
                case 3: CalculateAndShowResult('*'); break;
                case 4: CalculateAndShowResult('/'); break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CalculatorWindow";
    wc.hbrBackground = CreateSolidBrush(RGB(0, 200, 200));
    
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("CalculatorWindow", "My Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 100, 100, 250, 200, NULL, NULL, hInstance, NULL);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}