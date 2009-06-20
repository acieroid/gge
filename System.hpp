#ifndef GGE_SYSTEM_HPP
#define GGE_SYSTEM_HPP

#include <vector>
#include <string>
#include <libguile.h>

class System {
  private:
    /* Arguments passed to the script */
    std::vector<std::string> m_vArgs;
    
    System() {}

    static System* get() {
      static System instance;
      return &instance;
    }

  public:
    /* Set the m_vArgs variable */
    void setScriptArguments(std::vector<std::string> args);

    /* Get the arguments in a list */
    static SCM get_args();
};

#endif
