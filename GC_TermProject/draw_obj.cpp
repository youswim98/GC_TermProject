//
//
//#include "draw_obj.h"
//
//void setTextureMapping(GLuint textureMonkey) {
//	int imgWidth, imgHeight, channels;
//	uchar* img = readImageData("monkey.bmp", &imgWidth, &imgHeight, &channels);
//
//	int texNum = 1;
//	glGenTextures(texNum, &textureMonkey);
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
//
//
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, img);
//}
//
//void draw_obj(ObjParser* objParser)
//{
//	glBegin(GL_TRIANGLES);
//	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
//		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
//			objParser->normal[objParser->normalIdx[n] - 1].y,
//			objParser->normal[objParser->normalIdx[n] - 1].z);
//		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
//			objParser->vertices[objParser->vertexIdx[n] - 1].y,
//			objParser->vertices[objParser->vertexIdx[n] - 1].z);
//
//		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
//			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
//			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
//		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
//			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
//			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);
//
//		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
//			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
//			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
//		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
//			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
//			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
//	}
//	glEnd();
//}
//void draw_obj_with_texture(ObjParser* objParser, GLuint textureMonkey)
//{
//	glDisable(GL_BLEND);
//	// glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_TRIANGLES);
//	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
//		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
//			objParser->textures[objParser->textureIdx[n] - 1].y);
//		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
//			objParser->normal[objParser->normalIdx[n] - 1].y,
//			objParser->normal[objParser->normalIdx[n] - 1].z);
//		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
//			objParser->vertices[objParser->vertexIdx[n] - 1].y,
//			objParser->vertices[objParser->vertexIdx[n] - 1].z);
//
//		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
//			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
//		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
//			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
//			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
//		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
//			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
//			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);
//
//		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
//			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
//		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
//			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
//			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
//		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
//			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
//			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
//	}
//	glEnd();
//	glEnable(GL_BLEND);
//}
//void draw_cube_textures(GLuint textureMonkey)
//{
//	int size = 2;
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_QUADS);
//	//Quad 1
//	glNormal3f(1.0f, 0.0f, 0.0f);   //N1
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
//  //Quad 2
//	glNormal3f(0.0f, 0.0f, -1.0f);  //N2
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
//  //Quad 3
//	glNormal3f(-1.0f, 0.0f, 0.0f);  //N3
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
//  //Quad 4
//	glNormal3f(0.0f, 0.0f, 1.0f);   //N4
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
//  //Quad 5
//	glNormal3f(0.0f, 1.0f, 0.0f);   //N5
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, size / 2, -size / 2);   //V6
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, size / 2, size / 2);   //V8
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, size / 2, size / 2);   //V2
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, size / 2, -size / 2);   //V4
//  //Quad 6
//	glNormal3f(1.0f, -1.0f, 0.0f);  //N6
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size / 2, -size / 2, size / 2);   //V7
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size / 2, -size / 2, -size / 2);   //V5
//	glTexCoord2f(1.0f, 0.0f); glVertex3f(size / 2, -size / 2, -size / 2);   //V3
//	glTexCoord2f(1.0f, 1.0f); glVertex3f(size / 2, -size / 2, size / 2);   //V1
//	glEnd();
//}
//
//void draw_textureCube(GLuint textureMonkey) {
//	glColor3f(1.0, 1.0, 1.0);	// white로 color를 set해주어야 texture색상이 제대로 적용 됨!
//	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//			// polygon의 원래 색상은 무시하고 texture로 덮음
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	// polygon의 원래 색상과 texture 색상을 곱하여 덮음, texture가 입혀진 표면에 광원 효과 설정 가능
////glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//		// texture의 색상으로 덮어 씌운다
//
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_QUADS);
//	glNormal3f(-1.0, 0, 0);	// -x axis
//	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, -1.0);
//	glTexCoord2f(1, 0); glVertex3f(-1.0, -1.0, -1.0);
//	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
//	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, 1.0);
//	glEnd();
//
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_QUADS);
//	glNormal3f(1.0, 0, 0);	//x axis
//	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
//	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, 1.0);
//	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, -1.0);
//	glTexCoord2f(0, 1); glVertex3f(1.0, 1.0, -1.0);
//	glEnd();
//
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_QUADS);
//	glNormal3f(0, -1.0, 0);	// -y axis
//	glTexCoord2f(0, 0); glVertex3f(-1.0, -1.0, -1.0);
//	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, -1.0);
//	glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, 1.0);
//	glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, 1.0);
//	glEnd();
//
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_QUADS);
//	glNormal3f(0, 1.0, 0);	// y axis
//	glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, 1.0);
//	glTexCoord2f(1, 0); glVertex3f(1.0, 1.0, 1.0);
//	glTexCoord2f(1, 1); glVertex3f(1.0, 1.0, -1.0);
//	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, -1.0);
//	glEnd();
//
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_QUADS);
//	glNormal3f(0, 0, 1.0);	//z axis
//	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, 1.0);
//	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, 1.0);
//	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, 1.0);
//	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, 1.0);
//	glEnd();
//
//	glBindTexture(GL_TEXTURE_2D, textureMonkey);
//	glBegin(GL_QUADS);
//	glNormal3f(0, 0, -1.0);	//-z축
//	glTexCoord2f(0, 0); glVertex3f(1.0, 1.0, -1.0);
//	glTexCoord2f(1, 0); glVertex3f(-1.0, 1.0, -1.0);
//	glTexCoord2f(1, 1); glVertex3f(-1.0, -1.0, -1.0);
//	glTexCoord2f(0, 1); glVertex3f(1.0, -1.0, -1.0);
//	glEnd();
//
//}
//
//void get_resource(const char* str, ObjParser* monkey)
//{
//	monkey = new ObjParser(str);
//}