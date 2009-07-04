#include "ScriptManager.hpp"

ScriptManager::ScriptManager() {
  //LogManager::log("Guile initialization");
  scm_init_guile();
  scm_c_define_gsubr("load-script", 1, 0, 0, (SCM (*)()) load_script);

}

void ScriptManager::loadScript(const char *script) {
  /* make sure guile is initialized */
  get();
  //LogManager::log("Loading script: %s\n", script);
  scm_c_primitive_load(script);
} 

SCM ScriptManager::load_script(SCM script) {
  ScriptManager::loadScript((const char*) script);
}
  
