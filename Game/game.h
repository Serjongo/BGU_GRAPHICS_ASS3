#pragma once
#include "scene.h"

class Game : public Scene
{
public:

	Game();
	Game(float angle, float relationWH, float near, float far);
	void Init();
	void Update(const glm::mat4& MVP, const glm::mat4& Model, const int  shaderIndx);
	void ControlPointUpdate();
	void WhenRotate();
	void WhenTranslate();
	void Motion();

	//cube_controls
	void cube_rotate_left_side();
	void cube_rotate_right_side();
	void cube_rotate_up_side();
	void cube_rotate_down_side();
	void cube_rotate_front_side();
	void cube_rotate_back_side();



	//cube_face_angles
	//float left_face_angle();

	float get_angle();
	void increase_angle();
	void decrease_angle();


	float add_angle(float initial_angle,float added_angle);

	//for documentation
	void cube_rotation(int mode);
	void print_cube_faces();


	//cube_angles
	//float angles[] = {2.8125f,5.625f,11.25f,22.5f,45.0f,90.0f,180.0f}
	float angle = 90.0f; //initial value

	float left_face_angle = 0.0f;
	float right_face_angle = 0.0f;
	float front_face_angle = 0.0f;
	float back_face_angle = 0.0f;
	float up_face_angle = 0.0f;
	float down_face_angle = 0.0f;

	//this will only be updated once we reach a twist/2 twists
	float left_face_angle_proper = 0.0f;
	float right_face_angle_proper = 0.0f;
	float front_face_angle_proper = 0.0f;
	float back_face_angle_proper = 0.0f;
	float up_face_angle_proper = 0.0f;
	float down_face_angle_proper = 0.0f;

	//cube locks to prevent weird collisions
	int right_face_lock = 0;
	int left_face_lock = 0;
	int front_face_lock = 0;
	int back_face_lock = 0;
	int up_face_lock = 0;
	int down_face_lock = 0;

	//cube_sides
	//NOTE: we are looking from the perspective of a 2d-spread out cube, with the front being the center
	int up_side[9] = // relevant axis (0,1,0)
	{
		6,15,24,
		7,16,25,
		8,17,26
	};
	int down_side[9] = // relevant axis (0,1,0)
	{
		2,11,20,
		1,10,19,
		0,9,18
	};
	int left_side[9] = // relevant axis (1,0,0)
	{
		6, 7, 8,
		3, 4, 5,
		0, 1, 2
	};
	int right_side[9] = // relevant axis (1,0,0)
	{
		26, 25, 24,
		23, 22, 21,
		20, 19, 18
	};
	int front_side[9] = // relevant axis (0,0,1)
	{
		8,17,26,
		5,14,23,
		2,11,20
	};
	int back_side[9] = // relevant axis (0,0,1)
	{
		0,9,18,
		3,12,21,
		6,15,24
	};


	//cube_sides_prev - for documentation and checking diffs
	int up_side_prev[9] = // relevant axis (0,1,0)
	{
		6,15,24,
		7,16,25,
		8,17,26
	};
	int down_side_prev[9] = // relevant axis (0,1,0)
	{
		2,11,20,
		1,10,19,
		0,9,18
	};
	int left_side_prev[9] = // relevant axis (1,0,0)
	{
		6, 7, 8,
		3, 4, 5,
		0, 1, 2
	};
	int right_side_prev[9] = // relevant axis (1,0,0)
	{
		26, 25, 24,
		23, 22, 21,
		20, 19, 18
	};
	int front_side_prev[9] = // relevant axis (0,0,1)
	{
		8,17,26,
		5,14,23,
		2,11,20
	};
	int back_side_prev[9] = // relevant axis (0,0,1)
	{
		0,9,18,
		3,12,21,
		6,15,24
	};


	//rotation_mode
	float clockwise = 1; //by default clockwise, -1 is anti-clockwise

	~Game(void);
};

