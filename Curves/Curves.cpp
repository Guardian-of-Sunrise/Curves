#define _USE_MATH_DEFINES
#include <iostream>
#include "Curve.h"
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <omp.h> 

std::vector<std::shared_ptr<Curve>> genRandCircleVec(int size) {
	std::vector<std::shared_ptr<Curve>> rezult;
	BasicCurveGenerator gen;
	for (int i = 0; i < size; i++) {
		rezult.push_back(gen.GenerateRandomCurve());
	}
	return rezult;
}


int main()
{
	
	std::vector<std::shared_ptr<Curve>> curves = genRandCircleVec(10);
	double t = M_PI / 4;
	for (auto i : curves) {
		std::cout << i->getPoint(t).x << " " << i->getPoint(t).y << " " << i->getPoint(t).z<<std::endl;
		std::cout<< "Der " << i->getDerivative(t).x << " " << i->getDerivative(t).y << " " << i->getDerivative(t).z << std::endl;
		std::cout << std::endl;
	}
	
	std::vector<std::shared_ptr<Circle>> onlyCircles;
	for (auto i : curves) {
		auto cast = std::dynamic_pointer_cast<Circle>(i);
		if (cast) {
			onlyCircles.push_back(cast);
		}
	}

	std::sort(onlyCircles.begin(), onlyCircles.end(), [](std::shared_ptr<Circle> a, std::shared_ptr<Circle> b) {return a->getRadius() < b->getRadius();});

	for (auto i : onlyCircles) {
		std::cout << "Radis = " << i->getRadius()<<std::endl;
	}

	double sum = 0.;
	#pragma omp parallel for reduction(+:sum)
	for (auto i: onlyCircles) {
		sum +=i->getRadius();
	}

	std::cout << "Summ = " << sum;

}
