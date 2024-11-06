#pragma once
#include <iostream>
class Job{
public: 
	float wallet = 0;
	float wage = 0;
	int experience = 0;
	int level = 0;
	int tier = 1;
	float accChance = 0;
	bool accepted = false;
	bool hasJob = false;
	bool applied = false;
	bool startJob = false;

	int wageUpgrade = 1;
	int jobAccChance = 1;

	void Search();			// search for job
	void Apply();			// apply for job
	void Wage(float bonus); // amount paid
	void Quit();			// quit job

};

