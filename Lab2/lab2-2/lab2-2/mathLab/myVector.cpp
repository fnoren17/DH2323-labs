#include "MyVector.h"

using namespace MyMathLab;

MyVector::MyVector(void)
{
	this->x = this->y = this->z = 0.0;
}

MyVector::MyVector(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

MyVector::MyVector(MyPosition& start, MyPosition& end)
{
	this->x = end.x - start.x;
	this->y = end.y - start.y;
	this->z = end.z - start.z;
}

MyVector MyVector::addTo(const MyVector &other) const
{
	MyVector result;
	//your code here
	result.x = other.x + this->x;
	result.y = other.y + this->y;
	result.z = other.z + this->z;

	return result;
}

MyVector MyVector::subtractFrom(const MyVector &other) const
{
	MyVector result;
	//your code here
	result.x = other.x - this->x;
	result.y = other.y - this->y;
	result.z = other.z - this->z;
	return result;
}
		
float MyVector::getMagnitude(void) const
{
	double result;
	//your code here
	result = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	return result;
}

void MyVector::uniformScale(const float m)
{
	//your code here
}

void MyVector::normalise(void)
{
	//your code here
	float len = getMagnitude();
	if (len > 0.0f)
	{
		this->x = this->x / len;
		this->y = this->y / len;
		this->z = this->z / len;
	}
}

void MyVector::setMagnitude(const float m)
{
	if (this->getMagnitude() > 0.0)
	{
		this->normalise();
		this->uniformScale(m);
	}
}
	
float MyVector::getDotProduct(const MyVector &other) const
{
	float result;
	//your code here
	result = other.x*this->x + other.y*this->y + other.z*this->z;
	return result;
}

MyVector MyVector::getCrossProduct(const MyVector &other) const
{
	MyVector result;
	//your code here
	result.x = other.z*this->y - other.y*this->z;
	result.y = other.x*this->z - this->x*other.z;
	result.z = other.y*this->x - other.x*this->y;
	return result;
}

MyVector MyVector::multiplyScalar(const float scalar) const
{
	MyVector result;
	if (fabs(this->x) < 0.000001)
	{
		result.x = 0.0;
	}
	else
	{
		result.x = this->x*scalar;
	}
	if (fabs(this->y) < 0.000001)
	{
		result.y = 0.0;
	}
	else
	{
		result.y = this->y*scalar;
	}
	if (fabs(this->z) < 0.000001)
	{
		result.z = 0.0;
	}
	else
	{
		result.z = this->z*scalar;
	}
	
	return result;
}