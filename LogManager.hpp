#ifndef LOGMANAGER_HPP
#define LOGMANAGER_HPP

#include "GGEElement.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <libguile.h>

class LogManager : public GGEElement {
	private:
		int m_iOutputMode;
		std::string m_sOutputFile;
		std::ofstream m_oOutputStream;

		LogManager(); 
		void initGuile();

	public:
    static LogManager* get() {
      static LogManager instance;
      return &instance;
    }

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
