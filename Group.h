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
};
class Group
{
private:
	std::string m_name;
	std::list<Team> m_group;
public:
	Group(std::string name);
	~Group();
	const std::string name() const;
	std::list<Team> list();
	void push_back(Team team);
	void print();
	bool isInGroup(std::string team);
	void update(Team team);
};

