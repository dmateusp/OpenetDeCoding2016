// compile with: g++ --std=c++11 Main.cpp -o Main

// Daniel Mateus Pires
// Student, 3rd year Computer Science

/* This is my solution for 
* De/Coding 2016 OPENET */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Group.h"
class Values{

private:
 std::vector<std::string> m_values;
 const std::string m_filename;
 std::vector<Group> groups;
 Group knockOut = Group("Knock out phase");

public:
	Values(const std::string filename) : m_filename(filename){
		// Groups creation
		Team albania, france, hungary, iceland, repireland, ukraine;
		albania.name = "Albania";
		france.name = "France";
		hungary.name = "Hungary";
		iceland.name = "Iceland";
		repireland.name = "Republic of Ireland";
		ukraine.name = "Ukraine";
		groups.push_back(Group("A", france));
		groups.push_back(Group("B", repireland));
		groups.push_back(Group("C", ukraine));
		groups.push_back(Group("D", albania));
		groups.push_back(Group("E", hungary));
		groups.push_back(Group("F", iceland));
 }
 void populateValues(){
  std::ifstream in_stream(m_filename);

  for(std::string line; getline(in_stream, line, ','); ){ // This splits every line using the ',' token
	  if (line.find('\n') != std::string::npos) {
		  m_values.push_back(line.substr(0, line.find('\n'))); // Here we get rid of new line character
		  m_values.push_back(line.substr(line.find('\n')+1, line.size()));
	  }
	  else {
		  m_values.push_back(line);
	  }
  }
 }

 void printValues(){
for(auto i = m_values.begin(); i != m_values.end(); ++i){
	std::cout << *i << std::endl;
  }
 }
// Reads the vector m_values and creates the Groups
void populateGroups() {
	int count = 0;
	Team opponentTeam, thisTeam;
	for (auto i = m_values.begin(); i != m_values.end(); ++i) {
		count++;
		if (count == 1) { // First team
			opponentTeam.name = *i;
		}
		else if (count == 2) { // Goals scored by first team
			opponentTeam.goals = atoi((*i).c_str());
		}
		else if (count == 3) { // Goals scored by second team
			thisTeam.goals = atoi((*i).c_str());
			if (opponentTeam.goals > thisTeam.goals)
				opponentTeam.points += 3;
			else if (thisTeam.goals > opponentTeam.goals)
				thisTeam.points += 3;
			else {
				opponentTeam.points += 1;
				thisTeam.points += 1;
			}
			// Goals difference
			int tempGoals = opponentTeam.goals;
			opponentTeam.goals -= thisTeam.goals;
			thisTeam.goals -= tempGoals;
		}
		else if (count == 4) { // Second team
			bool found = false;
			thisTeam.name = *i;
			for (auto j = groups.begin(); j != groups.end(); ++j) {
				/* We look for a group in which one of the teams is.
				* if one of the team is found we add the other team
				* to the group and we add the points (3 for Win, 1 Draw).*/
				bool inGroupOpponent = j->isInGroup(opponentTeam.name);
				bool inGroupThisTeam = j->isInGroup(*i);
				if (inGroupOpponent || inGroupThisTeam) {
					if (!inGroupOpponent) {
						j->push_back(opponentTeam); // Add the other team to the group
						j->update(thisTeam);
					}
					if (!inGroupThisTeam) {
						j->push_back(thisTeam); // Add the other team to the group
						j->update(opponentTeam);
					}
					if (inGroupOpponent && inGroupThisTeam) {
						j->update(thisTeam);
						j->update(opponentTeam);
					}
					found = true;
					break;
				}
			}
			count = 0;
			/*If no team is found we add both teams
			* to an empty group.*/
			if (!found) {
				for (auto j = groups.begin(); j != groups.end(); ++j) {
					if (j->list().empty()) {
						j->push_back(thisTeam);
						j->push_back(opponentTeam);
						break;
					}
				}
			}
			opponentTeam.points = 0, thisTeam.points = 0;
		}
	}
}
void printGroups() {
	for (auto i = groups.begin(); i != groups.end(); i++) {
		i->print();
	}
}
void sortGroups() {
	for (auto i = groups.begin(); i != groups.end(); i++) {
		i->sort();
	}
}
void knockOutPhase() {
	Group bestThirdPlaced = Group("Temporary");
	for (auto i = groups.begin(); i != groups.end(); i++) {
		/*
		Adding the 2 best teams of each group
		and the third team to a temporary group
		*/
		knockOut.push_back(i->getTeam(0));
		knockOut.push_back(i->getTeam(1));
		bestThirdPlaced.push_back(i->getTeam(2));
	}
	/*
	The 4 best teams of the temporary group
	are added to the knockout group
	*/
	bestThirdPlaced.sort();
	knockOut.push_back(bestThirdPlaced.getTeam(0));
	knockOut.push_back(bestThirdPlaced.getTeam(1));
	knockOut.push_back(bestThirdPlaced.getTeam(2));
	knockOut.push_back(bestThirdPlaced.getTeam(3));
}
void printKnockOut() {
	knockOut.print();
}
Team simulateMatches(Team &team1, Team &team2, int nMatches, bool print = false) {
	team1.weight = team1.points * 5 + team1.goals; // see page 3 for formula
	team2.weight = team2.points * 5 + team2.goals;
	int totalWeight = team1.weight + team2.weight;
	double team1WinProb = ((double)team1.weight) / totalWeight;
	int team1Wins = 0, team2Wins = 0;
	for (int i = 0; i < nMatches; i++) {
		double randomN = ((double)rand() / (RAND_MAX));
		if (randomN < team1WinProb)
			team1Wins++;
		else
			team2Wins++;
	}
	if (print) {
		std::cout << "-- Team,  Weighting,  Wins --" << std::endl;
		std::cout << team1.name << ",  " << team1.weight << ",  " << team1Wins << std::endl;
		std::cout << team2.name << ",  " << team2.weight << ",  " << team2Wins << std::endl;
		std::cout << "             -----" << std::endl;
	}
	if (team1Wins > team2Wins)
		return team1;
	else
		return team2;
}
void simulateKnockouts(Group &contestants) { // Here I use recursion as knockout groups have a recursive behavior
	Group newContestants = Group("Winners");
	while (contestants.size()) {
		int j = rand() % (contestants.size()-1) + 1;
		Team winner = simulateMatches(contestants.getTeam(0, true), contestants.getTeam(j, true), 1);
		newContestants.push_back(winner);
	}
	newContestants.print(true);
	if (newContestants.size() > 1)
		return simulateKnockouts(newContestants);
}
void simulateKnockouts() {
	simulateKnockouts(knockOut);
}
};


