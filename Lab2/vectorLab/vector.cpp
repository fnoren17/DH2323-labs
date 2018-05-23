#include "vector.h"

using namespace MyOGLProg;

Vector::Vector(void)
{
	this->x = this->y = this->z = 0.0;
}

Vector::Vector(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

Vector::Vector(Position& start, Position& end)
{
	//initialise this vector from two positionss
	this->x = end.x - start.x;
	this->y = end.y - start.y;
	this->z = end.z - start.z;
}

Vector Vector::addTo(const Vector &other) const
{
	//add this vector to other and return the result
	Vector result;
	//your code here
	result.x = other.x + this->x;
	result.y = other.y + this->y;
	result.z = other.z + this->z;

	return result;
}

Vector Vector::subtractFrom(const Vector &other) const
{
	//subtract this vector from other and return the result
	Vector result;
	//your code here
	result.x = other.x - this->x;
	result.y = other.y - this->y;
	result.z = other.z - this->z;
	return result;
}
		
float Vector::getMagnitude(void) const
{
	//get the length of the vector
	float result;
	//your code here
	result = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	return result;
}

void Vector::setMagnitude(const float m)
{
	//set the length of the vector
	//your code here
	float direction = atan2(this->y, this->x);
	this->x = cos(direction)*m;
	this->y = sin(direction)*m;
}
	
float Vector::getDotProduct(const Vector &other) const
{
	//return the dot product between this vector and other
	float result;
	//your code here
	result = other.x*this->x + other.y*this->y + other.z*this->z;
	return result;
}

Vector Vector::getCrossProduct(const Vector &other) const
{
	//return the cross product between this vector and other
	Vector result;
	//your code here
	result.x = other.y*this->z - other.z*this->y;
	result.y = other.z*this->x - other.x*this->z;
	result.z = other.x*this->y - other.y*this->x;
	return result;
}

void Vector::normalise(void)
{
	//normalise this vector (set its length to 1)
	//your code here
	float len = getMagnitude();
	if (len > 0.0f)
	{
		this->x = this->x / len;
		this->y = this->y / len;
		this->z = this->z / len;
	}

}

