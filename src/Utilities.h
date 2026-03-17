//
// Created by Binh Nguyen Thanh on 17/3/26.
//

#ifndef _UTILITIES_H
#define _UTILITIES_H
namespace Utilities{
    inline SDL_Rect Round(const SDL_FRect& R) {
        return {
            static_cast<int>(std::round(R.x)),
            static_cast<int>(std::round(R.y)),
            static_cast<int>(std::round(R.w)),
            static_cast<int>(std::round(R.h)),
          };
    }
}
#endif //_UTILITIES_H