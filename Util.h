#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include "SETTINGS.h"
using namespace std;

const float PI = 3.1415926535;

void writePPM(const string& filename, int& xRes, int& yRes, const float* values);
void readPPM(const string& filename, int& xRes, int& yRes, float*& values);
void hadamard(VEC3 a, VEC3 b);
float clamp(float value);
float exerpFloat(float start, float end, float t);
float lerpFloat(float start, float end, float t);
VEC2 lerpVec(VEC2 start, VEC2 end, float t);
VEC2 smerpVec(VEC2 start, VEC2 end, float t);
float smerpFloat(float start, float end, float t);
float keyframeFloat(vector<float> keyframes, vector<float> values, vector<int> interpolation, float t);
VEC2 keyframeVec(vector<float> keyframes, vector<VEC2> values, vector<int> interpolation, float t);
float min(float a, float b);
float max(float a, float b);
float area(VEC2 v0, VEC2 v1);
VEC3 extend(VEC2 in);
VEC2 truncate(VEC3 in);
VEC2 translate(VEC2 in, VEC2 trans);
VEC2 rotate(VEC2 in, float rot, VEC2 anchor);
VEC2 scale(VEC2 in, VEC2 scale);
VEC2 v2_animate(Anim_v2 anim, float t_in);
float f_animate(Anim_f anim, float t_in);
Image newImage(char * filename_in);

#endif