#ifndef GGE_SYSTEM_HPP
#define GGE_SYSTEM_HPP

#include "GGEElement.hpp"
#include <vector>
#include <string>
#include <libguile.h>

class System : public GGEElement {
  private:
    /* Arguments passed to the script */
    std::vector<std::string> m_vArgs;
    
    System() {}
    void initGuile();

  public:
    static System* get() {
      static System instance;
      return &instance;
    }

    static void setScriptArguments(std::vector<std::string> args);

    /* Get the arguments in a list */
    static SCM scm_get_args();
    /* Quit GGE */
    static SCM scm_quit();
    /* Launch a instance of guile's interpreter */
    static SCM scm_debug_prompt();
};

#endif
