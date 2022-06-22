
#include "draw_object.h"

void setWall(int x, int y, int z, GLuint* texName) {

	glColor3f(1.0, 1.0, 1.0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	//glTexCoord2f(0, 0); glVertex3i(x, 0, z);
	//glTexCoord2f(1, 0); glVertex3i(x, y, z);
	//glTexCoord2f(1, 1); glVertex3i(x, y, -z);
	//glTexCoord2f(0, 1); glVertex3i(x, 0, -z);
	glTexCoord2f(0, 0); glVertex3i(x, 0, -z);
	glTexCoord2f(x / 20, 0); glVertex3i(x, 0, z);
	glTexCoord2f(x / 20, y / 20); glVertex3i(x, y, z);
	glTexCoord2f(0, y / 20); glVertex3i(x, y, -z);
	glEnd();

	//glColor3f(1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -z);
	glTexCoord2f(0, 0); glVertex3i(x, 0, z); 
	glTexCoord2f(x / 20, 0); glVertex3i(-x, 0, z);
	glTexCoord2f(x / 20, y / 20); glVertex3i(-x, y, z);
	glTexCoord2f(0, y / 20);; glVertex3i(x, y, z);
	glEnd();

	//glColor3f(0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(x, 0, -z);
	glTexCoord2f(x / 10, 0); glVertex3f(-x, 0, -z);
	glTexCoord2f(x / 10, x / 10); glVertex3f(-x, 0, z);
	glTexCoord2f(0, x / 10); glVertex3f(x, 0, z);
	glEnd();

	//glColor3f(0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3i(-x, 0, z);
	glTexCoord2f(x/20, 0); glVertex3i(-x, 0, -z);
	glTexCoord2f(x/20, y/20); glVertex3i(-x, y, -z);
	glTexCoord2f(0, y/20); glVertex3i(-x, y, z);
	glEnd();

	//glColor3f(1, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0); glVertex3i(-x, 0, -z); 
	glTexCoord2f(x / 20, 0); glVertex3i(x, 0, -z);
	glTexCoord2f(x / 20, y / 20); glVertex3i(x, y, -z);
	glTexCoord2f(0, y / 20); glVertex3i(-x, y, -z);
	glEnd();

}


void draw_axis(void) {
	glLineWidth(3); // 좌표축 두께
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // x축
	glVertex3f(0, 0, 0);
	glVertex3f(20, 5, 0);

	glColor3f(0, 1, 0); // y축
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1); // z축
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
	glLineWidth(1);
}

