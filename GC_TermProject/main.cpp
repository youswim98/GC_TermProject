//컴퓨터 그래픽스 미니 프로젝트

//bullet* ts = new bullet();
//bullets.push_back(ts);
//위의 내용은 전역변수로는 사용하지 못하는 부분임.
//draw함수에 넣어야 할 듯

#include "draw_object.h"
#include "bullet_zombie.h"
#include "ObjParser.h"
#include "bmpfuncs.h"
#include <time.h>
#include <string>

GLuint textureZombieTop;
ObjParser* zombieTop;

GLuint textureZombieLeg;
ObjParser* zombieLeg;

GLuint textureMan;
ObjParser* man;

GLuint textureBack[2];



std::vector<bullet*> bullets;
std::vector<zombie2*> zombies;

float zombieSpeed = 0.3;

float bullet_direction[3];
float zombieVector[3] = { 0 ,0, 0 };
//계산 과정에서 중간 저장으로 사용하는 float배열


float userPosi[3] = { 0, 0, 0 };
float userRotateVector[3] = { 0, 1, 0 };
float userRotateAngle = 0;
float firstCamPosi[3] = { userPosi[0], userPosi[1] + 5, userPosi[2] };
float camFocus[3] = { 1,5,0 }, camUpVector[3] = { 0, 1, 0 };
bool firstPerson = true;
float thirdCamPosi[3] = { 0, 0, 0 };
float camPosi[3] = { 0, 0, 0 };
//캐릭터 위치 구현에 사용할 것임.

static float lx = 0.0f, ly = 0.0f, lz = -1.0f;

float camFromUser = 40.0;
float movingFoc[2] = { 0, 0 };
int movingCam[3] = { 0, 0, 0 };
float camAngle = 0;
float current_mouse_x = 0;

int userWallCollisionNot[2] = { 1, 1 };
//1이면 Collision발생했다는 뜻.
float userPosi_t[3] = { 0, 0, 0 };

const char* health3 = "@ @ @";
const char* health2 = "@ @";
const char* health1 = "@";

int health = 3;

clock_t startTime;
clock_t nowTime;
int score;
int start = 0;
char timeStr[50];
char scoreStr[50];
clock_t tempTime = clock();
clock_t coolTime = 0;
int difficultyTime = 0;

int wall[3] = { 200, 70, 200 };

bool bullet_wall_collision(bullet* b);

bool bullet_zombie_collision(bullet* b, zombie2* z);

void user_wall_collision(float* userPosi);

char cam_wall_collision();

bool user_zombie_collision(zombie2* z);


void light();

void material();

void init(void);

void idle(void);

void resize(int width, int height);

void move_user_fornt_back(int direction);

void move_user_left_right(int direction);

void move_cam_front_back(int direction);

void move_cam_left_right(int direction);

void keyboard(unsigned char key, int x, int y);

void light_posi();


void draw(void);

void motion(int x, int y);

void mouse(int button, int state, int x, int y);

void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue);

void manTextureMaping();

void wallTextureMapping();

void set_texture_mapping_zombie();

void set_texture_mapping_man();

void draw_obj_with_texture_zombie(ObjParser* objParser);

void draw_obj_with_texture_man(ObjParser* objParser);

void get_resource_zombie(const char* str);

void get_resource_man(const char* str);



int main(int argc, char** argv) {
	//printf("%f, %f, %f", firstCamPosi[0], firstCamPosi[1], firstCamPosi[2]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// double buffer로 변경
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("12171809 유수영");
	init();

	get_resource_zombie("obj/zombie_up6.obj");
	get_resource_man("obj/man4.obj");

	glutReshapeFunc(resize);
	glutDisplayFunc(draw); //윈도우의 위치 및 크기 변경시에 동작한다.

	//처음 윈도우 열때, 크기를 바꿀때 동작하는 함수이다.
	//변경된 윈도우의 폭과 높이를 전달한다.
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);

	glutMainLoop();

	return 0;
}

