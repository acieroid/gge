#include "System.hpp"

void System::setScriptArguments(std::vector<std::string> args) {
  m_vArgs = args;
}


SCM System::get_args() {
  SCM args;
  for (std::vector<std::string>::iterator I = get()->m_vArgs.begin(); 
       I != get()->m_vArgs.end(); I++) {
    args = scm_append(
            scm_list_2(args, 
                       scm_list_1(scm_from_locale_string((*I).c_str()))));
    

  }
  return args;
}

