#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <iostream>
#include <fstream>
#include <float.h>
#include "Util.h"
#include "SETTINGS.h"

vector<VEC2> particleSources;
vector<float> particleMasses;

vector<VEC2> magnets;
vector<float> magnetMasses;

float velocity = 2.f;
float g_const = -100.f;
int thetaSteps = 100;
int simSteps = 100;
float step_dt = 5;

// Screen bounds
VEC2 screenMin = {0.f, 0.f};
VEC2 screenMax = {1920.f, 1080.f};

float circleRadius = 2.f;
vector<VEC2> circles;


void buildScene(float t){
	particleSources.clear();
	particleMasses.clear();
	magnets.clear();
	magnetMasses.clear();

	// Particle Sources
	particleSources.push_back({960.f, 540.f});
	particleMasses.push_back(-1);

	// Magnets
	magnets.push_back(lerpVec({0.f, 540.f}, {660.f, 540.f}, (float)t/3000.f));
	magnetMasses.push_back(50.f);

	magnets.push_back(lerpVec({1920.f, 540.f}, {1260.f, 540.f}, (float)t/3000.f));
	magnetMasses.push_back(50.f);
}

void genCircles(){
	circles.clear();
	for(int i = 0; i < particleSources.size(); i++){
		float charge = particleMasses[i];
		// For each particle source
		for(int j = 0; j < thetaSteps; j++){
			// For each angle
			float angle = 2.f*PI*((float)j/thetaSteps);
			VEC2 v = {velocity*cos(angle), velocity*sin(angle)};
			VEC2 p = particleSources[i];

			for(int step_num = 0; step_num < simSteps; step_num++){
				// For each simulation step
				VEC2 force = {0.f, 0.f};

				for(int mag_num = 0; mag_num < magnets.size(); mag_num++){
					// Calculate all forces from all magnets
					VEC2 magnet = magnets[mag_num];
					float magnet_mass = magnetMasses[mag_num];
					float dist = (p-magnet).norm();

					VEC2 this_force = (magnet-p).normalized();
					this_force = this_force * g_const * magnet_mass * charge / pow(dist, 2);
					force += this_force;
				}

				if((p[0] < screenMin[0]) || (p[1] < screenMin[1]) || (p[0] > screenMax[0]) || (p[1] > screenMax[1])){
					// Break maybe (Just ingorign it for now)	
				}

				p = p + v*step_dt + force*pow(step_dt,2)/2.f;
				v = v + step_dt*force;
				circles.push_back(p);
			}
		}
	}
}

float * rasterize(int xRes, int yRes){
	float * pixels = new float[3*xRes*yRes];

	float v_res = screenMax[0] - screenMin[0];
	float u_res = screenMax[1] - screenMin[1];

	for(int y = 0; y < yRes; y++){
		for(int x = 0; x < xRes; x++){
			float v = v_res*(float)x/xRes;
			float u = u_res*(float)y/yRes;

			VEC2 look = {v, u};
			VEC3 color = {0.f, 0.f, 0.f};
			for(int i = 0; i < circles.size(); i++){
				float dist = (look - circles[i]).norm();
				if(dist < circleRadius){
					color = {1.f, 1.f, 1.f};
					break;
				}
			}	

			int index = 3*((y*xRes) + x);
			pixels[index + 0] = color[0]*255.f;
			pixels[index + 1] = color[1]*255.f;
			pixels[index + 2] = color[2]*255.f;
		}
	}

	return pixels;
}


int main(int argc, char ** argv){
	int startFrame, endFrame;
	if(argc == 1){
		startFrame = 0;
		endFrame = 1;
	}else if(argc == 2){
		startFrame = atoi(argv[1]);
		endFrame = 300;
	}else{
		startFrame = atoi(argv[1]);
		endFrame = atoi(argv[2]);
	}

	int xRes = 1920;
	int yRes = 1080;

	for(int frame_num = startFrame; frame_num < endFrame; frame_num++){
		buildScene(frame_num);
		genCircles();
		float * pixels = rasterize(xRes, yRes);
		char buffer[256];
	  sprintf(buffer, "./oven/frame.%04i.ppm", frame_num);
		writePPM(buffer, xRes, yRes, pixels);
		cout << "Rendered frame " << frame_num << endl;
	}
	
}