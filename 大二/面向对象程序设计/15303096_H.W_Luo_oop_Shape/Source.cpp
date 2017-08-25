#include <iostream>
using namespace std;

#include "shape.h"
#include "circle.h"
#include "square.h"
#include "triangle.h"

int main(){
	Shape *p=NULL;
	Circle circle(3);
	Square square(3);
	Triangle tri(3,4,5);
	p=&circle;
	p->info();
	p=&square;
	p->info();
	p=&tri;
	p->info();
	system("pause");
	return 0;
}