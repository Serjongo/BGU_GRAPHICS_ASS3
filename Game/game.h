#pragma once
#include "scene.h"

class Game : public Scene
{
public:
	
	Game();
	Game(float angle,float relationWH,float near, float far);
	void Init();
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
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

	//for documentation
	void cube_rotation(int mode);
	void print_cube_faces();

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

