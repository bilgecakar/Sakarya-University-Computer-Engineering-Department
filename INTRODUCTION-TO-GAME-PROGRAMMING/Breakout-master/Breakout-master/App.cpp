// Breakout.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Engine.h"
#include "App.h"

#pragma comment(lib, "d2d1")

// Forward declarations of functions included in this code module:

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        MainApp app;

        if (SUCCEEDED(app.Initialize()))
        {
            app.RunMessageLoop();
        }
        
        CoUninitialize();
    }

    return 0;
}


MainApp::MainApp() : m_hwnd(NULL)
{
    engine = new Engine();
}


MainApp::~MainApp()
{
}


void MainApp::RunMessageLoop()
{
    MSG msg;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    int frames = 0;
    double framesTime = 0;

    boolean running = true;
    while (running) 
    {

        end = std::chrono::steady_clock::now();
        double elapsed_secs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
        begin = end;

        // Display FPS
        framesTime += elapsed_secs;
        frames++;
        if (framesTime > 1) {
            WCHAR fpsText[32];
            swprintf(fpsText, 32, L"Game: %d FPS", frames);
            SetWindowText(m_hwnd, fpsText);
            frames = 0;
            framesTime = 0;
        }

        // Messages and user input
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                running = false;
        }

        // Game logic
        engine->Logic(elapsed_secs);

        // Drawing
        engine->Draw();
    }
}


HRESULT MainApp::Initialize()
{
    HRESULT hr = S_OK;

    // Register the window class.
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MainApp::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = HINST_THISCOMPONENT;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wcex.lpszClassName = L"D2DMainApp";

    ATOM x = RegisterClassEx(&wcex);

    // Create the window.
    m_hwnd = CreateWindowEx(
        NULL,
        L"D2DMainApp",
        L"Game",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        RESOLUTION_X,
        RESOLUTION_Y,
        NULL,
        NULL,
        HINST_THISCOMPONENT,
        this
    );
    hr = m_hwnd ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        engine->InitializeD2D(m_hwnd);

        ShowWindow(m_hwnd, SW_SHOWNORMAL);
        UpdateWindow(m_hwnd);
    }

    return hr;
}

LRESULT CALLBACK MainApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        MainApp* pMainApp = (MainApp*)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pMainApp)
        );

        result = 1;
    }
    else
    {
        MainApp* pMainApp = reinterpret_cast<MainApp*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )));

        bool wasHandled = false;

        if (pMainApp)
        {
            switch (message)
            {

            case WM_MOUSEMOVE:
            {
                pMainApp->engine->MousePos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_LBUTTONUP:
            {
                pMainApp->engine->Reset();
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DISPLAYCHANGE:
            {
                InvalidateRect(hwnd, NULL, FALSE);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            result = 1;
            wasHandled = true;
            break;
            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    return result;
}
