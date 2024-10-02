#pragma once
#include <iostream>
class Job{
public: 
	float wallet = 0;
	float wage = 0;
	int experience = 0;
	int level = 0;
	int tier = 0;
	float accChance = 0;
	bool accepted = false;
	bool hasJob = false;


	void Search();			// search for job
	void Apply();			// apply for job
	void StartJob();		// start job
	void Wage(float bonus); // amount paid
	void Quit();			// quit job

};

