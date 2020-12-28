#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class BreakOut : public olc::PixelGameEngine
{
public:
	BreakOut()
	{
		sAppName = "TUTORIAL - BreakOut Clone";
	}

private: 
  float fBatPos = 20.0f;
  float fBatWidth = 40.0f;

  olc::vf2d vBall = { 200.0f, 200.0f };
  olc::vf2d vBallVel = { 200.0f, -100.0f };
  float fBatSpeed = 250.0f;
  float fBallRadius = 5.0f;

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
    // Handle user input 
    if (GetKey(olc::Key::LEFT).bHeld) fBatPos -= fBatSpeed * fElapsedTime;
    if (GetKey(olc::Key::RIGHT).bHeld) fBatPos += fBatSpeed * fElapsedTime;

    if (fBatPos < 11.0f) fBatPos = 11.0f;
    if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;

    // Update ball
    vBall += vBallVel * fElapsedTime;

    // Really crude arena detection 
    // flip in y direction
    if (vBall.y <= 10.0f) vBallVel.y *= -1.0f;
    // flip in x direction
    if (vBall.x <= 10.0f) vBallVel.x *= -1.0f;
    // flip in x direction (other side)
    if (vBall.x >= float(ScreenWidth()) - 10.0f) vBallVel.x *= -1.0f;

    // Check Bat 
    if (vBall.y >= (float(ScreenHeight()) - 20.0f) && (vBall.x > fBatPos) && (vBall.x < fBatPos + fBatWidth))
      vBallVel.y *= -1.0f;

    // check if ball has gone off screen
    if (vBall.y > ScreenHeight()) 
    {
      // reset ball location
      vBall = { 200.0f, 200.0f };
      // choose random direction 
      float fAngle = (float(rand()) / float(RAND_MAX)) * 2.0f * 3.14159f;
      vBallVel = { 300.0f * float(cos(fAngle)), 300.0f * float(sin(fAngle)) };
    }

    if (GetMouse(0).bHeld)
    { 
      vBall = { float(GetMouseX()), float(GetMouseY()) };
    }

    if (GetMouseWheel() > 0) fBallRadius += 1.0f;
		if (GetMouseWheel() < 0) fBallRadius -= 1.0f;
		if (fBallRadius < 5.0f) fBallRadius = 5.0f;

    // Erase previous frame 
    Clear(olc::DARK_BLUE);

    // Draw Boundary 
    DrawLine(10, 10, 502, 10, olc::YELLOW);
    DrawLine(10, 10, 10, 470, olc::YELLOW);
    DrawLine(502, 10, 502, 470, olc::YELLOW);

    // Draw Bat
    FillRect(int(fBatPos), ScreenHeight() - 20, int(fBatWidth), 10, olc::GREEN);

    // Draw Ball 
    FillCircle(vBall, 5, olc::CYAN);

    return true;
	}
};

int main()
{
	BreakOut demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();
	return 0;
}
