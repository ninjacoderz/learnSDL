/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 * Converted to SDL3_mixer 3.0 API
 */

#include <SDL3_mixer/SDL_mixer.h>
#include <string.h>

#include "../common.h"
#include "sound.h"
#include "../Defs.h"

static void loadSounds(void);

static MIX_Audio *sounds[SND_MAX];
static MIX_Audio *music;

static MIX_Track *soundTracks[SND_MAX];
static MIX_Track *musicTrack;

static MIX_Mixer *mixer;

void initSound(void)
{
    memset(sounds,      0, sizeof(MIX_Audio *) * SND_MAX);
    memset(soundTracks, 0, sizeof(MIX_Track *) * SND_MAX);

    music      = NULL;
    musicTrack = NULL;

    if (!MIX_Init())
    {
        SDL_Log("MIX_Init failed: %s", SDL_GetError());
        return;
    }

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!mixer)
    {
        SDL_Log("MIX_CreateMixerDevice failed: %s", SDL_GetError());
        return;
    }

    for (int i = 0; i < SND_MAX; i++)
    {
        soundTracks[i] = MIX_CreateTrack(mixer);
        if (!soundTracks[i])
            SDL_Log("MIX_CreateTrack[%d] failed: %s", i, SDL_GetError());
    }

    musicTrack = MIX_CreateTrack(mixer);
    if (!musicTrack)
        SDL_Log("MIX_CreateTrack (music) failed: %s", SDL_GetError());

    loadSounds();
}

void loadMusic(char *filename)
{
    if (music != NULL)
    {
        MIX_StopTrack(musicTrack, 0);
        MIX_DestroyAudio(music);
        music = NULL;
    }

    music = MIX_LoadAudio(mixer, filename, false);
    if (!music)
        SDL_Log("MIX_LoadAudio(%s) failed: %s", filename, SDL_GetError());
}

void playMusic(int loop)
{
    if (!music || !musicTrack)
        return;

    MIX_SetTrackAudio(musicTrack, music);

    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, (loop) ? -1 : 0);
    MIX_PlayTrack(musicTrack, props);
    SDL_DestroyProperties(props);
}

void stopMusic(void)
{
    if (musicTrack)
        MIX_StopTrack(musicTrack, 0);
}

void playSound(int id, int channel)
{
    MIX_Track *track = (channel >= 0 && channel < SND_MAX)
                       ? soundTracks[channel]
                       : soundTracks[id];

    if (!track || !sounds[id])
        return;

    MIX_SetTrackAudio(track, sounds[id]);
    MIX_PlayTrack(track, 0);
}

void setSoundVolume(int volume)
{
    float v = SDL_clamp((float)volume / 128.0f, 0.0f, 1.0f);

    for (int i = 0; i < SND_MAX; i++)
        if (soundTracks[i])
            MIX_SetTrackGain(soundTracks[i], v);
}

void setMusicVolume(int volume)
{
    float v = SDL_clamp((float)volume / 128.0f, 0.0f, 1.0f);

    if (musicTrack)
        MIX_SetTrackGain(musicTrack, v);
}

void quitSound(void)
{
    for (int i = 0; i < SND_MAX; i++)
    {
        if (soundTracks[i]) { MIX_DestroyTrack(soundTracks[i]); soundTracks[i] = NULL; }
        if (sounds[i])      { MIX_DestroyAudio(sounds[i]);      sounds[i] = NULL; }
    }

    if (musicTrack) { MIX_DestroyTrack(musicTrack); musicTrack = NULL; }
    if (music)      { MIX_DestroyAudio(music);       music = NULL; }
    if (mixer)      { MIX_DestroyMixer(mixer);        mixer = NULL; }

    MIX_Quit();
}

static void loadSounds(void)
{
    /* Ví dụ:
     * sounds[SND_JUMP] = MIX_LoadAudio(mixer, "audio/jump.wav", false);
     */
}