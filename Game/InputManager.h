#pragma once   //maybe should be static class
#include "display.h"
#include "game.h"


void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Game* scn = (Game*)glfwGetWindowUserPointer(window);
		double x2, y2;
		glfwGetCursorPos(window, &x2, &y2);
		scn->Picking((int)x2, (int)y2);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game* scn = (Game*)glfwGetWindowUserPointer(window);
	float zoomAmount = -(float)yoffset;
	scn->MoveCameraZ(scn->GetCurrentCameraIndex(), zoomAmount);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Game* scn = (Game*)glfwGetWindowUserPointer(window);

	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_SPACE:
			scn->clockwise = scn->clockwise * -1;

			if (scn->IsActive())
				scn->Deactivate();
			else
				scn->Activate();
			break;

		case GLFW_KEY_UP:
			//scn->MoveCamera(0, scn->zTranslate, 0.4f);
			scn->MyRotate(2.0f, glm::vec3(-1, 0, 0), 3);
			break;
		case GLFW_KEY_DOWN:
			scn->MyRotate(2.0f, glm::vec3(1, 0, 0), 3);
			//scn->MoveCamera(0, scn->zTranslate, -0.4f);
			break;
		case GLFW_KEY_LEFT:
			//scn->MoveCamera(0, scn->zTranslate, 0.4f);
			scn->MyRotate(2.0f, glm::vec3(0, -1, 0),3);
			break;
		case GLFW_KEY_RIGHT:
			//scn->MoveCamera(0, scn->zTranslate, -0.4f);
			scn->MyRotate(2.0f, glm::vec3(0, 1, 0), 3);
			break;


			//cube controls
		case GLFW_KEY_R:
			scn->cube_rotate_right_side();
			break;
		case GLFW_KEY_L:
			scn->cube_rotate_left_side();
			break;
		case GLFW_KEY_U:
			scn->cube_rotate_up_side();
			break;
		case GLFW_KEY_D:
			scn->cube_rotate_down_side();
			break;
		case GLFW_KEY_LEFT_CONTROL:
			scn->print_cube_faces();
			break;
		case GLFW_KEY_LEFT_SHIFT:
			scn->random_cuber_mixer();
			break;
		case GLFW_KEY_F:
			scn->cube_rotate_front_side();
			break;
		case GLFW_KEY_B:
			scn->cube_rotate_back_side();
			break;
		case GLFW_KEY_A:
			scn->increase_angle();
			break;
		case GLFW_KEY_Z:
			scn->decrease_angle();
			break;
		default:
			break;
		}
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Game* scn = (Game*)glfwGetWindowUserPointer(window);

	scn->UpdatePosition((float)xpos, (float)ypos);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		scn->MouseProccessing(GLFW_MOUSE_BUTTON_RIGHT);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		scn->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
	}

}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	Game* scn = (Game*)glfwGetWindowUserPointer(window);

	scn->Resize(width, height);

}

void Init(Display& display)
{
	display.AddKeyCallBack(key_callback);
	display.AddMouseCallBacks(mouse_callback, scroll_callback, cursor_position_callback);
	display.AddResizeCallBack(window_size_callback);
}