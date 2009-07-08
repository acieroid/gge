#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include "GGEElement.hpp"
#include <libguile.h>
#include <vector>

class ScriptManager {
  private:
    std::vector<GGEElement*> m_vElements;
    ScriptManager() {}

    static ScriptManager* get() {
      static ScriptManager instance;
      return &instance;
    }
  public:
		/* Initialize guile */
		static void initGuile();

    static void registerElement(GGEElement *e);

    /* Load a script */
    static void loadScript(const char *script); 
    static SCM scm_load_script(SCM script);
};

#endif
