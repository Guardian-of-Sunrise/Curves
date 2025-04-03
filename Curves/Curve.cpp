#include "Curve.h"
#include <random>




Circle::Circle(double R) {
	if (R < 0) {
		throw std::invalid_argument("Radius cannot be negative.");
	}
	radius = R;
}

Point3D Circle::getPoint(double t) const {
	return Point3D(radius * cos(t), radius * sin(t), 0);
}
Point3D Circle::getDerivative(double t) const {
	return Point3D(-radius * sin(t), radius * cos(t), 0);
}
double Circle::getRadius() const {
	return radius;
}



Ellipse::Ellipse(double a, double b) {
	if (a < 0 || b < 0) {
		throw std::invalid_argument("Radius cannot be negative.");
	}
	radiusA = a;
	radiusB = b;
}

Point3D Ellipse::getPoint(double t) const {
	return Point3D(radiusA * cos(t), radiusB * sin(t), 0);
}
Point3D Ellipse::getDerivative(double t) const {
	return Point3D(-radiusA * sin(t), radiusB * cos(t), 0);
}


Helix::Helix(double R, double H) {
	if (R < 0) {
		throw std::invalid_argument("Radius cannot be negative.");
	}
	radius = R;
	step = H;
}

Point3D Helix::getPoint(double t) const {
	return Point3D(radius * cos(t), radius * sin(t), step * t / (2 * M_PI));
}
Point3D Helix::getDerivative(double t) const {
	return Point3D(-radius * sin(t), radius * cos(t), step / (2 * M_PI));
}
double Helix::getRadius() const {
	return radius;
}

double Helix::getStep() const {
	return step;
}


std::shared_ptr<Curve> BasicCurveGenerator::GenerateRandomCurve() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> typeDist(0, 2);
	int rand = typeDist(gen);
	static std::uniform_real_distribution<> radiusDist(0.1, 20.0);

	switch (rand)
	{
	case 0:
	{
		double radius = radiusDist(gen);
		return std::make_shared<Circle>(Circle(radius));
	}
	case 1:
	{
		double radiusA = radiusDist(gen);
		double radiusB = radiusDist(gen);
		return std::make_shared<Ellipse>(Ellipse(radiusA, radiusB));
	}
	case 2:
	{
		static std::uniform_real_distribution<> stepDist(0.1, 5.0);
		double radius = radiusDist(gen);
		double step = stepDist(gen);
		return std::make_shared<Helix>(Helix(radius, step));
	}
	}
}