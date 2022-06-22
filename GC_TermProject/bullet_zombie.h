#pragma once
#include<cmath>
#include<stdio.h>
#include <gl/glut.h>
#include <gl/freeglut.h>

class bullet {
public:
	float position[3];
	float direction[3];
	float speed;


	bullet(float* posi, float* dir, float spd) {

		float gen = sqrt(dir[0] * dir[0] + dir[1] * dir[1]); //����

		this->position[0] = posi[0];
		this->position[1] = posi[1] - 3;
		this->position[2] = posi[2];

		this->direction[0] = dir[0];
		this->direction[1] = dir[1];
		this->direction[2] = dir[2];

		this->speed = spd;
	}
	~bullet() {
		printf("bullet �Ҹ�!\n"); //���� �浹�� ���, �̰����� �Ҹ��Ű�� �� �� ����.
	}
	void moving() {
		this->position[0] += this->speed * direction[0];
		this->position[2] += this->speed * direction[2];
	}
};


class zombie2 {
public:
	float worldPosition[3];
	float worldDirection[3];
	float localAngle;
	float speed;


	zombie2(float* posi, float* dir, float spd) {

		for (int i = 0; i < 3; i++) {
			this->worldPosition[i] = posi[i];
			this->worldDirection[i] = dir[i];
			this->localAngle = 0;
		}

		this->speed = spd;
	}
	~zombie2() {
		printf("zombie �Ҹ�!\n"); //���� �浹�� ���, �̰����� �Ҹ��Ű�� �� �� ����.
	}

	void calc_angle(float* worldDirection, float* camPosi) {
		float tempAngle = acos(worldDirection[0]) * 180.0 / 3.141592;
		//printf("tempAngle : %f\n", tempAngle);
		if (camPosi[2] - worldPosition[2] >= 0)
			this->localAngle = -tempAngle;
		else
			this->localAngle = tempAngle;
		//this->localAngle = tempAngle;
		
	}
	void moving(float* zombieVector, float* camPosi) {
		//cam�� ��ġ���Ϳ� ���� ������ ��ġ������ ���� ���ϰ�
		//���񿡼� cam������ �������͸� ���Ѵ�.
		//�� �������͸� ���� ������ ��ġ�� ���Ѵ�.

		for (int i = 0; i < 3; i++) {
			zombieVector[i] = camPosi[i] - this->worldPosition[i];
		}//���� -> ���� ����
		float posiSize = sqrt(
			pow(zombieVector[0], 2)
			+ pow(zombieVector[1], 2)
			+ pow(zombieVector[2], 2));
		//���� -> ���� ���� ũ�� 
		for (int i = 0; i < 3; i++) {
			this->worldDirection[i] = zombieVector[i] / posiSize;
			//���⺤�͸� ���⺤�� ũ��� �������ν�
			//�������͸� ����.
		}

		this->worldPosition[0] += this->speed * worldDirection[0];
		this->worldPosition[2] += this->speed * worldDirection[2];
		calc_angle(worldDirection, camPosi);
	
	}

};