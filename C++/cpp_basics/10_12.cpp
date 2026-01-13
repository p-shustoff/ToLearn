#include <stdio.h>

class Prism {
	double height;
public:
	Prism(double h) : height(h) {}
	virtual double Square() const = 0;
	double Volume() const { return height * Square(); }

};

class Box : public Prism {
	double edge;
public:
	Box(double h, double e) : Prism(h), edge(e) {}
	virtual double Square() const { return edge*edge; }
};

class Cube : public Box {
	double edge;
public:
	Cube(double e) : Box(e, e), edge(e) {}
};

int main() {
	const Prism *p, *q, *r;
	Box a(0.5, 2), b(5, 0.2);
	Cube c(0.5);
	p = &a; q = &b; r = &c;
	printf("Squares: %3.3lf %3.3lf %3.3lf\n", p->Square(), q->Square(), r->Square());
	printf("Volumes: %3.3lf %3.3lf %3.3lf\n", p->Volume(), q->Volume(), r->Volume());
	return 0;
}
