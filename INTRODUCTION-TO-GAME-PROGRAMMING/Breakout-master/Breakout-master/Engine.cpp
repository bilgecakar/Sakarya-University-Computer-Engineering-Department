#include "framework.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Engine.h"

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

Engine::Engine() : m_pDirect2dFactory(NULL), m_pRenderTarget(NULL)
{
    // Initializes everything in the game: ball, paddles, positions
    ball = new Ball();
    paddle = new Paddle(RESOLUTION_Y - 5);
    mouseXPos = RESOLUTION_X / 2;

    // Intitilize bricks
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            int posX = RESOLUTION_X / 2 + (j - 7) * BRICK_WIDTH;
            int posY = 100 + i * BRICK_HEIGHT;
            bricks[i * 15 + j] = new Brick(posX, posY);
        }
    }

    playing = true;
}

Engine::~Engine()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
}

HRESULT Engine::InitializeD2D(HWND m_hwnd)
{
    // Initializes Direct2D, to draw with
    D2D1_SIZE_U size = D2D1::SizeU(RESOLUTION_X, RESOLUTION_Y);
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
    m_pDirect2dFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(m_hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
        &m_pRenderTarget
    );

    ball->Initialize(m_pRenderTarget);

    paddle->Initialize(m_pRenderTarget);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            bricks[i * 15 + j]->Initialize(m_pRenderTarget);
        }
    }

    return S_OK;
}

void Engine::Reset()
{
    // This method reset the game, given that the game was won or lost
    if (!playing)
    {
        ball->Reset();
        playing = true;
    }
}

void Engine::MousePos(int x, int y)
{
    // receives the mouse position, to be used on the right paddle
    mouseXPos = x;
}

void Engine::Logic(double elapsedTime)
{
    // This is the logic part of the engine. It receives the elapsed time from the app class, in seconds.
    // It uses this value for a smooth and consistent movement, regardless of the CPU or graphics speed
    if (playing)
    {
        // Moves the ball forward
        ball->Advance(elapsedTime);

        // Moves the paddle based on the received mouse position
        paddle->MoveToPosition(mouseXPos);

        // Checks if the ball hits the left/right paddle and apply the bounce
        ball->CheckHitsPaddle(paddle->position.x);

        // Ball hits any of the bricks
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                bricks[i * 15 + j]->BallCollision(ball);
            }
        }

        // If it goes outisde of th eplaying area, the game stops
        if (ball->IsOutside())
        {
            playing = false;
        }
    }
}

HRESULT Engine::Draw()
{
    // This is the drawing method of the engine.
    // It simply draws all the elements in the game using Direct2D
    HRESULT hr;

    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());


    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    ball->Draw(m_pRenderTarget);

    paddle->Draw(m_pRenderTarget);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            bricks[i * 15 + j]->Draw(m_pRenderTarget);
        }
    }
    
    hr = m_pRenderTarget->EndDraw();

    return S_OK;
}