bool bullet_wall_collision(bullet* b) {
	//각 사분면을 나눠서, 4번의 조건문을 통과한다.
	//공이 1사분면에 있으면, x(+) z(+)
	//공이 2사분면에 있으면, x(-) z(+)
	//공이 3사분면에 있으면, x(-) z(-)
	//공이 4사분면에 있으면, x(+) z(-)

	if (int(b->position[0]) > wall[0] || int(b->position[0]) < -wall[0])
		return true;
	else if (int(b->position[2]) > wall[2] || int(b->position[2]) < -wall[2])
		return true;
	return false;
}

bool bullet_zombie_collision(bullet* b, zombie2* z) {
	int zombieRadius = 3;
	int bulletRadius = 1;
	float distanceBetweenObj = 0;
	float temp = 0;
	temp += pow(b->position[0] - z->worldPosition[0], 2);
	temp += pow(b->position[1] - (z->worldPosition[1] + 3.5), 2);
	temp += pow(b->position[2] - z->worldPosition[2], 2);

	distanceBetweenObj = sqrt(temp);

	if (distanceBetweenObj < zombieRadius + bulletRadius)
		return true;

	return false;
}

void user_wall_collision(float* userPosi_f) {

	int range = 8;

	if ((int(userPosi_f[0]) + range > wall[0]) || (int(userPosi_f[0]) - range < -wall[0]))
		userWallCollisionNot[0] = 0;

	else if ((int(userPosi_f[0]) + range <= wall[0]) || (int(userPosi_f[0]) - range >= -wall[0]))
		userWallCollisionNot[0] = 1;

	if ((int(userPosi_f[2]) + range > wall[2]) || (int(userPosi_f[2]) - range < -wall[2]))
		userWallCollisionNot[1] = 0;

	else if ((int(userPosi_f[2]) + range <= wall[2]) || (int(userPosi_f[2]) - range >= -wall[2]))
		userWallCollisionNot[1] = 1;
}

bool user_zombie_collision(zombie2* z) {

	//printf("nowTime : %d, cooltime : %d\n", nowTime, coolTime);
	if (double(nowTime - coolTime) > 2000) {

		int zombieRadius = 2;
		int manRadius = 2;
		float distanceBetweenObj = 0;
		float temp = 0;
		temp += pow(z->worldPosition[0] - userPosi[0], 2);
		temp += pow(z->worldPosition[1] - userPosi[1], 2);
		temp += pow(z->worldPosition[2] - userPosi[2], 2);

		distanceBetweenObj = sqrt(temp);

		if (distanceBetweenObj < zombieRadius + manRadius) {
			coolTime = nowTime;
			return true;
		}
	}

	return false;
}

char cam_wall_collision_x() {
	char axis;
	bool camWallCollision = false;
	if (thirdCamPosi[0] > wall[0]) {
		//camFromUser = abs(userPosi[0] - wall[0]) - 1;
		//printf("w반환\n");
		axis = 'w';
		camWallCollision = true;
	}
	else if (thirdCamPosi[0] < -wall[0]) {
		//camFromUser = abs(userPosi[0] + wall[0]) - 1;
		camWallCollision = true;
		axis = 'x';
	}
	if (camWallCollision)
		return axis;
	else {
		//printf("else실행\n");
		camFromUser = 40;
	}
}

char cam_wall_collision_z() {
	char axis;
	bool camWallCollision = false;
	if (thirdCamPosi[2] > wall[2]) {
		//camFromUser = abs(userPosi[2] - wall[2]) - 1;
		axis = 'y';
		camWallCollision = true;
	}
	else if (thirdCamPosi[2] < -wall[2]) {
		//camFromUser = abs(userPosi[2] + wall[2]) - 1;
		axis = 'z';
		camWallCollision = true;
	}
	if (camWallCollision)
		return axis;
	else {
		//printf("else실행\n");
		camFromUser = 40;
	}
}

