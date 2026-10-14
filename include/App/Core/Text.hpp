#ifndef __APP_CORE_TEXT__HPP__
#define __APP_CORE_TEXT__HPP__

#include "App/Core/Entity.hpp"
#include <iostream>

namespace App::Core {
class Text : public Entity {
  public:
    Text();
    virtual ~Text();

    virtual int  getWidth()                                              = 0;
    virtual int  getHeight()                                             = 0;
    virtual void setText(std::string text, int red, int green, int blue) = 0;
    virtual void visualize()                                             = 0;
};
} // namespace App::Core

#endif
