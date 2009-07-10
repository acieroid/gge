#include "LogManager.hpp"

LogManager::LogManager() {
}

void LogManager::setOutputMode(int outputMode) {
	if (outputMode & OUTPUT_FILE &&
			!(m_iOutputMode & OUTPUT_FILE)) {
    m_oOutputStream.open(m_sOutputFile.c_str());
	}
	else if (!(outputMode & OUTPUT_FILE) &&
					 m_iOutputMode & OUTPUT_FILE) {
		m_oOutputStream.close();
	}
  m_iOutputMode = outputMode;
}

void LogManager::setOutputFile(std::string path) {
	if (m_iOutputMode & OUTPUT_FILE) {
		m_oOutputStream.close();
		m_oOutputStream.open(path.c_str());
	}
	m_sOutputFile = path;
}

void LogManager::log(std::string what) {
	if (m_iOutputMode & OUTPUT_STDOUT) std::cout << what << std::endl;
	if (m_iOutputMode & OUTPUT_STDERR) std::cerr << what << std::endl;
	if (m_iOutputMode & OUTPUT_FILE) 
	  m_oOutputStream << what << std::endl;
}

MainLog::MainLog() {
  m_iOutputMode = OUTPUT_STDOUT; 
	m_sOutputFile = "log.txt";
}

void MainLog::initGuile() {
	scm_c_define_gsubr("log", 1, 0, 0, (SCM (*)()) scm_log);
}

SCM MainLog::scm_log(SCM what) {
	get()->log(scm_to_locale_string(what));
}

ErrorLog::ErrorLog() {
  m_iOutputMode = OUTPUT_STDERR;
  m_sOutputFile = "error.txt";
}

void ErrorLog::initGuile() {
	scm_c_define_gsubr("error", 1, 1, 0, (SCM (*)()) scm_error);
}

SCM ErrorLog::scm_error(SCM what, SCM fatal) {
  ErrorLog::get()->log(scm_to_locale_string(what));
  if (!SCM_UNBNDP(fatal) && scm_is_true(fatal)) {
    System::abort();
  }
}
