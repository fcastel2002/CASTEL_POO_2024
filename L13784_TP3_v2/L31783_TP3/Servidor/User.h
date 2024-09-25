#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
class User
{
private:

	std::string m_alias{};
	std::string m_ipAddress{};
	
	int m_numbersGenerated{};
	int m_sequencesStarted{};
public:
	User(std::string alias, std::string ipAddress, int numbersGenerated, int sequencesStarted);
	std::string getAlias() const { return m_alias };
	std::string getIpAddress() const { return m_ipAddress };
	int getNumbersGenerated() const { return m_numbersGenerated };
	int getSequencesStarted() const { return m_sequencesStarted };
	void incrementNumbersGenerated() { m_numbersGenerated++ };
	void incrementSequencesStarted() { m_sequencesStarted++ };
	void serialize(std::ofstream& file) const;
	static User deserialize(std::ifstream& file);
	
};

class UserManager
{
private:
	std::unordered_map<std::string, User> m_users{};
public:
	void addUser(const std::string& alias, const std::string& ipAddress);
	User* getUser(const std::string& alias);

	void saveUsers(const std::string& filename);
	void loadUsers(const std::string& filename);

};