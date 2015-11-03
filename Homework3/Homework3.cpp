// Homework3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

time_t startTime = time(0);

class StopLight {

public:
	StopLight(string direction) {
		this->lightColor = "";
		this->direction = direction;
	}

	StopLight(string color , string direction) {
		this->lightColor = color;
		this->direction = direction;
	}

	string getLightColor() {
		return this->lightColor;
	}

	void setLightColor(string c) {
		this->lightColor = c;
	}

	string getDirection() {
		return this->direction;
	}

	void setNextLight(StopLight	*nextLight) {
		this->nextLight = nextLight;
	}

	void cycleLights() {

		if(this->nextLight != NULL) {
			this->nextLight->lightColor = "green";
			this->nextLight->cycleLights();
		}		
	}
private:
	string lightColor;
	StopLight *nextLight;
	string direction;
};

int _tmain(int argc, _TCHAR* argv[])
{
	StopLight north("red");
	StopLight south("red");
	StopLight east("red");
	StopLight west("red");

	north.setNextLight(&south);
	south.setNextLight(&west);
	west.setNextLight(&east);
	east.setNextLight(NULL);

	north.cycleLights();

	cout << north.getLightColor() << endl;
	cout << south.getLightColor() << endl;
	cout << east.getLightColor() << endl;
	cout << west.getLightColor() << endl;

	return 0;
}

