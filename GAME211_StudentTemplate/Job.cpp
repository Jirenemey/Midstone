#include "Job.h"

void Job::Search() {
	// randomly sets tier and wage of job while searching based on percentage
	if (hasJob == false) {
		int x = rand() % 100 + 1;
		if (experience < 10) {			// less than 10 experience
			if (x <= 50)				// 50% for tier 1
				tier = 1;
			else if (x > 50 && x <= 75) // 25% for tier 2
				tier = 2;
			else if (x > 75 && x <= 90) // 15% for tier 3
				tier = 3;
			else						// 10% for tier 4
				tier = 4;

			wage = rand() % 10 + 16 * (tier * experience + 1);
		}
		else if (experience < 30){		// less than 30 experience
			if (x <= 20)				// 30% for tier 1
				tier = 1;
			else if (x > 20 && x <= 55) // 35% for tier 2
				tier = 2;
			else if (x > 55 && x <= 80) // 25% for tier 3
				tier = 3;
			else						// 20% for tier 4
				tier = 4;
			wage = rand() % 20 + 30 * (tier * experience + 1);
		}
		else if(experience < 50){		// less than 50 experience
			if (x <= 15)				// 15% for tier 1
				tier = 1;
			else if (x > 15 && x <= 40) // 25% for tier 2
				tier = 2;
			else if (x > 40 && x <= 70) // 30% for tier 3
				tier = 3;
			else						// 30% for tier 4
				tier = 4;
			wage = rand() % 35 + 52 * (tier * experience + 1);
		}
		else if (experience < 70) {		// experience less than 70
			if (x <= 10)				// 10% for tier1
				tier = 1;
			else if (x > 10 && x <= 30) // 20% for tier2
				tier = 2;
			else if (x > 30 && x <= 70) // 40% for tier 3
				tier = 3;
			else						// 30% for tier4
				tier = 4;
			wage = rand() % 53 + 82 * (tier * experience + 1);
		}
		else if(experience < 100) {		// experience less than 100
			if (x <= 5)					// 5% for tier1
				tier = 1;
			else if (x > 5 && x <= 25) //20% for tier2
				tier = 2;
			else if (x > 25 && x <= 60) // 35% for tier3
				tier = 3;
			else						//40% for tier4
				tier = 4;
			wage = rand() % 74 + 120 * (tier * experience + 1);
		}
		else {
			if (x <= 5)					// 5% for tier1
				tier = 1;
			else if (x > 5 && x <= 20) // 15% for tier2
				tier = 2;
			else if (x > 20 && x <= 45) // 25% for tier3
				tier = 3;
			else						// 55% for tier4
				tier = 4;
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
		accChance = 1000 / tier + experience; // 1000 for testing purposes - real formula: (10 + (jobAccChanceLevel * 3)) / (tier - (experience/100));
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
	if (performance < 0) // if you do very terribly and go negative you dont lose money but get paid 0
		performance = 0;
	wallet += wage * pow(1.1, wageUpgradeLevel) * performance; 
	std::cout << "Wage: " << wage << "\nPerformance Multi: " << performance << "\nWallet: " << wallet << std::endl;
}

void Job::Quit() {
	hasJob = false;
}

void Job::UpgradeJobAcc() {
	jobAccChancePrice = pow(jobAccChanceLevel, 4.7) * 25; // formula for price calculation
	int maxLevel = 10;
	if (wallet >= jobAccChancePrice && jobAccChanceLevel < maxLevel) {
		jobAccChanceLevel++;
		wallet -= jobAccChancePrice;
		std::cout << "Hire Chance Upgrade Level: " << experienceLevel << std::endl;
	}
	else {
		std::cout << "Insufficient funds for HIRE CHANCE UPGRADE." << std::endl;
		std::cout << "Current cost: " << jobAccChancePrice << std::endl;
	}
}

void Job::UpgradeWage() {
	wageUpgradePrice = pow(wageUpgradeLevel, 3.1) * 70; // formula for price calculation
	int maxLevel = 25;
	if (wallet >= wageUpgradePrice && wageUpgradeLevel < maxLevel) {
		wageUpgradeLevel++;
		wallet -= wageUpgradePrice;
		std::cout << "Wage Upgrade Level: " << experienceLevel << std::endl;
	}
	else {
		std::cout << "Insufficient funds for WAGE UPGRADE." << std::endl;
		std::cout << "Current cost: " << wageUpgradePrice << std::endl;
	}
}

void Job::UpgradeExperience() {
	experiencePrice = pow(experienceLevel, 4.2) * 40; // formula for price calculation
	int maxLevel = 20;
	if (wallet >= experiencePrice && experienceLevel < maxLevel) {
		experienceLevel++;
		wallet -= experiencePrice;
		std::cout << "Experience Upgrade Level: " << experienceLevel << std::endl;
	}
	else {
		std::cout << "Insufficient funds for EXP UPGRADE." << std::endl;
		std::cout << "Current cost: " << experiencePrice << std::endl;
	}
}