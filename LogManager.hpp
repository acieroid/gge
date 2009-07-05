#ifndef LOGMANAGER_HPP
#define LOGMANAGER_HPP
#include <string>
#include <fstream>
#include <iostream>
#include <libguile.h>
#include "ScriptManager.hpp"

class LogManager {
	friend class ScriptManager;
	private:
		LogManager(); 

    static LogManager *get() {
      static LogManager instance;
      return &instance;
    }

		static void initGuileFunctions();

		int m_iOutputMode;
		std::string m_sOutputFile;
		std::ofstream m_oOutputStream;
	public:
		enum {
			OUTPUT_FILE = 1, 
			OUTPUT_STDOUT = 2,
			OUTPUT_STDERR = 4
		};
		static void setOutputMode(int outputMode);
		static void setOutputFile(std::string path);

		static void log(std::string what);
		static SCM scm_log(SCM what);
};
#endif
