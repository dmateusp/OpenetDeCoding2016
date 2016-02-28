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

public:
	Values(const std::string filename) : m_filename(filename){
		// Groups creation
		groups.push_back(Group("A"));
		groups.push_back(Group("B"));
		groups.push_back(Group("C"));
		groups.push_back(Group("D"));
		groups.push_back(Group("E"));
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
};


int main(int argc, char *argv[]){

 Values values("./group_results_windows.csv");

 values.populateValues();

 std::cout << "GROUPS -- " << std::endl;
 values.populateGroups();
 values.printGroups();

 system("pause");
}

