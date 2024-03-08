#include "MovableGLM.h"
#include <stdio.h>
#include "../res/includes/glm/gtc/matrix_transform.hpp"
#include "../res/includes/glm/gtc/quaternion.hpp"


static void printMat(const glm::mat4 mat)
{
	printf(" matrix: \n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f ", mat[j][i]);
		printf("\n");
	}
}

MovableGLM::MovableGLM()
{
	ZeroTrans();
}

glm::mat4 MovableGLM::MakeTrans(const glm::mat4 &prevTransformations) const
{
	return prevTransformations * MakeTrans();
}

glm::mat4 MovableGLM::MakeTrans() const
{
	return   rot * trans * scl;
}

void MovableGLM::MyTranslate(glm::vec3 delta,int mode)
{
	//glm::mat4 transposed_trans = glm::transpose(trans);
	trans = glm::translate(trans,delta);
}

void MovableGLM::MyRotate(float angle, const glm::vec3& vec, int mode)
{
	if (mode == 3)
	{
		
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, vec);

		// Apply the rotation matrix to the current rotation
		rot = rotationMatrix * rot;
	}
	else 
	{
		glm::mat4 transposed_rot = glm::transpose(rot);
		rot = glm::rotate(rot, angle, vec);
	}
}
	
void  MovableGLM::MyScale(glm::vec3 scale)
{
	scl = glm::scale(scl,scale);
}

void MovableGLM::ZeroTrans()
{
	trans = glm::mat4(1);
	rot = glm::mat4(1);
	scl = glm::mat4(1);
}

glm::mat4 MovableGLM::getTrans() 
{
	return trans;
}
glm::mat4 MovableGLM::getRot() 
{
	return rot;
}
glm::mat4 MovableGLM::getScl()
{
	return scl;
}

void MovableGLM::setRot(glm::mat4 rot)
{
	this->rot = rot;
}

void MovableGLM::setTrans(glm::mat4 trans)
{
	this->trans = trans;
}
void MovableGLM::setScale(glm::mat4 scale)
{
	this->scl = scale;
}

//void MovableGLM::Rotate_around_axis(glm)