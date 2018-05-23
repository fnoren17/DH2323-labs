#include "MyQuat.h"

using namespace MyMathLab;

///YOUR CODE HERE
#define PI 3.14159265

MyQuat::MyQuat(void) {
}
MyQuat::MyQuat(float angleDeg, MyVector &axis) {
	float angleRad = angleDeg * PI / 180.0;
	this->w = cos(angleRad / 2.0);
	this->v = axis;
	this->v.normalise();
	
	this->v = this->v.multiplyScalar(sin(angleRad / 2.0));
}
MyQuat::MyQuat(MyPosition &p) {
	this->w = 0.0;
	this->v.x = p.x;
	this->v.y = p.y;
	this->v.z = p.z;
	this->v.normalise();
}


MyQuat MyQuat::addTo(const MyQuat &other) const
{
	MyQuat result;
	result.w = other.w + this->w;
	result.v.x = other.v.x + this->v.x;
	result.v.y = other.v.x + this->v.y;
	result.v.z = other.v.x + this->v.z;

	return result;
	
}

MyQuat MyQuat::multiplyBy(const MyQuat &other) const
{
	/* 
	w1 = this.w
	v1 = this.v
	w2 = other.w
	v2 = other.v
	*/

	MyQuat result;

	result.w = this->w*other.w - this->v.getDotProduct(other.v);
	MyVector v1crossv2 = this->v.getCrossProduct(other.v);
	MyVector w1v2;
	MyVector w2v1;
	w1v2.x = this->w * other.v.x;
	w1v2.y = this->w * other.v.y;
	w1v2.z = this->w * other.v.z;
	
	w2v1.x = other.w * this->v.x;
	w2v1.y = other.w * this->v.y;
	w2v1.z = other.w * this->v.z;

	result.v = v1crossv2.addTo(w1v2.addTo(w2v1));

	return result;

}

float MyQuat::getMagnitude(void) const
{
	return sqrt((this->w * this->w) + (this->v.x * this->v.x) + (this->v.y * this->v.y) + (this->v.z * this->v.z));
}

void MyQuat::normalise(void)
{
	float len = getMagnitude();
	
	if (len > 0.0f)
	{
		this->w = this->w / len;
		this->v = this->v.multiplyScalar(1.0 / len);
	}
}

MyQuat MyQuat::getConjugate(void) const
{
	MyQuat result;

	result.w = this->w;
	result.v = this->v.multiplyScalar(-1.0);
	return result;
}


MyQuat MyQuat::getInverse(void) const 
{
	float bottom = getMagnitude()*getMagnitude();
	MyQuat result;
	result.w = this->w / bottom;
	result.v = this->v.multiplyScalar(-1.0/bottom);
	return result;
}

MyMatrix MyQuat::convertToRotationMatrix(void) const 
{
	MyQuat normal;
	normal.w = this->w;
	normal.v = this->v;
	normal.normalise();

	GLfloat rotMatrix[16] = 
	{
		(normal.w*normal.w) + (normal.v.x*normal.v.x) - (normal.v.y*normal.v.y) - (normal.v.z*normal.v.z),
		2.0 * normal.v.x * normal.v.y - 2.0 * normal.w * normal.v.z,
		2.0 * normal.v.x * normal.v.z + 2.0 * normal.w * normal.v.y,
		0.0,
		2.0 * normal.v.x * normal.v.y + 2.0 * normal.w * normal.v.z,
		(normal.w*normal.w) - (normal.v.x*normal.v.x) + (normal.v.y*normal.v.y) - (normal.v.z*normal.v.z),
		2.0 * normal.v.y * normal.v.z - 2.0 * normal.w * normal.v.x,
		0.0,
		2.0 * normal.v.x * normal.v.z - 2.0 * normal.w * normal.v.y,
		2.0 * normal.v.y * normal.v.z + 2.0 * normal.w * normal.v.x,
		(normal.w*normal.w) - (normal.v.x*normal.v.x) - (normal.v.y*normal.v.y) + (normal.v.z*normal.v.z),
		0.0,
		0.0, 0.0, 0.0, 1.0
	};
	MyMatrix matrix(rotMatrix);
	return matrix;
}