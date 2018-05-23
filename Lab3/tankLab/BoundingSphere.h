#include "objloader.h"
#include <vector>
using namespace std;


struct Position
{
	float x;
	float y;
	float z;
};

class BoundingSphere
{
public:
	BoundingSphere(void);
	void initMesh(vector<ObjMesh*> listofMyMesh);
	float radius;
	Position center;

private:

	ObjMesh *myMesh;
};


