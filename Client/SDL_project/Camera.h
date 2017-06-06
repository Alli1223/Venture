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

	int setX(int newX) { return X = newX; }
	int setY(int newY) { return Y = newY; }

	void SetPos(int X, int Y);

	void SetTarget(int* X, int* Y);

	int xoffset = 0, yoffset = 0;
	int WindowWidth = 0;
	int WindowHeight = 0;

	static Camera CameraControl;

private:
	int X;
	int Y;

	int* TargetX;
	int* TargetY;

	




};


