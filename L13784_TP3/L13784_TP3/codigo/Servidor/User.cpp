#include "User.h"


User::User(std::string alias, std::string ipAddress, int numbersGenerated, int sequencesStarted) 
	: m_alias{alias}, m_ipAddress{ipAddress}, m_numbersGenerated{numbersGenerated}, m_sequencesStarted{sequencesStarted}
{
}


void User::addNumberToSequence(double number)
{
	m_sequence.push_back(number);
	m_sum += number;
	m_numbersGenerated++;
}

void User::clearSequence()
{
	m_sequence.clear();
	m_sum = 0;
	m_sequencesStarted++;
}

void User::serialize(std::ofstream& file) const
{
	file.write(m_alias.c_str(), m_alias.size());
	file.put('\0');
	file.write(m_ipAddress.c_str(), m_ipAddress.size());
	file.put('\0');
	file.write(reinterpret_cast<const char*>(&m_numbersGenerated), sizeof(m_numbersGenerated));
	file.write(reinterpret_cast<const char*>(&m_sequencesStarted), sizeof(m_sequencesStarted));

}

User User::deserialize(std::ifstream& file)
{
	std::string alias{};
	std::string ipAddress{};
	int numbersGenerated{};
	int sequencesStarted{};

	std::getline(file, alias, '\0');
	std::getline(file, ipAddress, '\0');
	file.read(reinterpret_cast<char*>(&numbersGenerated), sizeof(numbersGenerated));
	file.read(reinterpret_cast<char*>(&sequencesStarted), sizeof(sequencesStarted));

	return User(alias, ipAddress, numbersGenerated, sequencesStarted);
}



void UserManager::addUser(const std::string& alias, const std::string& ipAddress)
{
	if (m_users.find(alias) == m_users.end())
	{
		m_users[alias] = User(alias, ipAddress);
	}
}

User* UserManager::getUser(const std::string& alias)
{
	auto it = m_users.find(alias); //iterator
	if (it != m_users.end())
	{
		return &it->second;
	}
	else
	{
		return nullptr;
	}
}

void UserManager::saveUsers(const std::string& filename)
{

	std::ofstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		int numUsers = m_users.size();
		file.write(reinterpret_cast<const char*>(&numUsers), sizeof(numUsers));
		for (auto& pair : m_users)
		{
			pair.second.serialize(file);
		}
	}
}

void UserManager::loadUsers(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (file.is_open())
	{
		int numUsers{};
		file.read(reinterpret_cast<char*>(&numUsers), sizeof(numUsers));
		for (int i = 0; i < numUsers; i++)
		{
			User user = User::deserialize(file);
			m_users[user.getAlias()] = user;
		}

	}
}

void UserManager::clearUsersFile(const std::string& filename) 
{
	// Abrir el archivo en modo binario y de truncado para eliminar su contenido
	std::ofstream file(filename, std::ios::binary | std::ios::trunc);
	if (file.is_open())
	{
		// Archivo truncado exitosamente
		file.close();
		

		// Opcional: tambi�n puedes limpiar los usuarios en memoria si lo deseas
		// m_users.clear();
	}
	else
	{
		// Manejo de error si no se puede abrir el archivo
		std::cerr << "Error: No se pudo abrir el archivo '" << filename << "' para borrar.\n";
	}
}