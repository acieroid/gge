#include "System.hpp"

void System::initGuileFunctions() {
  scm_c_define_gsubr("get-args", 0, 0, 0, (SCM (*)()) scm_get_args);
  scm_c_define_gsubr("quit", 0, 0, 0, (SCM (*)()) scm_quit);
}
void System::setScriptArguments(std::vector<std::string> args) {
  m_vArgs = args;
}

SCM System::scm_get_args() {
  SCM args;
  for (std::vector<std::string>::iterator I = get()->m_vArgs.begin(); 
       I != get()->m_vArgs.end(); I++) {
    args = scm_append(
            scm_list_2(args, 
                       scm_list_1(scm_from_locale_string((*I).c_str()))));

  }
  return args;
}

SCM System::scm_quit() {
  /* Not really clean, but ... */
  exit(0);
}
