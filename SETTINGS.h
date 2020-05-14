#ifndef SETTINGS_H
#define SETTINGS_H

#include <cassert>

#define USING_OSX 1

#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "Eigen/Geometry"

#include <functional> 
using namespace Eigen;
using namespace std;

#define Real double

typedef Matrix<Real, 2, 2 > MATRIX2;
typedef Matrix<Real, 3, 3 > MATRIX3;
typedef Matrix<Real, 4, 4 > MATRIX4;
typedef Matrix<Real, 6, 6 > MATRIX6;
typedef Matrix<Real, 2, 1 > VEC2;
typedef Matrix<Real, 3, 1 > VEC3;
typedef Matrix<Real, 4, 1 > VEC4;
typedef Matrix<int, 3, 1 > VEC3I;

typedef Matrix<Real, Dynamic, Dynamic> MATRIX;
typedef Matrix<Real, Dynamic, 1> VECTOR;
typedef Eigen::SparseMatrix<Real> SPARSE_MATRIX;
typedef Eigen::Triplet<Real> TRIPLET;


typedef struct Anim_f{
	vector<float> keys;
	vector<float> vals_f;
	vector<function<float(float)>> interps; // Lambda functions
}Anim_f;

typedef struct Anim_v2{
	vector<float> keys;
	vector<VEC2> vals_v2;
	vector<function<float(float)>> interps; // Lambda functions
}Anim_v2;

typedef struct Image{
	char * filename;
	float * pixels;
	int xRes;
	int yRes;
}Image;

typedef struct Fill{
	int type; //0 = solid color, 1 = Image, 2 = gradient (You would put stroke and text in here too probably maybe idk)
	VEC3 color;
	Image img;
}Fill;

typedef struct Stroke{

}Stroke;

auto lerp = [](float t){
	return t;
};

auto serp = [](float t){
	return 3*pow(t,2) - 2*pow(t,3);
};

#ifndef NDEBUG
#define NDEBUG
#endif

#endif
