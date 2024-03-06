#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

//colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


//custom cube class

class Rubic
{
private:
	glm::mat4 cube_matrix;
	

};





static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
}

//for (int item : left_side)
//{
//	shapes[item]->MyRotate(45.0f, glm::vec3(1, 0, 0), 0);
//	//shapes[item]->MyTranslate(glm::vec3(0, 0, 0), 0);
//}

Game::Game(float angle ,float relationWH, float near1, float far1) : Scene(angle,relationWH,near1,far1)
{ 	
}

void Game::Init()
{		

	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader");
	
	AddTexture("../res/textures/plane.png",false);

	//AddShape(Plane,-1,TRIANGLES);
	//
	//pickedShape = 0;
	//
	//SetShapeTex(0,0);




	MoveCamera(0,zTranslate,10);
	pickedShape = -1;

	int size = 3;
	float distance = 1;
	int index = 0;

	
	for (float i = -distance; i <= distance; i += 1)
	{
		for (float j = -distance; j <= distance; j += 1)
		{
			for (float k = -distance; k <= distance; k += 1)
			{
				AddShape(Scene::Cube, -1, Scene::TRIANGLES);
				SetShapeTex(index, 0);
				shapes[index]->MyTranslate(glm::vec3(i, j, k), 0);
				shapes[index]->MyScale(glm::vec3(0.5, 0.5, 0.5));
				index++;
			}
		}

	}

	//shapes[front_side[6]]->MyScale(glm::vec3(0, 0, 0));
	//shapes[front_side[7]]->MyScale(glm::vec3(0, 0, 0));
	//shapes[front_side[8]]->MyScale(glm::vec3(0, 0, 0));

	//shapes[8]->MyScale(glm::vec3(0, 0, 0));
	//shapes[17]->MyScale(glm::vec3(0, 0, 0));
	//shapes[26]->MyScale(glm::vec3(0, 0, 0));

	//TESTING

	//for(int item : down_side)
	//{
	//	shapes[item]->MyScale(glm::vec3(0, 0, 0));
	//}

	//------


	//ReadPixel(); //uncomment when you are reading from the z-buffer
}


//for documentation of indeces, num will only will only work with 0,1,2. I'm expecting a 3x3 cube. mode == 1 is column, else is row


//sketch of how it should look like in documentation
// ---------------------------------
//			 down face
//			 back face
//left face,  up face,  right face
//			 front face
// ---------------------------------


//char* face_worth_of_spaces = "            ";
//int counter = 0;
//std::cout << face_worth_of_spaces;
//std::cout << "down side indeces: \n";
//for (int item : down_side)
//{
//	std::cout << face_worth_of_spaces;
//	if (counter % 3 == 0)
//	{
//		std::cout << "\n";
//	}
//	std::cout << item << " , ";
//
//	//counter++;
//
//}
//std::cout << "\n";


