#include <stdio.h>
#include <math.h>

class Body {
	double dens;
public:
	Body(double d) : dens(d) {};
	virtual double Volume() const = 0;
	double Mass() const { return dens * Volume(); }
};

class Cube : public Body {
	double edge;
public:
	Cube(double e, double d) : Body(d), edge(e) {}
	virtual double Volume() const { return pow(edge, 3); }
};

class Tetrahedron : public Body {
	double edge;
public:
	Tetrahedron(double e, double d) : Body(d), edge(e) {}
	virtual double Volume() const { return M_SQRT2 / 12 * pow(edge, 3); }
};


int main() {
	const Body *p, *q, *r;
	Cube a(2,10), b(5, 0.1);
	Tetrahedron t(6, 2.5);
	p = &a; q = &b, r = &t;
	printf("Volumes: %3.3lf %3.3lf %3.3lf\n", p->Volume(), q->Volume(), r->Volume());
	printf("Weights: %3.3lf %3.3lf %3.3lf\n", p->Mass(), q->Mass(), r->Mass());
	return 0;
}
