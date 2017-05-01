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
	void OnMove(int MoveX, int MoveY);

	int TargetMode;

	int getX();
	int getY();

	void SetPos(int X, int Y);

	void SetTarget(int* X, int* Y);

	int xoffset = 0, yoffset = 0;

	static Camera CameraControl;

private:
	int X;
	int Y;

	

	int* TargetX;
	int* TargetY;

	int WindowWidth = 1920;
	int WindowHeight = 1080;




};


