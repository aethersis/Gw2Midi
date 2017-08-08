#pragma once
#include "stdafx.h"
#include <string>
#include "KeyConfig.h"

class ConfigParser
{
public:
	ConfigParser(const std::string& configPath);
	KeyConfig getParsedConfig();
	void writeDefaultConfig();
private:
	const std::string m_configPath;
};