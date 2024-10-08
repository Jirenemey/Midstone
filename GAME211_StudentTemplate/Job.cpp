#include "Job.h"

void Job::Search() {
	// randomly sets tier and wage of job while searching
	if (hasJob == false) {
		switch (experience) {
		case 0:
			tier = rand() % 5 + 1;
			wage = rand() % 10 + 16 * (tier * experience);
			break;
		case 10:
			tier = rand() % 4 + 2;
			wage = rand() % 20 + 30 * (tier * experience);
			break;
		case 30:
			tier = rand() % 3 + 3;
			wage = rand() % 35 + 52 * (tier * experience);
			break;
		case 50:
			tier = rand() % 2 + 4;
			wage = rand() % 53 + 82 * (tier * experience);
			break;
		case 70:
			tier = rand() % 1 + 5;
			wage = rand() % 74 + 120 * (tier * experience);
			break;
		case 100:
			tier = 5;
			wage = rand() % 100 + 166 * (tier * experience);
			break;
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
		accChance = 10 / tier + experience;
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

void Job::StartJob() {

}

void Job::Wage(float performance) {
	wallet += wage * performance; 
}

void Job::Quit() {
	hasJob = false;
}