int main(int argc, char *argv[]){

 Values values("./group_results_windows.csv");

 values.populateValues();
 std::cout << " Sorting and printing groups " << std::endl;
 std::cout << std::endl;
 system("pause");
 std::cout << "GROUPS -- " << std::endl;
 values.populateGroups();
 values.sortGroups();
 values.printGroups();
 std::cout << std::endl;

 std::cout << " Forming knockout group " << std::endl;
 std::cout << std::endl;
 system("pause");
 std::cout << "KNOCKOUT --" << std::endl;
 values.knockOutPhase();
 values.printKnockOut();
 std::cout << std::endl;

 std::cout << " Match simulation " << std::endl;
 std::cout << std::endl;
 std::cout << "WINNING SIMULATION --" << std::endl;
 Team a, b;
 a.name = "A";
 b.name = "B";
 int nMatches = 0;
 std::cout << "Enter Team A points :";
 std::cin >> a.points;
 std::cout << "Enter Team A goals :";
 std::cin >> a.goals;
 std::cout << "Enter Team B points :";
 std::cin >> b.points;
 std::cout << "Enter Team B goals :";
 std::cin >> b.goals;
 std::cout << "Enter number of matches :";
 std::cin >> nMatches;
 values.simulateMatches(a,b,nMatches, true);
 
 std::cout << " Knockout rounds simulation " << std::endl;
 std::cout << std::endl;
 system("pause");
 std::cout << "KNOCKOUT ROUNDS --" << std::endl;
 values.simulateKnockouts();

 system("pause");
}

