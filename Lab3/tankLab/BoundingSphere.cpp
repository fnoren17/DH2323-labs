#include "BoundingSphere.h"
#include "stdio.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

BoundingSphere::BoundingSphere(void) {

}

void BoundingSphere::initMesh(vector<ObjMesh*> listofMyMesh)
{
	float maxX = 0.0;
	float maxY = 0.0;
	float maxZ = 0.0;
	float minX = 0.0;
	float minY = 0.0;
	float minZ = 0.0;

	for (int j = 0; j < listofMyMesh.size(); j++)
	{
		this->myMesh = listofMyMesh[j];

		float x, y, z;
		float size = myMesh->m_iNumberOfVertices;

		//float lenX, lenY, lenZ;

		for (int i = 0; i < size; i++)
		{
			float comp;
			x = myMesh->m_aVertexArray[i].x;
			y = myMesh->m_aVertexArray[i].y;
			z = myMesh->m_aVertexArray[i].z;

			maxX = max(x, maxX);
			maxY = max(y, maxY);
			maxZ = max(z, maxZ);

			minX = min(x, minX);
			minY = min(y, minY);
			minZ = min(z, minZ);
		}
	}

	float dX = maxX - minX;
	float dY = maxY - minY;
	float dZ = maxZ - minZ;

	float ret = max(dX, dY);
	float big = max(ret, dZ);

	float radius = big / 2.0;

	this->radius = radius;

	float minmaxX = minX + maxX;
	float minmaxY = minY + maxY;
	float minmaxZ = minZ + maxZ;
	

	this->center.x = minmaxX / 2.0;
	this->center.y = minmaxY / 2.0;
	this->center.z = minmaxZ / 2.0;

	printf("CENTER X: %f ", minmaxX / 2.0);
}


