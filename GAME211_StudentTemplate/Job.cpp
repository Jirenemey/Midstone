#include "Job.h"

void Job::Search() {
	// randomly sets tier and wage of job while searching
	if (hasJob == false) {
		switch (experience) {
		case 0:
			tier = rand() % 5 + 1;
			wage = rand() % 10 + 16 * tier * experience;
		case 10:
			tier = rand() % 4 + 2;
			wage = rand() % 20 + 30 * tier * experience;
		case 30:
			tier = rand() % 3 + 3;
			wage = rand() % 35 + 52 * tier * experience;
		case 50:
			tier = rand() % 2 + 4;
			wage = rand() % 53 + 82 * tier * experience;
		case 70:
			tier = rand() % 1 + 5;
			wage = rand() % 74 + 120 * tier * experience;
		case 100:
			tier = 5;
			wage = rand() % 100 + 166 * tier * experience;
		}
	}
	else {
		std::cout << "Player already has job." << std::endl;
	}
}

void Job::Apply() {
	// randomly lets player have job based on experience
	accChance = 10 / tier + experience;
	if (rand() % 100 + 1 < accChance && !hasJob) {
		accepted = true;
		hasJob = true;
	}
	else {
		std::cout << "Job not accepted." << std::endl;
		accepted = false;
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