#ifndef GGEELEMENT_HPP
#define GGEELEMENT_HPP

#include <libguile.h>
/*#include "ScriptManager.hpp"*/

class GGEElement {
  friend class ScriptManager;
  private:
    virtual void initGuile() = 0;
  public:
    GGEElement() ;

};

#endif