void light() {
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
} //빛의 성질 설정 함수

void material() {
	GLfloat ambient_Sun[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse_Sun[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specular_Sun[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_Sun);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_Sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_Sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
} //물체의 빛 반사 성질 설정 함수

void init(void) {//처음에 한번만 실행됨
	light();
	material();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_LINE_SMOOTH);

	wallTextureMapping();
	set_texture_mapping_zombie();
	set_texture_mapping_man();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);


	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glFrontFace(GL_CCW); // Teapot은 CW로 정의됨, 원점에서 polygon을 바라봤을때, vertex가 CCW순서로 자리한다.
	glPolygonMode(GL_BACK, GL_FILL);




	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_BLEND);


}

void difficulty() {
	int temp = nowTime / 10000;
	if (temp != difficultyTime) {
		//printf("difficulty실행!\n");
		zombieSpeed += 0.01;
		difficultyTime = temp;
	}

}

void record_time() {
	nowTime = clock();
	float temp = double(nowTime - startTime);

	sprintf(timeStr, "time : %.2f", temp / 1000.0);
}

void record_score() {
	sprintf(scoreStr, "Score : %d", score);
}

void make_zombie() {
	srand((unsigned int)clock());
	int num = rand() % 8;
	float z_pos[3];
	float z_dir[3] = { 1, 0, 0 };
	float y = 0;
	if (num == 0) {
		z_pos[0] = -wall[0];
		z_pos[1] = y;
		z_pos[2] = -wall[2];
	}
	else if (num == 1) {
		z_pos[0] = -wall[0];
		z_pos[1] = y;
		z_pos[2] = 0;
	}
	else if (num == 2) {
		z_pos[0] = -wall[0];
		z_pos[1] = y;
		z_pos[2] = wall[2];
	}
	else if (num == 3) {
		z_pos[0] = 0;
		z_pos[1] = y;
		z_pos[2] = wall[2];
	}
	else if (num == 4) {
		z_pos[0] = wall[0];
		z_pos[1] = y;
		z_pos[2] = wall[2];
	}
	else if (num == 5) {
		z_pos[0] = wall[0];
		z_pos[1] = y;
		z_pos[2] = 0;
	}
	else if (num == 6) {
		z_pos[0] = wall[0];
		z_pos[1] = y;
		z_pos[2] = -wall[2];
	}
	else if (num == 7) {
		z_pos[0] = 0;
		z_pos[1] = y;
		z_pos[2] = -wall[2];
	}
	zombie2* z = new zombie2(z_pos, z_dir, zombieSpeed);
	zombies.push_back(z);

}

void reset() {
	start = 0;
	zombieSpeed = 0.3;
	//printf("start : %d", start);
	zombies.clear();
	bullets.clear();
}

void idle(void) {

	if (health <= 0 && start) {
		reset();
	}

	if (start) {
		difficulty();
		record_time();
		record_score();
		if (double(nowTime - tempTime) > 1000) {
			make_zombie();
			tempTime = nowTime;
		}
	}


	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->moving();
	}

	for (int i = 0; i < zombies.size(); i++) {
		zombies[i]->moving(zombieVector, firstCamPosi);
	}

	glutPostRedisplay();
}

void resize(int width, int height) {//윈도우 크기가 변할때마다 호출된다
	//printf("resize실행\n");
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)width / (double)height, 0.1, 1000);
}

void move_user_fornt_back(int direction)
{
	user_wall_collision(userPosi);
	if (!userWallCollisionNot[0] || !userWallCollisionNot[1]) {
		//printf("fristCollision\n");
		userPosi_t[0] = userPosi[0] + (float)direction * (lx) * 10;
		userPosi_t[2] = userPosi[2] + (float)direction * (lz) * 10;
		user_wall_collision(userPosi_t);
		if (!userWallCollisionNot[0] || !userWallCollisionNot[1]) {
			//printf("secondCollision\n");
		}
	}
	userPosi[0] = userPosi[0] + (float)direction * (lx)*userWallCollisionNot[0];
	userPosi[2] = userPosi[2] + (float)direction * (lz)*userWallCollisionNot[1];
	//printf("[0] : %d, [1] : %d\n", userWallCollisionNot[0], userWallCollisionNot[1]);
	move_cam_front_back(direction);
}

