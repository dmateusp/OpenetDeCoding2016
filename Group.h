#pragma once
// Daniel Mateus Pires
// Student, 3rd year Computer Science

/* This is my solution for
* De/Coding 2016 OPENET */
#include <string>
#include <list>
#include <iostream>
struct Team {
	std::string name;
	int points = 0;
	int goals = 0;
	int weight = 0;
	bool operator ==(const Team& a)
	{
		return (name == a.name && points == a.points && goals == a.goals && weight == a.weight);
	}
};
class Group
{
private:
	std::string m_name;
	std::list<Team> m_group;
	static bool compare_rank(const Team &first,const Team &second);
	void calculateWeights();
public:
	Group(std::string name);
	Group(std::string name, Team predefinedTeam);
	~Group();
	const std::string name() const;
	std::list<Team> list();
	void push_back(Team team);
	void print(bool onlyName = false);
	bool isInGroup(std::string team);
	void update(Team team);
	void sort();
	std::list<Team>::iterator begin();
	std::list<Team>::iterator end();
	int size();
	Team getTeam(int index, bool pop = false);
};