void Game::print_cube_faces() 
{
	char* border = "--------------------------------------------------\n";
	char* face_worth_of_spaces = "               ";
	int counter = 0;

	char* color = ""; //this will take different values throughout the prints as to indicate change from previous state

	std::cout << border;
	std::cout << face_worth_of_spaces;
	std::cout << "back: \n";
	for (int i = 0; i < 9; i++)
	{
		
		if (counter % 3 == 0)
		{
			std::cout << "\n";
			std::cout << face_worth_of_spaces;
		}

		//check if changed from prev print
		if(back_side[i] != back_side_prev[i])
		{
			color = GREEN;
		}
		else 
		{
			color = RESET;
		}

		std::cout << color << back_side[i] << RESET << " , ";

		counter++;

	}
	counter = 0;
	std::cout << "\n";



	std::cout << face_worth_of_spaces;
	std::cout << "up: \n";
	for (int i = 0 ; i < 9 ; i++)
	{
		
		if (counter % 3 == 0)
		{
			std::cout << "\n";
			std::cout << face_worth_of_spaces;
		}
		//check if changed from prev print
		if (up_side[i] != up_side_prev[i])
		{
			color = GREEN;
		}
		else
		{
			color = RESET;
		}
		std::cout << color << up_side[i] << RESET << " , ";

		counter++;

	}
	counter = 0;
	std::cout << "\n";



	
	std::cout << "\nleft:" << "          " << "front:" << "            " << "right: \n";
	for (int row = 0 ; row < 3; row++)
	{
		for(int left = row*3; left < row * 3 +3; left++)
		{
			if (left_side[left] != left_side_prev[left])
			{
				color = GREEN;
			}
			else
			{
				color = RESET;
			}
			std::cout << color << left_side[left] << RESET;
			if (left + 1 >= row * 3 + 3)
			{
				std::cout << "      ";
			}
			else 
			{
				std::cout << " , ";
			}

		}
		//std::cout << "   ";
		for (int front = row*3; front < row*3+3; front++)
		{
			if (front_side[front] != front_side_prev[front])
			{
				color = GREEN;
			}
			else
			{
				color = RESET;
			}
			std::cout << color << front_side[front] << RESET;
			if (front + 1 >= row * 3 + 3)
			{
				std::cout << "      ";
			}
			else
			{
				std::cout << " , ";
			}
		}
		//std::cout << "   ";
		for (int right = row*3; right < row * 3 +3; right++)
		{
			if (right_side[right] != right_side_prev[right])
			{
				color = GREEN;
			}
			else
			{
				color = RESET;
			}
			std::cout << color << right_side[right] << RESET;
			if (right + 1 >= row * 3 + 3)
			{
				std::cout << "      ";
			}
			else
			{
				std::cout << " , ";
			}
		}
		std::cout << "\n";
	}

	



	//i've inverted the y so it prints as per our initial perspective
	std::cout << face_worth_of_spaces;
	std::cout << "down: \n";
	for(int i = 0 ; i < 3 ; i++)
	{
		std::cout << "\n";
		std::cout << face_worth_of_spaces;
		for(int j = 0 ; j < 3 ; j++)
		{
			if (down_side[i*3+j] != down_side_prev[i * 3 + j])
			{
				color = GREEN;
			}
			else
			{
				color = RESET;
			}
			std::cout << color << down_side[i * 3 + j] << RESET << " , ";
			
		}
	}
	//counter = 0;
	std::cout << "\n";


	std::cout << border;

	//resetting the "prev" and updating it
	int* cube_sides_backup[6] = { front_side_prev ,back_side_prev, left_side_prev, right_side_prev, up_side_prev, down_side_prev };
	int* cube_sides_originals[6] = { front_side ,back_side, left_side, right_side, up_side, down_side };

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cube_sides_backup[i][j] = cube_sides_originals[i][j];
		}
	}



}