void move_user_left_right(int direction)
{
	user_wall_collision(userPosi);
	if (!userWallCollisionNot[0] || !userWallCollisionNot[1]) {
		//printf("fristCollision\n");
		userPosi_t[0] = userPosi[0] + (float)direction * (-lz) * 10;
		userPosi_t[2] = userPosi[2] + (float)direction * (lx) * 10;
		user_wall_collision(userPosi_t);
		if (!userWallCollisionNot[0] || !userWallCollisionNot[1]) {
			//printf("secondCollision\n");
		}
	}
	userPosi[0] = userPosi[0] + (float)direction * (-lz) * userWallCollisionNot[0];
	userPosi[2] = userPosi[2] + (float)direction * (lx)*userWallCollisionNot[1];
	move_cam_left_right(direction);
}


void move_cam_front_back(int direction) {

	firstCamPosi[0] = firstCamPosi[0] + (float)direction * (lx)*userWallCollisionNot[0];
	firstCamPosi[2] = firstCamPosi[2] + (float)direction * (lz)*userWallCollisionNot[1];
}

void move_cam_left_right(int direction) {
	firstCamPosi[0] = firstCamPosi[0] + (float)direction * (-lz) * userWallCollisionNot[0];
	firstCamPosi[2] = firstCamPosi[2] + (float)direction * (lx)*userWallCollisionNot[1];
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w') {
		//printf("w\n");
		move_user_fornt_back(1);
	}
	else if (key == 'a') {
		//printf("a\n");
		move_user_left_right(-1);
	}
	else if (key == 's') {
		//printf("s\n");
		move_user_fornt_back(-1);
	}
	else if (key == 'd') {
		//printf("d\n");
		move_user_left_right(1);
	}
	else if (key == 't') {
		//printf("t\n");
		firstPerson = !firstPerson;
	}
	else if (key == 'z') {
		float z_dir[3] = { 1, 0, 0 };
		float z_pos[3] = { 0, 0, 0 };
		zombie2* z = new zombie2(z_pos, z_dir, 0.05);
		zombies.push_back(z);
	}
	else if (key == 'p')
	{
		//printf("key : p, start : %d\n", start);

		if (start == 0) {
			health = 3;
			score = 0;
			startTime = clock();
			start = 1;
		}
		else if (start == 1) {
			reset();
		}

	}
	glutPostRedisplay();
}

