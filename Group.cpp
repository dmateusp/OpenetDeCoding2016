#include "Group.h"
// Daniel Mateus Pires
// Student, 3rd year Computer Science

/* This is my solution for
* De/Coding 2016 OPENET */
Group::Group(std::string name) : m_name(name), m_group(NULL)
{}
Group::~Group()
{}
const std::string Group::name() const {
	return m_name;
}
std::list<Team> Group::list() {
	return m_group;
}
void Group::push_back(Team team) {
	m_group.push_back(team);
}
void Group::print() {
	std::cout << "-- GROUP " << m_name << " --" << std::endl;
	if (!m_group.empty()) {
		for (std::list<Team>::iterator j = m_group.begin(); j != m_group.end(); j++) {
			std::cout << j->name << ", pts : " << j->points << ", goals : " << j->goals << std::endl;
		}
	}
}
bool Group::isInGroup(std::string team) {
	if (!m_group.empty()) {
		for (std::list<Team>::iterator j = m_group.begin(); j != m_group.end(); j++) {
			if (j->name == team)
				return true;
		}
	}
	return false;
}
void Group::update(Team team) {
	for (std::list<Team>::iterator j = m_group.begin(); j != m_group.end(); j++) {
		if (j->name == team.name) {
			j->points += team.points;
			j->goals += team.goals;
		}
	}
}