void Game::cube_rotation(int mode)
{
	int copy_front[9];
	int copy_back[9];
	int copy_left[9];
	int copy_right[9];
	int copy_up[9];
	int copy_down[9];

	int *cube_sides_backup[6] = { copy_front ,copy_back, copy_left, copy_right, copy_up, copy_down };
	int *cube_sides_originals[6] = { front_side ,back_side, left_side, right_side, up_side, down_side};

	//deep copy as backup
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cube_sides_backup[i][j] = cube_sides_originals[i][j];
		}
	}



	//num will only will only work with 0,1,2. I'm expecting a 3x3 cube

	//if (mode == 1) //meaning column - meaning left and right
	//{
	//	if (clockwise == 1) 
	//	{
	//		front_side[num] = copy_up[num];
	//		front_side[num +3] = copy_up[num +3];
	//		front_side[num +6] = copy_up[num +6];

	//		down_side[num] = copy_front[num];
	//		down_side[num + 3] = copy_front[num + 3];
	//		down_side[num + 6] = copy_front[num + 6];

	//		back_side[num] = copy_down[num];
	//		back_side[num + 3] = copy_down[num + 3];
	//		back_side[num + 6] = copy_down[num + 6];

	//		up_side[num] = copy_back[num];
	//		up_side[num + 3] = copy_back[num + 3];
	//		up_side[num + 6] = copy_back[num + 6];
	//	}
	//	else //counter clockwise
	//	{
	//		front_side[num] = copy_down[num];
	//		front_side[num + 3] = copy_down[num + 3];
	//		front_side[num + 6] = copy_down[num + 6];

	//		up_side[num] = copy_front[num];
	//		up_side[num + 3] = copy_front[num + 3];
	//		up_side[num + 6] = copy_front[num + 6];

	//		back_side[num] = copy_up[num];
	//		back_side[num + 3] = copy_up[num + 3];
	//		back_side[num + 6] = copy_up[num + 6];

	//		down_side[num] = copy_back[num];
	//		down_side[num + 3] = copy_back[num + 3];
	//		down_side[num + 6] = copy_back[num + 6];
	//	}

	//}

	//else if (mode == 2) //meaning row -up and down
	//{
	//	if (clockwise == 1)
	//	{
	//		//front_side[(num * 3)] = copy_right[(num * 3)];
	//		//front_side[(num * 3) + 1] = copy_right[(num * 3) + 1];
	//		//front_side[(num * 3) + 2] = copy_right[(num * 3) + 2];

	//		//left_side[(num * 3)] = copy_front[(num * 3)];
	//		//left_side[(num * 3) + 1] = copy_front[(num * 3) + 1];
	//		//left_side[(num * 3) + 2] = copy_front[(num * 3) + 2];

	//		//back_side[(num * 3)] = copy_left[(num * 3)];
	//		//back_side[(num * 3) + 1] = copy_left[(num * 3) + 1];
	//		//back_side[(num * 3) + 2] = copy_left[(num * 3) + 2];

	//		//right_side[(num * 3)] = copy_back[num * 3];
	//		//right_side[(num * 3) + 1] = copy_back[(num * 3) + 1];
	//		//right_side[(num * 3) + 2] = copy_back[(num * 3) + 2];

	//		front_side[]

	//	}
	//	else //counter clockwise
	//	{
	//		front_side[(num * 3)] = copy_left[(num * 3)];
	//		front_side[(num * 3) + 1] = copy_left[(num * 3) + 1];
	//		front_side[(num * 3) + 2] = copy_left[(num * 3) + 2];

	//		right_side[(num * 3)] = copy_front[(num * 3)];
	//		right_side[(num * 3) + 1] = copy_front[(num * 3) + 1];
	//		right_side[(num * 3) + 2] = copy_front[(num * 3) + 2];

	//		back_side[(num * 3)] = copy_right[num * 3];
	//		back_side[(num * 3) + 1] = copy_right[(num * 3) + 1];
	//		back_side[(num * 3) + 2] = copy_right[(num * 3) + 2];

	//		left_side[(num * 3)] = copy_back[num * 3];
	//		left_side[(num * 3) + 1] = copy_back[(num * 3) + 1];
	//		left_side[(num * 3) + 2] = copy_back[(num * 3) + 2];
	//	}
	//}
	if (mode == 1) //meaning left 
	{
		front_side[0] = left_side[2];
		front_side[3] = left_side[5];
		front_side[6] = left_side[8];

		back_side[0] = left_side[6];
		back_side[3] = left_side[3];
		back_side[6] = left_side[0];

		down_side[0] = left_side[8];
		down_side[3] = left_side[7];
		down_side[6] = left_side[6];

		up_side[0] = left_side[0];
		up_side[3] = left_side[1];
		up_side[6] = left_side[2];


	}

	else if (mode == 2) //meaning right 
	{
		front_side[2] = right_side[0];
		front_side[5] = right_side[3];
		front_side[8] = right_side[6];

		back_side[2] = right_side[8];
		back_side[5] = right_side[5];
		back_side[8] = right_side[2];

		down_side[2] = right_side[6];
		down_side[5] = right_side[7];
		down_side[8] = right_side[8];

		up_side[2] = right_side[2];
		up_side[5] = right_side[1];
		up_side[8] = right_side[0];
	}


	else if (mode == 3) //meaning up
	{
		front_side[0] = up_side[6];
		front_side[1] = up_side[7];
		front_side[2] = up_side[8];

		back_side[6] = up_side[0];
		back_side[7] = up_side[1];
		back_side[8] = up_side[2];

		left_side[0] = up_side[0];
		left_side[1] = up_side[3];
		left_side[2] = up_side[6];

		right_side[0] = up_side[8];
		right_side[1] = up_side[5];
		right_side[2] = up_side[2];
	}

	else if (mode == 4) //meaning down
	{
		front_side[6] = down_side[0];
		front_side[7] = down_side[1];
		front_side[8] = down_side[2];

		back_side[0] = down_side[6];
		back_side[1] = down_side[7];
		back_side[2] = down_side[8];

		left_side[6] = down_side[6];
		left_side[7] = down_side[3];
		left_side[8] = down_side[0];

		right_side[6] = down_side[2];
		right_side[7] = down_side[5];
		right_side[8] = down_side[8];
	}
	else if (mode == 5) //meaning front
	{
		up_side[6] = front_side[0];
		up_side[7] = front_side[1];
		up_side[8] = front_side[2];

		down_side[0] = front_side[6];
		down_side[1] = front_side[7];
		down_side[2] = front_side[8];

		left_side[2] = front_side[0];
		left_side[5] = front_side[3];
		left_side[8] = front_side[6];

		right_side[0] = front_side[2];
		right_side[3] = front_side[5];
		right_side[6] = front_side[8];
	}
	else if (mode == 6) //meaning back
	{
		up_side[0] = back_side[6];
		up_side[1] = back_side[7];
		up_side[2] = back_side[8];

		down_side[6] = back_side[0];
		down_side[7] = back_side[1];
		down_side[8] = back_side[2];

		left_side[0] = back_side[6];
		left_side[3] = back_side[3];
		left_side[6] = back_side[0];

		right_side[2] = back_side[8];
		right_side[5] = back_side[5];
		right_side[8] = back_side[2];
	}
	

}

