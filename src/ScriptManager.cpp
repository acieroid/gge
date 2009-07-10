#include "ScriptManager.hpp"

void ScriptManager::initGuile() {
  scm_init_guile();
  scm_c_define_gsubr("load-script", 1, 0, 0, (SCM (*)()) scm_load_script);


  for (std::vector<GGEElement *>::iterator I = get()->m_vElements.begin(), 
       E = get()->m_vElements.end(); I != E; I++) {
    (*I)->initGuile();
  }
}

void ScriptManager::registerElement(GGEElement *e) {
  get()->m_vElements.push_back(e);
}

void ScriptManager::loadScript(const char *script) {
  scm_c_primitive_load(script);
} 

SCM ScriptManager::scm_load_script(SCM script) {
  ScriptManager::loadScript(scm_to_locale_string(script));
}
