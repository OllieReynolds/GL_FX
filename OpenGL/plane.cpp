#include "plane.hpp"

Plane::Plane(float sizeX, float sizeZ, int facesX, int facesZ) {
	faces = facesX * facesZ;

	float* vertices = new float[3 * (facesX + 1) * (facesZ + 1)];
	float* normals = new float[3 * (facesX + 1) * (facesZ + 1)];
	float* uvs = new float[2 * (facesX + 1) * (facesZ + 1)];
	unsigned int* indices = new unsigned int[6 * facesX * facesZ];

	float x2 = sizeX / 2.0f;
	float z2 = sizeZ / 2.0f;

	float iFactor = (float)sizeZ / facesZ;
	float jFactor = (float)sizeX / facesX;
	float iUV = 32.f / facesZ;
	float jUV = 32.f / facesX;
	float x, z;
	int vTemp = 0, uvTemp = 0;

	for (int i = 0; i <= facesZ; i++) {
		z = iFactor * i - z2;
		for (int j = 0; j <= facesX; j++) {
			x = jFactor * j - x2;
			vertices[vTemp] = x;
			vertices[vTemp+1] = 0.0f;
			vertices[vTemp+2] = z;
			normals[vTemp] = 0.0f;
			normals[vTemp+1] = 1.0f;
			normals[vTemp+2] = 0.0f;
			vTemp += 3;
			uvs[uvTemp] = j * iUV;
			uvs[uvTemp+1] = i * jUV;
			uvTemp += 2;
		}
	}

	unsigned int rowStart, nextRowStart;
	int idx = 0;
	for (int i = 0; i < facesZ; i++) {
		rowStart = i * (facesX+1);
		nextRowStart = (i+1) * (facesX+1);
		for (int j = 0; j < facesX; j++) {
			indices[idx] = rowStart + j;
			indices[idx+1] = nextRowStart + j;
			indices[idx+2] = nextRowStart + j + 1;
			indices[idx+3] = rowStart + j;
			indices[idx+4] = nextRowStart + j + 1;
			indices[idx+5] = rowStart + j + 1;
			idx += 6;
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(4, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * (facesX+1) * (facesZ+1) * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * (facesX+1) * (facesZ+1) * sizeof(float), uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, 3 * (facesX+1) * (facesZ+1) * sizeof(float), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * facesX * facesZ * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	unsigned char* image;
	int width, height;


	glActiveTexture(GL_TEXTURE2);
	glGenTextures(1, &texture_data);
	glBindTexture(GL_TEXTURE_2D, texture_data);
	image = SOIL_load_image("panel.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	SOIL_free_image_data(image);

	delete vertices;
	delete normals;
	delete uvs;
	delete indices;
}

Plane::~Plane() {

}

void Plane::draw() {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, 0);
}