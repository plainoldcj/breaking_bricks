/*
file: log.h
*/

#pragma once

#include <string>
#include <fstream>
#include "util_singleton.h"

class Log : public UTIL::Singleton<Log> {
private:
	std::ofstream _file;

	std::ofstream& MessageType(const std::string& label,
		const std::string& htmlColor);
public:
	static const char* endl;

	Log(void);
	~Log(void);

	bool IsOpen(void) const {
		return _file.is_open();
	}

	std::ofstream& Info(void);
	std::ofstream& Warning(void);
	std::ofstream& Error(void);
};