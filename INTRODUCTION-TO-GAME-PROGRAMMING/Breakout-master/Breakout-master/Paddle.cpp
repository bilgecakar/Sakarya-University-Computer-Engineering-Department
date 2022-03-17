#include "framework.h"
#include "Point2D.h"
#include "Paddle.h"
#include "Engine.h"

Paddle::Paddle(float yPos) : m_pBlueBrush(NULL), m_pWhiteBrush(NULL)
{
	// Initializes the position of the paddle with a fixed X position and Y being at the middle of the screen
	position.y = yPos;
	position.x = RESOLUTION_X / 2;
}

Paddle::~Paddle()
{
	SafeRelease(&m_pBlueBrush);
	SafeRelease(&m_pWhiteBrush);
}

void Paddle::Initialize(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Creates a blue brush for drawing
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&m_pBlueBrush
	);

	// Initialize text writing factory and format
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
	);

	m_pDWriteFactory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		50,
		L"", //locale
		&m_pTextFormat
	);

	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&m_pWhiteBrush
	);
}

void Paddle::MoveToPosition(int xPos)
{
	// Moves the paddle to a specified position, also making sure it doesn't go outside the screen
	position.x = xPos;
	if (position.x < PADDLE_WIDTH / 2)
	{
		position.x = PADDLE_WIDTH / 2;
	}
	if (position.x > RESOLUTION_X - PADDLE_WIDTH / 2)
	{
		position.x = RESOLUTION_X - PADDLE_WIDTH / 2;
	}
}

void Paddle::Draw(ID2D1HwndRenderTarget* m_pRenderTarget)
{
	// Draws a rectangle representing the paddle
	D2D1_RECT_F rectangle1 = D2D1::RectF(
		position.x - PADDLE_WIDTH / 2, position.y - 5,
		position.x + PADDLE_WIDTH / 2, position.y + 5
	);
	m_pRenderTarget->FillRectangle(&rectangle1, m_pBlueBrush);

}