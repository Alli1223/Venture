#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	enum {
		TARGET_MODE_NORMAL = 0,
		TARGET_MODE_CENTER
	};
public:
	void OnMove(int MoveX, int MoveY);

	int TargetMode;

	int GetX();
	int GetY();

	void SetPos(int X, int Y);

	void SetTarget(int* X, int* Y);

	static Camera CameraControl;

private:
	int X;
	int Y;

	int* TargetX;
	int* TargetY;

	int WindowWidth = 1920;
	int WindowHeight = 1080;




};


