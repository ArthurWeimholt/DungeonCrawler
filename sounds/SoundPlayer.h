// This file contains the implementation of the sounds using the SDL library
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

enum class SoundEffect 
{
    GameStart,
    Death,
    Footstep,
    HitWall
};

class SoundPlayer
{
public:
    bool init();
    void play(SoundEffect sound);
    void cleanup();

private:
    bool load_sound(SoundEffect type, const std::string& path);
    
    // Map that stores the current sounds
    std::unordered_map<SoundEffect, Mix_Chunk*> m_sounds;
};
