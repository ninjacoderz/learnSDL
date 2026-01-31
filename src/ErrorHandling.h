#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <SDL3/SDL.h>
#include <iostream>
#include <string>

void CheckSDLError( const std::string& action) {
    const char* error = SDL_GetError();
    if(*error != '\0') {
        std::cout << action << " Error: " << error << '\n';
        SDL_ClearError();
    }
}

#endif 