#include "System.hpp"

void System::initGuile() {
  scm_c_define_gsubr("get-args", 0, 0, 0, (SCM (*)()) scm_get_args);
  scm_c_define_gsubr("quit", 0, 0, 0, (SCM (*)()) scm_quit);
  scm_c_define_gsubr("debug-prompt", 0, 0, 0, (SCM (*)()) scm_debug_prompt);
}
void System::setScriptArguments(std::vector<std::string> args) {
  get()->m_vArgs = args;
}

SCM System::scm_get_args() {
  SCM args = SCM_EOL;
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

SCM System::scm_debug_prompt() {
  scm_shell(0, NULL);
}