void light_posi() {
	GLfloat light_position[] = { 0.0, 30.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}


void draw(void) {
	char axis = 't';
	float distanceX;
	float distanceZ;
	//printf("draw실행\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//단위행렬로 초기화

	camFocus[0] = firstCamPosi[0] + lx;
	camFocus[1] = firstCamPosi[1] + ly;
	camFocus[2] = firstCamPosi[2] + lz;

	if (!firstPerson) {
		thirdCamPosi[0] = userPosi[0] - (lx * 40);
		thirdCamPosi[1] = userPosi[1] + 10;
		thirdCamPosi[2] = userPosi[2] - (lz * 40);

		camPosi[0] = userPosi[0] - (lx * camFromUser);
		camPosi[1] = userPosi[1] + 10;
		camPosi[2] = userPosi[2] - (lz * camFromUser);

		axis = cam_wall_collision_x();
		//printf("[0] : %f, [1] : %f, [2] : %f\n", lx, userPosi[1], lz);
		//어떤 방향의 벽과 충돌이 일어났는지, 넘어간 카메라의 좌표는 얼마나 되는지 알아야 함.
		if (axis == 'w') {//w : x, x : -x, y : z, z : -z
			//printf("w실asdf행\n");
			distanceX = thirdCamPosi[0] - wall[0];
			camPosi[0] -= distanceX;
		}
		else if (axis == 'x') {
			//printf("x실행\n");
			distanceX = thirdCamPosi[0] + wall[0];
			camPosi[0] -= distanceX;
		}
		axis = cam_wall_collision_z();
		if (axis == 'y') {
			distanceZ = thirdCamPosi[2] - wall[2];
			camPosi[2] -= distanceZ;

		}
		else if (axis == 'z') {
			distanceZ = thirdCamPosi[2] + wall[2];
			camPosi[2] -= distanceZ;
		}



		//printf("3인칭 실행\n");
	}
	else {
		camPosi[0] = firstCamPosi[0];
		camPosi[1] = firstCamPosi[1];
		camPosi[2] = firstCamPosi[2];
		glTranslatef(3, 0, 2);
		//printf("1인칭 실행\n");
	}
	gluLookAt(camPosi[0], camPosi[1], camPosi[2],
		camFocus[0], camFocus[1], camFocus[2],
		camUpVector[0], camUpVector[1], camUpVector[2]);

	for (int i = 0; i < bullets.size(); i++) {//bullet vs 벽 충돌 확인 & bullet 그리기
		if (bullet_wall_collision(bullets[i])) {
			bullets[i]->~bullet();
			bullets.erase(bullets.begin() + i);
		}
		glPushMatrix();
		glTranslatef(
			bullets[i]->position[0],
			bullets[i]->position[1],
			bullets[i]->position[2]
		);
		glColor3f(1, 1, 1);
		glutSolidSphere(1, 50, 50);
		glPopMatrix();
	}

	for (int i = 0; i < zombies.size(); i++) {//bullet vs zombie 벽 충돌 확인 & zombie 그리기
		for (int j = 0; j < bullets.size(); j++) {
			if (bullet_zombie_collision(bullets[j], zombies[i])) {
				bullets[i]->~bullet();
				bullets.erase(bullets.begin() + j);
				zombies[i]->~zombie2();
				zombies.erase(zombies.begin() + i);
				score++;
			}
		}

		if (user_zombie_collision(zombies[i])) {
			health--;
			printf("user_zombie_collision_true!!\n");
		}
		glPushMatrix();
		glTranslatef(zombies[i]->worldPosition[0],
			zombies[i]->worldPosition[1],
			zombies[i]->worldPosition[2]);
		glRotatef(
			zombies[i]->localAngle, 0, 1, 0);
		//draw_axis();
		//glColor3f(1, 0, 1);
		//glutSolidTeapot(2);
		glColor3f(1, 1, 1);
		draw_obj_with_texture_zombie(zombieTop);
		glPopMatrix();
	}


	glPushMatrix();
	glTranslatef(userPosi[0], userPosi[1], userPosi[2]);
	glRotatef(-userRotateAngle, userRotateVector[0], userRotateVector[1], userRotateVector[2]);
	//draw_axis();
	glColor3f(1, 1, 1);
	//glutWireTeapot();
	draw_obj_with_texture_man(man);
	glPopMatrix();


	//draw_axis();
	setWall(wall[0], wall[1], wall[2], textureBack);
	light_posi();

	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, timeStr, 6, 9, 1, 1, 1);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, scoreStr, 6, 8, 1, 1, 1);
	if (health == 3)
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, health3, -9, 9, 1, 1, 1);
	else if (health == 2)
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, health2, -9, 9, 1, 1, 1);
	else if (health == 1)
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, health1, -9, 9, 1, 1, 1);
	else
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER!", -9, 9, 1, 1, 1);

	glFlush();
	glutSwapBuffers();
	// back buffer를 front buffer로 변경
}

