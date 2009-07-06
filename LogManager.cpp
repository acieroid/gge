#include "LogManager.hpp"

LogManager::LogManager() {
  m_iOutputMode = OUTPUT_STDERR;
	m_sOutputFile = "log.txt";
}

void LogManager::initGuileFunctions() {
	scm_c_define_gsubr("log", 1, 0, 0, (SCM (*)()) scm_log);
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
	if (get()->m_iOutputMode & OUTPUT_STDOUT) std::cout << what << std::endl;
	if (get()->m_iOutputMode & OUTPUT_STDERR) std::cerr << what << std::endl;
	if (get()->m_iOutputMode & OUTPUT_FILE) 
	  get()->m_oOutputStream << what << std::endl;
}

SCM LogManager::scm_log(SCM what) {
	LogManager::log(scm_to_locale_string(what));
}
