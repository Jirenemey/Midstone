#include "Job.h"

void Job::Search() {
	// randomly sets tier and wage of job while searching
	if (hasJob == false) {
		int x = rand() % 100 + 1;
		if (experience < 10) {
			if (x <= 50)
				tier = 1;
			else if (x > 50 && x <= 75)
				tier = 2;
			else if (x > 75 && x <= 90)
				tier = 3;
			else if (x > 90 && x <= 99)
				tier = 4;
			else
				tier = 5;
			wage = rand() % 10 + 16 * (tier * experience + 1);
		}
		else if (experience < 30){
			if (x <= 20)
				tier = 1;
			else if (x > 20 && x <= 55)
				tier = 2;
			else if (x > 55 && x <= 80)
				tier = 3;
			else if (x > 80 && x <= 95)
				tier = 4;
			else
				tier = 5;
			wage = rand() % 20 + 30 * (tier * experience + 1);
		}
		else if(experience < 50){
			if (x <= 15)
				tier = 1;
			else if (x > 15 && x <= 40)
				tier = 2;
			else if (x > 40 && x <= 70)
				tier = 3;
			else if (x > 70 && x <= 90)
				tier = 4;
			else
				tier = 5;
			wage = rand() % 35 + 52 * (tier * experience + 1);
		}
		else if (experience < 70) {
			if (x <= 10)
				tier = 1;
			else if (x > 10 && x <= 30)
				tier = 2;
			else if (x > 30 && x <= 50)
				tier = 3;
			else if (x > 50 && x <= 80)
				tier = 4;
			else
				tier = 5;
			wage = rand() % 53 + 82 * (tier * experience + 1);
		}
		else if(experience < 100) {
			if (x <= 5)
				tier = 1;
			else if (x > 5 && x <= 15)
				tier = 2;
			else if (x > 15 && x <= 30)
				tier = 3;
			else if (x > 30 && x <= 70)
				tier = 4;
			else
				tier = 5;
			wage = rand() % 74 + 120 * (tier * experience + 1);
		}
		else {
			if (x <= 2)
				tier = 1;
			else if (x > 2 && x <= 10)
				tier = 2;
			else if (x > 10 && x <= 20)
				tier = 3;
			else if (x > 20 && x <= 35)
				tier = 4;
			else
				tier = 5;
			wage = rand() % 100 + 166 * (tier * experience + 1);
		}
		std::cout << "Tier: " << tier << std::endl;
		std::cout << "Wage: " << wage << std::endl;
		applied = false;
	}
	else {
		std::cout << "Player already has job." << std::endl;
	}
}

void Job::Apply() {
	// randomly lets player have job based on experience
	if (applied == false) {
		accChance = 1000 / tier + experience; // set base value to 10 (100 for testing purposes)
		if (rand() % 100 + 1 < accChance && !hasJob) {
			accepted = true;
			hasJob = true;
			std::cout << "Accepted" << std::endl;
		}
		else {
			std::cout << "Job not accepted." << std::endl;
			accepted = false;
		}
		applied = true;
	}
	else {
		std::cout << "Already applied." << std::endl;
	}
}

void Job::Wage(float performance) {
	wallet += wage * performance; 
	std::cout << "Wage: " << wage << "\nPerformance Multi: " << performance << "\nWallet: " << wallet << std::endl;
}

void Job::Quit() {
	hasJob = false;
}