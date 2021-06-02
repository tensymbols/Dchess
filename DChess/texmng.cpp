#include "texmng.h"

SDL_Texture* texLoader::loadTexture(const char* filename, SDL_Renderer* renderer)
{
    SDL_Surface* surf = IMG_Load(filename);    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);;
    SDL_FreeSurface(surf);

    return tex;
}
