#include "LogManager.hpp"

LogManager::LogManager() {
  m_iOutputMode = OUTPUT_STDERR;
	m_sOutputFile = "log.txt";
}

void LogManager::setOutputMode(int outputMode) {
	if (outputMode & OUTPUT_FILE &&
			!(get()->m_iOutputMode & OUTPUT_FILE)) {
    get()->m_oOutputStream.open(get()->m_sOutputFile.c_str());
	}
	else if (!(outputMode & OUTPUT_FILE) &&
					 get()->m_iOutputMode & OUTPUT_FILE) {
		get()->m_oOutputStream.close();
	}
  get()->m_iOutputMode = outputMode;
}

void LogManager::setOutputFile(std::string path) {
	if (get()->m_iOutputMode & OUTPUT_FILE) {
		get()->m_oOutputStream.close();
		get()->m_oOutputStream.open(path.c_str());
	}
	get()->m_sOutputFile = path;
}

void LogManager::log(std::string what) {
	if (get()->m_iOutputMode & OUTPUT_STDOUT) std::cout << what;
	if (get()->m_iOutputMode & OUTPUT_STDERR) std::cerr << what;
	if (get()->m_iOutputMode & OUTPUT_FILE) get()->m_oOutputStream << what;
}

