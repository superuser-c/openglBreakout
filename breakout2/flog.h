#pragma once

#include <string>
#include <fstream>

enum LogType { info, error, warning, raw };

class FLog {
public:
	static void init();
	static void glogf(std::string s, std::string a, LogType t);
	static void logShutdown();
private:
	static int logFileCreated;
	static std::fstream fLogStream;
};