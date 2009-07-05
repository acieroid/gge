#ifndef GGE_SYSTEM_HPP
#define GGE_SYSTEM_HPP

#include <vector>
#include <string>
#include <libguile.h>

class System {
  friend class ScriptManager;
  private:
    /* Arguments passed to the script */
    std::vector<std::string> m_vArgs;
    
    System() {}

    static System* get() {
      static System instance;
      return &instance;
    }

    static void initGuileFunctions();

  public:
    void setScriptArguments(std::vector<std::string> args);

    /* Get the arguments in a list */
    static SCM scm_get_args();
    /* Quit GGE */
    static SCM scm_quit();
};

#endif
