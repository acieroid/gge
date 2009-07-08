#ifndef GGE_SCRIPTMANAGER_HPP
#define GGE_SCRIPTMANAGER_HPP

#include <libguile.h>
#include "LogManager.hpp"
#include "System.hpp"
#include "Display.hpp"

class ScriptManager {
  private:
    ScriptManager();

    static ScriptManager* get() {
      static ScriptManager instance;
      return &instance;
    }
  public:
		/* Initialize guile */
		static void initGuile();

    /* Load a script */
    static void loadScript(const char *script); 
    static SCM scm_load_script(SCM script);
};

#endif
