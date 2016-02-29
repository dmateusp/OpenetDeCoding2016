#include "Group.h"
// Daniel Mateus Pires
// Student, 3rd year Computer Science

/* This is my solution for
* De/Coding 2016 OPENET */
Group::Group(std::string name) : m_name(name), m_group(NULL)
{}
Group::Group(std::string name, Team predefinedTeam) : m_name(name), m_group(NULL)
{
	m_group.push_back(predefinedTeam);
}
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
void Group::print(bool onlyName) {
	std::cout << "-- GROUP " << m_name << " --" << std::endl;
	if (!m_group.empty()) {
		for (std::list<Team>::iterator j = m_group.begin(); j != m_group.end(); j++) {
			if (onlyName)
				std::cout << j->name << std::endl;
			else
				std::cout << j->name << ", pts : " << j->points << ", goal difference : " << j->goals << std::endl;
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
bool Group::compare_rank(const Team &first,const Team &second) { // Custon ranking with Football rules
	if (first.points > second.points)
		return true;
	else {
		if (first.points == second.points) {
			return (first.goals > second.goals);
		}
		else {
			return false;
		}
	}
}
void Group::sort() { // We pass our custom method to the sort method
	m_group.sort(compare_rank);
}
Team Group::getTeam(int index, bool pop) { // Returns a team from the list
	std::list<Team>::iterator i = m_group.begin();
	std::advance(i, index);
	Team t = *i;
	if (pop)
		m_group.remove(t);
	return t;
}
std::list<Team>::iterator Group::begin() {
	return m_group.begin();
}
std::list<Team>::iterator Group::end() {
	return m_group.end();
}
int Group::size() {
	return m_group.size();
}