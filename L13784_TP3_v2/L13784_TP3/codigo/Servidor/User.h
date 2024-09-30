#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
class User
{
private:

	std::string m_alias{};
	std::string m_ipAddress{};
	double m_sum{};
	int m_numbersGenerated{};
	int m_sequencesStarted{};

	std::vector <double> m_sequence{};
public:
	User(std::string alias =  {""}, std::string ipAddress = {""}, int numbersGenerated = {0}, int sequencesStarted = {1});
	
	std::string getAlias() const { return m_alias; }
	std::string getIpAddress() const { return m_ipAddress; }
	int getNumbersGenerated() const { return m_numbersGenerated; }
	int getSequencesStarted() const { return m_sequencesStarted; }
	void incrementNumbersGenerated() { m_numbersGenerated++; }
	void incrementSequencesStarted() { m_sequencesStarted++; }

	double getSum() const { return m_sum; }
	double getAverage() const { return m_sum / m_sequence.size(); }
	void addNumberToSequence(double number);
	std::vector<double> getSequence() const { return m_sequence; }
	void clearSequence();
	void serialize(std::ofstream& file) const;
	static User deserialize(std::ifstream& file);
	
};

class UserManager
{
private:
	std::map<std::string, User> m_users{};
public:
	void addUser(const std::string& alias, const std::string& ipAddress);
	User* getUser(const std::string& alias);
	const std::map<std::string, User>& getUsers() const { return m_users; } 
	void saveUsers(const std::string& filename = { "users.bin" });
	void loadUsers(const std::string& filename = { "users.bin" });
	void clearUsersFile(const std::string& filename = { "users.bin" });

};