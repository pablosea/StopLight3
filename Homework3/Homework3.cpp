// Homework3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int NUM_OF_LIGHTS = 4;

time_t startTime = time(0);

enum direction {
	north = 0 , south = 1 , east = 2 , west = 3
};

class StopLight {

public:
	StopLight(direction direction) {
		this->lightColor = "";
		this->direction = direction;
	}

	StopLight(string color , direction direction) {
		this->lightColor = color;
		this->direction = direction;
	}

	StopLight(string color , direction direction , StopLight *nextLight) {
		this->lightColor = color;
		this->direction = direction;
		this->nextLight = nextLight;
	}

	string getLightColor() {
		return this->lightColor;
	}

	void setLightColor(string c) {
		this->lightColor = c;
	}

	direction getDirection() {
		return this->direction;
	}

	void setNextLight(StopLight	*nextLight) {
		this->nextLight = nextLight;
	}

	void cycleLights() {
		this->lightColor = this->lightColor == "red" ? "green" : "red";
		
		/*switch(this->direction) {
		case north:
		case south:
			this->lightColor = this->lightColor == "red" ? "green" : "red";
			break;
		case east:
		case west:
			this->lightColor = this->lightColor == "red" ? "green" : "red";
			break;
		}*/

		if(this->nextLight != NULL) {
			this->nextLight->cycleLights();
		}
	}

	static void emergencyChange(direction dir , StopLight (&lights)[NUM_OF_LIGHTS]) {
		for(int i = 0; i < NUM_OF_LIGHTS; i++) {
			if(lights[i].direction == dir) 
				lights[i].setLightColor("green");
			else 
				lights[i].setLightColor("red");
		}
	}

	static void resetLights(StopLight (&lights)[NUM_OF_LIGHTS]) {
		for(int i = 0 ; i < NUM_OF_LIGHTS ; i++) {
			switch(lights[i].direction) {
			case north:
			case south:
				lights[i].setLightColor("green");
				break;
			case east:
			case west:
				lights[i].setLightColor("red");
				break;
			default:
				break;
			}
		}
	}

	void printLightColor() {
		cout << this->lightColor;
	}
private:
	string lightColor;
	StopLight *nextLight;
	direction direction;
};

int _tmain(int argc , _TCHAR* argv []) {
	StopLight lights [] = {
		StopLight("green" , direction::north , &lights[1]) ,
		StopLight("green" , direction::south , &lights[2]) ,
		StopLight("red" , direction::west , &lights[3]) ,
		StopLight("red" , direction::east , NULL)
	};

	lights[0].cycleLights();

	StopLight::emergencyChange(direction::north , lights);
	//StopLight::resetLights(lights);

	for each (auto var in lights) {
		cout << var.getDirection() << ": ";
		var.printLightColor();
		cout << endl;
	}

	return 0;
}

