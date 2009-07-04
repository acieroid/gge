#ifndef GGE_SCRIPTMANAGER_HPP
#define GGE_SCRIPTMANAGER_HPP

#include <libguile.h>

class ScriptManager {
  private:
    ScriptManager();

    static ScriptManager* get() {
      static ScriptManager instance;
      return &instance;
    }
  public:
    /* Load a script */
    static void loadScript(const char *script); 
    static SCM load_script(SCM script);
};

#endif
