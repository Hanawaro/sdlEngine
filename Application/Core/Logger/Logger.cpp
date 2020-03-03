#include <Logger.hpp>

#include <fstream>
#include <ctime>
#include <windows.h>

#define MESSAGE_COLOR		9
#define MESSAGE_IMPORTANT	3
#define SUCSESS_COLOR		10
#define WARNING_COLOR		14
#define ERROR_COLOR			4


static Logger::Status g_Status = Logger::Status::SUCSESS;
static std::ofstream* g_Log = nullptr;

void Logger::Init(void) {
	g_Log = new std::ofstream("App.log");
	if (g_Status >= Logger::Status::SUCSESS && g_Log) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUCSESS_COLOR);

		std::cout << buffer << "Logger initialize" << std::endl;
	}
}

void Logger::Init(Status l_Status) {
	g_Log = new std::ofstream("App.log");
	SetStatus(l_Status);
	if (g_Status >= Logger::Status::SUCSESS && g_Log) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUCSESS_COLOR);

		std::cout << buffer << "Logger initialize" << std::endl;
	}
}

void Logger::SetStatus(Status l_Status) {
	g_Status = l_Status;
}

void Logger::LogMessage(const std::string& l_Message) {
	if (g_Status >= Logger::Status::MESSAGES && g_Log) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MESSAGE_IMPORTANT);

		std::cout << buffer << l_Message << std::endl;
		*g_Log << buffer << l_Message << std::endl;
	}
}

void Logger::LogImportant(const std::string& l_Message) {
	if (g_Status >= Logger::Status::IMPORTANT && g_Log) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MESSAGE_COLOR);

		std::cout << buffer << l_Message << std::endl;
		*g_Log << buffer << l_Message << std::endl;
	}
}

void Logger::LogSucsess(const std::string& l_Message) {
	if (g_Status >= Logger::Status::SUCSESS && g_Log) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUCSESS_COLOR);

		std::cout << buffer << l_Message << std::endl;
		*g_Log << buffer << l_Message << std::endl;
	}
}

void Logger::LogWarning(const std::string& l_Message) {
	if (g_Status >= Logger::Status::WARNINGS && g_Log) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WARNING_COLOR);

		std::cout << buffer << l_Message << std::endl;
		*g_Log << buffer << l_Message << std::endl;
	}
}

void Logger::LogError(const std::string& l_Message) {
	if (g_Status >= Logger::Status::ERRORS && g_Log) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ERROR_COLOR);

		std::cout << buffer << l_Message << std::endl;
		*g_Log << buffer << l_Message << std::endl;
	}
}

void Logger::Destroy(void) {
	g_Log->close();
	delete g_Log;

	if (g_Status >= Logger::Status::SUCSESS) {
		char buffer[255] = { 0 };
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		strftime(buffer, 80, "[%H:%M:%S] ", timeinfo);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SUCSESS_COLOR);

		std::cout << buffer << "Logger closed" << std::endl;
	}
}




