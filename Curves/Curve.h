#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>



	class Point3D
	{
	public:

		double x;
		double y;
		double z;

		Point3D() : x(0), y(0), z(0) {}
		Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

	};


	class Curve {

	public:

		virtual Point3D getPoint(double t) const = 0;
		virtual Point3D getDerivative(double t) const = 0;
		virtual ~Curve() = default;

	};


	class Circle :public Curve {

		double radius;

	public:
		Circle() :radius(1.) {}
		Circle(double R);
		Point3D getPoint(double t) const;
		Point3D getDerivative(double t) const;
		double getRadius() const;
	};

	class Ellipse :public Curve {

		double radiusA;
		double radiusB;

	public:
		Ellipse() :radiusA(1), radiusB(1) {}
		Ellipse(double a, double b);
		Point3D getPoint(double t) const;
		Point3D getDerivative(double t) const;
	};

	class Helix :public Curve {

		double radius;
		double step;

	public:
		Helix() :radius(1), step(1) {}
		Helix(double R, double H);
		Point3D getPoint(double t) const;
		Point3D getDerivative(double t) const;
		double getRadius() const;
		double getStep() const;
	};


	class CurveGenerator {
	public:
		virtual std::shared_ptr<Curve> GenerateRandomCurve() = 0;
		virtual ~CurveGenerator() = default;
	};


	class BasicCurveGenerator : public CurveGenerator {

	public:
		virtual std::shared_ptr<Curve> GenerateRandomCurve();
		virtual ~BasicCurveGenerator() = default;
	};

