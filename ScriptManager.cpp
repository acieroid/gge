#include "ScriptManager.hpp"

ScriptManager::ScriptManager() {
  LogManager::log("Guile initialization");
  scm_init_guile();
  scm_c_define_gsubr("load-script", 1, 0, 0, (SCM (*)()) scm_load_script);

}

void ScriptManager::initGuile() {
	/* This just call the constructor */
	get();

	LogManager::initGuileFunctions();
  System::initGuileFunctions();
}

void ScriptManager::loadScript(const char *script) {
  LogManager::log("Loading script: " + std::string(script));
  scm_c_primitive_load(script);
} 

SCM ScriptManager::scm_load_script(SCM script) {
  ScriptManager::loadScript(scm_to_locale_string(script));
}