void transpose_array(int* side_array, float clockwise) //doing hardcoded 3 by 3
{
	int original_copy[9];
	//deep copying input array
	for (int i = 0; i < 9; i++) 
	{
		original_copy[i] = side_array[i];
	}

	if(clockwise != 1)
	{
		//first row to first column
		side_array[0] = original_copy[2];
		side_array[3] = original_copy[1];
		side_array[6] = original_copy[0];
		//second
		side_array[1] = original_copy[5];
		side_array[4] = original_copy[4];
		side_array[7] = original_copy[3];

		//third
		side_array[2] = original_copy[8];
		side_array[5] = original_copy[7];
		side_array[8] = original_copy[6];
	}
	else //clockwise
	{
		//first row to third column
		side_array[2] = original_copy[0];
		side_array[5] = original_copy[1];
		side_array[8] = original_copy[2];
		//second
		side_array[1] = original_copy[3];
		side_array[4] = original_copy[4];
		side_array[7] = original_copy[5];

		//third
		side_array[0] = original_copy[6];
		side_array[3] = original_copy[7];
		side_array[6] = original_copy[8];
	
	}
}


void Game::cube_rotate_left_side()
{

	//do the rotation
	for (int item : left_side)
	{
		glm::mat4 transposed_rot = glm::transpose(shapes[item]->getRot());
		shapes[item]->MyRotate(90.0f, glm::vec3(clockwise * transposed_rot * glm::vec4(1, 0, 0, 1)), 0);
	}

	transpose_array(left_side, clockwise);
	cube_rotation(1);
	


}

void Game::cube_rotate_right_side()
{
	for (int item : right_side)
	{
		glm::mat4 transposed_rot = glm::transpose(shapes[item]->getRot());
		shapes[item]->MyRotate(90.0f, glm::vec3(( - 1 * clockwise )* transposed_rot * glm::vec4(1, 0, 0, 1)), 0);
	}

	transpose_array(right_side, (clockwise));
	cube_rotation(2);
	
}


void Game::cube_rotate_up_side()
{

	//do the rotation
	for (int item : up_side)
	{
		glm::mat4 transposed_rot = glm::transpose(shapes[item]->getRot());
		shapes[item]->MyRotate(90.0f, glm::vec3(( - 1 * clockwise) * transposed_rot * glm::vec4(0, 1, 0, 1)), 0);
	}

	transpose_array(up_side, (clockwise));
	cube_rotation(3);
	
}

void Game::cube_rotate_down_side()
{

	//do the rotation
	for (int item : down_side)
	{
		glm::mat4 transposed_rot = glm::transpose(shapes[item]->getRot());
		shapes[item]->MyRotate(90.0f, glm::vec3(clockwise * transposed_rot * glm::vec4(0, 1, 0, 1)), 0);
	}

	transpose_array(down_side, clockwise);
	cube_rotation(4);
	
}

void Game::cube_rotate_front_side()
{

	//do the rotation
	for (int item : front_side)
	{
		glm::mat4 transposed_rot = glm::transpose(shapes[item]->getRot());
		shapes[item]->MyRotate(90.0f, glm::vec3(( - 1 * clockwise) * transposed_rot * glm::vec4(0, 0, 1, 1)), 0);
	}

	transpose_array(front_side, clockwise);
	cube_rotation(5);
	
}

void Game::cube_rotate_back_side()
{

	//do the rotation
	for (int item : back_side)
	{
		glm::mat4 transposed_rot = glm::transpose(shapes[item]->getRot());
		shapes[item]->MyRotate(90.0f, glm::vec3(clockwise * transposed_rot * glm::vec4(0, 0, 1, 1)), 0);
	}

	transpose_array(back_side, clockwise);
	cube_rotation(6);
	
}

//cube sides
//int up_side[] = {6,7,8,15,16,17,24,25,26}; // relevant axis (0,1,0)
//int down_side[] = {0,1,2,9,10,11,18,19,20}; // relevant axis (0,1,0)
//int left_side[] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // relevant axis (1,0,0)
//int right_side[] = {18, 19, 20, 21, 22, 23, 24, 25, 26}; // relevant axis (1,0,0)
//int front_side[] = {0,3,6,9,12,15,18,21,24}; // relevant axis (0,0,1)
//int back_side[] = {2,5,8,11,14,17,20,23,26}; // relevant axis (0,0,1)

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal",Model);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
	if(shaderIndx == 0)
		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
	else 
		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	if(isActive)
	{
	}
}

Game::~Game(void)
{
}
