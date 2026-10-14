#ifndef __APP_CORE_IMAGE__HPP__
#define __APP_CORE_IMAGE__HPP__

#include "App/Core/Entity.hpp"

namespace App::Core {
class Image : public Entity {
  public:
    Image();
    virtual ~Image();

    virtual int  getWidth()                                  = 0;
    virtual int  getHeight()                                 = 0;
    virtual void modulateColor(int red, int green, int blue) = 0;
    virtual void visualize()                                 = 0;
};
} // namespace App::Core

#endif
