#pragma once
#include <iostream>
class Job{
public: 
	float wallet = 0;
	float wage = 0;
	float experience = 0;
	int level = 0;
	int tier = 1;
	float accChance = 0;
	bool accepted = false;
	bool hasJob = false;
	bool applied = true;
	bool startJob = false;

	int wageUpgradeLevel = 0;
	int jobAccChanceLevel = 0;
	int experienceLevel = 0;

	void Search();				// search for job
	void Apply();				// apply for job
	void Wage(float bonus);		// amount paid
	void Quit();				// quit job
	void UpgradeJobAcc();		// job acceptance chance upgrade
	void UpgradeWage();			// wage multiplier upgrade
	void UpgradeExperience();	// experience gain increase upgrade

};

