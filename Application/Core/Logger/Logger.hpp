#ifndef LOGGER_HPP
#define LOGGER_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

namespace Logger {
	enum Status { NONE, ERRORS, WARNINGS, SUCSESS, IMPORTANT, MESSAGES, ALL };

	void Init(void);
	void Init(Status l_Status);
	void SetStatus(Status l_Status);

	void LogMessage(const std::string& l_Message);
	void LogImportant(const std::string& l_Message);
	void LogSucsess(const std::string& l_Message);
	void LogWarning(const std::string& l_Message);
	void LogError(const std::string& l_Message);

	void Destroy(void);
}

#endif