void motion(int x, int y) {
	if (current_mouse_x != x) {
		//printf("x : %d\n", x);
		camAngle += ((current_mouse_x - x) / 100.0);//x가 1픽셀 움직일때마다, 0.01라디안 변화.
		//printf("camAngle : %f\n", camAngle);
		userRotateAngle = camAngle * 180 / 3.141592;
		//printf("userRotateAngle : %f\n", userRotateAngle);
		lx = cos(camAngle);//삼각함수는 라디안을 입력으로 받는다.
		lz = sin(camAngle);
		float tmp = pow(lx, 2) + pow(lz, 2);
		tmp = sqrt(tmp);
		//printf("lx lz : %f\n", tmp);
		if (camAngle > 360)
			camAngle -= 360;
		current_mouse_x = x;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	//printf("마우스 좌클릭 눌림!\n");
	if (state == 0) {
		for (int i = 0; i < 3; i++) {
			bullet_direction[i] = camFocus[i] - firstCamPosi[i];
			printf("bullet_direction[%d] : %f\n", i, bullet_direction[i]);
		}
		//printf("cam_posi : %f %f %f\n", firstCamPosi[0], firstCamPosi[1], firstCamPosi[2]);
		//printf("cam_focus : %f %f %f\n", camFocus[0], camFocus[1], camFocus[2]);
		float temp[3] = { firstCamPosi[0] + 5 * lx, firstCamPosi[1] + 3.5, firstCamPosi[2] + 5 * lz };
		bullet* b = new bullet(temp, bullet_direction, 5);
		bullets.push_back(b);
	}
}

void manTextureMaping() {
	int imgWidth, imgHeight, channels;
	//uchar* img = readImageData("obj/zombie_up_uv.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img = readImageData("obj/man_uv.bmp", &imgWidth, &imgHeight, &channels);



	int texNum = 1;
	glGenTextures(texNum, &textureZombieTop);
	glBindTexture(GL_TEXTURE_2D, textureZombieTop);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, img);
}

void wallTextureMapping() {
	int imgWidth, imgHeight, channels;
	//uchar* img = readImageData("obj/zombie_up_uv.bmp", &imgWidth, &imgHeight, &channels);

	uchar* img;
	int texNum = 2;
	glGenTextures(texNum, textureBack);
	for (int i = 0; i < 2; i++) {
		glBindTexture(GL_TEXTURE_2D, textureBack[i]);
		if (i == 0)
			img = readImageData("img/side.bmp", &imgWidth, &imgHeight, &channels);
		else
			img = readImageData("img/floor.bmp", &imgWidth, &imgHeight, &channels);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

}

void set_texture_mapping_zombie() {
	int imgWidth, imgHeight, channels;
	//uchar* img = readImageData("obj/zombie_up_uv.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img = readImageData("obj/zombie_up_uv.bmp", &imgWidth, &imgHeight, &channels);

	int texNum = 1;
	glGenTextures(texNum, &textureZombieTop);
	glBindTexture(GL_TEXTURE_2D, textureZombieTop);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, img);
}

void set_texture_mapping_man() {
	int imgWidth, imgHeight, channels;
	//uchar* img = readImageData("obj/zombie_up_uv.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img = readImageData("obj/man_uv.bmp", &imgWidth, &imgHeight, &channels);

	int texNum = 1;
	glGenTextures(texNum, &textureMan);
	glBindTexture(GL_TEXTURE_2D, textureMan);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, img);
}


void draw_obj_with_texture_zombie(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, textureZombieTop);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) { //3씩 증가한다.
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}

void draw_obj_with_texture_man(ObjParser* objParser)
{
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, textureMan);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) { //3씩 증가한다.
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}

void get_resource_zombie(const char* str)
{
	zombieTop = new ObjParser(str);
}
void get_resource_man(const char* str)
{
	man = new ObjParser(str);
}


void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue) {
	glPushAttrib(GL_LIGHTING_BIT); //속성 push
	glDisable(GL_LIGHTING); // 조명효과 끄고
	glMatrixMode(GL_PROJECTION); // 2d처럼 보이기 위해서는 projection으로
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}