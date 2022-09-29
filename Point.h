#include <math.h>

class Point {
public:
	Point() {
		p[0] = 0;
		p[1] = 0;
		p[2] = 0;
		p[3] = 1;
	};

	Point(double x, double y, double z) {
		p[0] = x;
		p[1] = y;
		p[2] = z;
		p[3] = 1;
	};

	Point(const Point& v) {
		p[0] = v[0];
		p[1] = v[1];
		p[2] = v[2];
		p[3] = 1;
	};

	~Point() {};

	void normalize() {
		double l = sqrt((p[0] * p[0]) + (p[1] * p[1]) + (p[2] * p[2]));
		p[0] = p[0] / l;
		p[1] = p[1] / l;
		p[2] = p[2] / l;
		p[3] = 1;
	};

	Point& operator= (const Point v) {
		p[0] = v[0];
		p[1] = v[1];
		p[2] = v[2];
		p[3] = 1;
		return *this;
	};

	double at(int i) const {
		return p[i];
	}

	double& at(int i) {
		return p[i];
	}

	double operator[] (int i) const {
		return p[i];
	};

	double& operator[] (int i) {
		return p[i];
	}

	void unpack(double* d) {
		d[0] = p[0];
		d[1] = p[1];
		d[2] = p[2];
		d[3] = p[3];
	};

	double* unpack() {
		return p;
	}

	void init() {
		p[0] = 0;
		p[1] = 0;
		p[2] = 0;
		p[3] = 1;
	}

private:
	double p[4];
};
