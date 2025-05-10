#include "pch.h"
#include "SoundPlayer.h"

bool SoundPlayer::init() 
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) 
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Set up audio output format, buffer, and open the audio device
    if (Mix_OpenAudio(
        22050,              // Frequency aka sample rate
        MIX_DEFAULT_FORMAT, // Audio format (signed 16 bit native to system's endianness)
        2,                  // Number of channels (1 = mono, 2 = stereo)
        4096                // Buffer size (larger = more latency, smaller = more responsive)
        ) < 0) 
    {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << "\n";
        return false;
    }

    return load_sound(SoundEffect::Death, "sounds/death_sound.wav") &&
           load_sound(SoundEffect::Footstep, "sounds/grassy_footsteps.wav") &&
           load_sound(SoundEffect::HitWall, "sounds/hit_wall.wav") && 
           load_sound(SoundEffect::GameStart, "sounds/game_start.wav");
}

bool SoundPlayer::load_sound(SoundEffect type, const std::string& path) 
{
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) 
    {
        std::cerr << "Failed to load " << path << ": " << Mix_GetError() << "\n";
        return false;
    }
    m_sounds[type] = chunk;
    return true;
}

void SoundPlayer::play(SoundEffect sound) 
{
    auto it = m_sounds.find(sound);
    if (it != m_sounds.end()) 
    {
        Mix_PlayChannel(-1, it->second, 0);
    }
}

void SoundPlayer::cleanup() 
{
    // Wait until all sounds finish playing
    while (Mix_Playing(-1) != 0) 
    {
        SDL_Delay(100);
    }

    for (auto& [_, chunk] : m_sounds) 
    {
        Mix_FreeChunk(chunk);
    }
    Mix_CloseAudio();   // Close audio device
    Mix_Quit();         // Quit SDL_mixer
    SDL_Quit();         // Quit all SDL subsystems
}
