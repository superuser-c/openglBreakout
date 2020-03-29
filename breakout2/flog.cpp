#include "flog.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

int FLog::logFileCreated;
std::fstream FLog::fLogStream;

void FLog::init() {
	#ifdef LOGGER_CREATE_LOG_FILE
		logFileCreated = 0;
	#else
		logFileCreated = 2;
	#endif
}

void FLog::glogf(std::string s, std::string a, LogType t) {
	if (!logFileCreated) { // create log file it doesn't exist
		try {
			std::string fileName = "logs/log_";
			__time64_t t;
			struct std::tm now;
			_time64(&t);
			errno_t err = _localtime64_s(&now, &t); // get actual time
			if (err)
			{
				throw new std::exception();
			}
			// create name from time
			fileName += std::to_string(now.tm_year + 1900) + '_';
			fileName += std::to_string(now.tm_mon + 1) + '_';
			fileName += std::to_string(now.tm_mday) + '_';
			fileName += std::to_string(now.tm_hour) + '_';
			fileName += std::to_string(now.tm_min) + '_';
			fileName += std::to_string(now.tm_sec) + ".log";
			fLogStream.open(fileName, std::ios::out);
			logFileCreated = 1;
			glogf("log file created (" + fileName + ")", "LOGGER", LogType::info);
		}
		catch (const std::exception& e) { 
			logFileCreated = 2;
			glogf("failed to create log file", "LOGGER", LogType::error);
			glogf(e.what(), "LOGGER", LogType::error);
			std::cin.get();
			std::exit(-1);
		}
	}
	// log message
	if (t == LogType::raw) {
		std::cout << s << std::endl;
		if (logFileCreated == 1) {
			fLogStream << s << std::endl;
		}
		return;
	}
	std::string type = t == LogType::info ? "INFO"
		: t == LogType::warning ? "!WARNING!"
		: t == LogType::error ? "#ERROR#" : "";
	std::string c = "[" + type + "/" + a + "]: " + s;
	std::cout << c << std::endl;
	if (logFileCreated == 1) {
		fLogStream << c << std::endl;
	}
}

void FLog::logShutdown() {
	if (logFileCreated == 1) {
		fLogStream.close();
	}
}
