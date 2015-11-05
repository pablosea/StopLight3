// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

double currentTime = time(0);

int getRunTimeInSeconds() {
	return (int) time(0) - currentTime - 1;
}

enum direction {
	north , south , east , west
};

enum color {
	green , yellow , red
};

class stopLight {
public:
	int counter;

	stopLight(direction d , color c , stopLight *light) {
		this->direction = d;
		this->lightColor = c;
		this->prevLight = light;
		this->counter = 20;
	}

	void setlightColor(color c) {
		this->lightColor = c;
	}

	color getLightColor() {
		return this->lightColor;
	}

	direction getDirection() {
		return this->direction;
	}

	// working cycle funcion
	void cycle() {
		this->changed = false;

		if(this->counter == 9) {
			this->lightColor = yellow;
			this->changed = true;
		}
		else if(this->counter == 12) {
			this->lightColor = red;
			this->changed = true;
		}

		switch(this->direction) {
		case north:
		case east:
			this->change(12);
			break;
		case south:
		case west:
			this->change(6);
			break;
		}
	}

	void change(int num) {
		if(this->prevLight->counter == num) {
			this->goGreen();
		}
	}

	void goGreen() {
		this->counter = 0;
		this->lightColor = green;
		changed = true;
	}
	
	string getStrColor() {
		switch(this->lightColor) {
		case green:		return "Green ";
		case yellow:	return "Yellow";
		case red:		return "Red   ";
		}
	}

	bool getChanged() {
		return changed;
	}

	int getCounter() {
		return counter;
	}

private:
	bool changed;
	direction direction;
	color lightColor;
	stopLight *prevLight;
};

stopLight lights [] = {
	stopLight(north , red , &lights[3]) ,
	stopLight(south , red , &lights[0]) ,
	stopLight(east , red , &lights[1]) ,
	stopLight(west , red , &lights[2])
};

void printLights() {
	cout << "    " << getRunTimeInSeconds();
	for(int i = 0; i < 4; i++) {
		cout << "\t\t" << lights[i].getStrColor();
	}
	cout << endl;
}

int main() {
	int prior = getRunTimeInSeconds();

	lights[0].goGreen();
	lights[0].counter--;

	cout << "Time\tNorth\tSouth\tEast\tWest" << endl;
	cout << "-------------------------------------------------------------" << endl;

	bool display = true;

	while(getRunTimeInSeconds() <= 60) {
		if(getRunTimeInSeconds() > prior) {		

			for(int i = 0; i < 4; i++) {
				lights[i].counter++;
			}
			

			for(int i = 0; i < 4; i++) {
				lights[i].cycle();

				if(lights[i].getChanged())
					display = true;
			}

			if(display) {
				printLights();
			}
			
			display = false;
			prior = getRunTimeInSeconds();
		}
	}

	system("pause");

	return 0;
}