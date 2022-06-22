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

		float gen = sqrt(dir[0] * dir[0] + dir[1] * dir[1]); //제곱

		this->position[0] = posi[0];
		this->position[1] = posi[1] - 3;
		this->position[2] = posi[2];

		this->direction[0] = dir[0];
		this->direction[1] = dir[1];
		this->direction[2] = dir[2];

		this->speed = spd;
	}
	~bullet() {
		printf("bullet 소멸!\n"); //벽과 충돌할 경우, 이것으로 소멸시키면 될 것 같음.
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
		printf("zombie 소멸!\n"); //벽과 충돌할 경우, 이것으로 소멸시키면 될 것 같음.
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
		//cam의 위치벡터와 현재 좀비의 위치벡터의 차를 구하고
		//좀비에서 cam방향의 단위벡터를 구한다.
		//그 단위벡터를 현재 좀비의 위치에 더한다.

		for (int i = 0; i < 3; i++) {
			zombieVector[i] = camPosi[i] - this->worldPosition[i];
		}//좀비 -> 유저 벡터
		float posiSize = sqrt(
			pow(zombieVector[0], 2)
			+ pow(zombieVector[1], 2)
			+ pow(zombieVector[2], 2));
		//좀비 -> 유저 벡터 크기 
		for (int i = 0; i < 3; i++) {
			this->worldDirection[i] = zombieVector[i] / posiSize;
			//방향벡터를 방향벡터 크기로 나눔으로써
			//단위벡터를 구함.
		}

		this->worldPosition[0] += this->speed * worldDirection[0];
		this->worldPosition[2] += this->speed * worldDirection[2];
		calc_angle(worldDirection, camPosi);
	
	}

};