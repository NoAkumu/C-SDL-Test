#ifndef OBJECT_H
#define OBJECT_H

#include "Engine_Types.h"

typedef struct
{
    char* name;

    char* texture_file;
    SDL_Texture* texture;
    SDL_Rect bounds;
    Color color;
    
    Vector2 pos;
    Vector2 size;
} Object;

Object Awake(SDL_Renderer* renderer, Object *me) {
    SDL_Rect texture_rect = {me->pos.x, me->pos.y, me->size.x, me->size.y};
    me->bounds = texture_rect;
    me->texture = IMG_LoadTexture(renderer, me->texture_file);
}
void Draw(SDL_Renderer* renderer, Object *me) {
    SDL_Rect texture_rect = {me->pos.x, me->pos.y, me->size.x, me->size.y};
    me->bounds = texture_rect;
    SDL_SetRenderDrawColor(renderer, me->color.r, me->color.g, me->color.b, me->color.a);
    SDL_RenderCopy(renderer, me->texture, NULL, &me->bounds);
}
#endif