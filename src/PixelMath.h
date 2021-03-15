#ifndef PIXELMATH_H
#define PIXELMATH_H
#include <limits>

namespace PixelMath{
    bool ConvertPositionToPixel(const Vector2Elm &position,SDL_Point &pixelposition, const SDL_Rect &source, const int &screen_width, const int &screen_height){
        long max_pos_x = std::numeric_limits<int>::max()-screen_width/2.0 + source.w/2.0;
        long max_pos_y = std::numeric_limits<int>::max() + screen_height/2.0 - source.h/2.0;
        if(AuxMath::abs(position.x_) <= max_pos_y && AuxMath::abs(position.y_) <= max_pos_y){  
            pixelposition.x = static_cast<int>(screen_width/2.0 + position.x_- source.w/2.0 );
            pixelposition.y = static_cast<int>(screen_height/2.0 - position.y_ - source.h/2.0);
            return true;
        }
        return false;
    }
}
#endif
