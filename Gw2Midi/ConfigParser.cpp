#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "ConfigParser.h"

ConfigParser::ConfigParser(const std::string & configPath) : m_configPath(std::move(configPath))
{
}

bool endsWith(const std::string& s, const std::string& suffix)
{
	return s.size() >= suffix.size() &&
		s.substr(s.size() - suffix.size()) == suffix;
}

std::vector<std::string> split(const std::string& s, const std::string& delimiter, const bool& removeEmptyEntries = false)
{
	std::vector<std::string> tokens;

	for (size_t start = 0, end; start < s.length(); start = end + delimiter.length())
	{
		size_t position = s.find(delimiter, start);
		end = position != std::string::npos ? position : s.length();

		std::string token = s.substr(start, end - start);
		if (!removeEmptyEntries || !token.empty())
		{
			tokens.push_back(token);
		}
	}

	if (!removeEmptyEntries &&
		(s.empty() || endsWith(s, delimiter)))
	{
		tokens.push_back("");
	}

	return tokens;
}

KeyConfig ConfigParser::getParsedConfig()
{
	KeyConfig config;
	std::ifstream inputFile(m_configPath);
	std::string line;
	auto lineId = 0;

	if (inputFile.is_open())
	{
		while (std::getline(inputFile, line) && lineId < KeyCount)
		{
			if (line.size() > 0 && line[0] != '#')
			{
				std::remove_if(line.begin(), line.end(), isspace); // remove whitespaces
				auto columns = split(line, ",", true);
				if (columns.size() == 2)
				{
					config.bindings[lineId] = columns[1][0];
				}
				else
				{
					inputFile.close();
					throw std::exception("Config file is corrupted. Remove it to automatically generate valid config. Using default settings.");
				}
				++lineId;
			}
		}
	}
	else
	{
		writeDefaultConfig();
		throw std::exception("Failed to open config file. Writing default config in current location and using default settings.");
	}

	inputFile.close();
	return config;
}

void ConfigParser::writeDefaultConfig()
{
	std::ofstream outputFile(m_configPath);
	if (outputFile.is_open())
	{
		outputFile << "#Please do not modify the order of rows in this file.Only the second column is modifiable." << std::endl <<
			          "#The first column represents note name or function and the second column represents bound key." << std::endl <<
			          "#I.e. If you want to bind key ; to note D, change the line D, 2 to D, ;" << std::endl << 
			          "C, 1" << std::endl <<
			          "D, 2" << std::endl <<
			          "E, 3" << std::endl <<
			          "F, 4" << std::endl <<
			          "G, 5" << std::endl <<
			          "A, 6" << std::endl <<
			          "H, 7" << std::endl <<
			          "OctaveDown, 9" << std::endl <<
			          "OctaveUp, 0";
		outputFile.close();
	}
	else
	{
		throw std::exception("Failed to write config file. Make sure you have write permissions");
	}

}