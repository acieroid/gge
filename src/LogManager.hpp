#ifndef LOGMANAGER_HPP
#define LOGMANAGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <libguile.h>
#include "GGEElement.hpp"
#include "System.hpp"

class LogManager {
	protected:
		int m_iOutputMode;
		std::string m_sOutputFile;
		std::ofstream m_oOutputStream;

		void setOutputMode(int outputMode);
		void setOutputFile(std::string path);

		void log(std::string what);
	public:
		LogManager(); 
		enum {
			OUTPUT_FILE = 1, 
			OUTPUT_STDOUT = 2,
			OUTPUT_STDERR = 4
		};
};

class MainLog : public GGEElement, public LogManager {
  private:
    MainLog();
    void initGuile();
    
    static SCM scm_log(SCM what);
  public:
    static MainLog* get() {
      static MainLog instance;
      return &instance;
    }
};

class ErrorLog : public GGEElement, public LogManager {
  private:
    ErrorLog();
    void initGuile();
    
    static SCM scm_error(SCM what, SCM fatal);
  public:
    static ErrorLog* get() {
      static ErrorLog instance;
      return &instance;
    }
};

#endif
