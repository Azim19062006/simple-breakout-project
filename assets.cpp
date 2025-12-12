#include "assets.h"

#include "raylib.h"

void load_fonts()
{
    menu_font = LoadFontEx("data/fonts/ARCADECLASSIC.TTF", 256, nullptr, 0);
}

void unload_fonts()
{
    UnloadFont(menu_font);
}

void load_textures()
{
    wall_texture = LoadTexture("data/images/wall.png");
    void_texture = LoadTexture("data/images/void.png");
    block_texture = LoadTexture("data/images/block.png");
    paddle_texture = LoadTexture("data/images/paddle.png");
    ball_sprite = load_sprite("data/images/ball/ball", ".png", 8, true, 10);
}

void unload_textures()
{
    UnloadTexture(wall_texture);
    UnloadTexture(void_texture);
    UnloadTexture(block_texture);
    UnloadTexture(paddle_texture);
    unload_sprite(ball_sprite);
}

void load_sounds()
{
    InitAudioDevice();
    background_music = LoadMusicStream("data/sounds/background.wav");
    win_sound = LoadSound("data/sounds/level_completed.wav");
    lose_sound = LoadSound("data/sounds/lose_of_lives.wav");
    block_hit_sound = LoadSound("data/sounds/block_hit.wav");
    paddle_bounce_sound = LoadSound("data/sounds/paddle_bounce.wav");
    wall_bounce_sound = LoadSound("data/sounds/wall_bounce.wav");
    PlayMusicStream(background_music);
}

void unload_sounds()
{
    UnloadMusicStream(background_music);
    UnloadSound(win_sound);
    UnloadSound(lose_sound);
    UnloadSound(block_hit_sound);
    UnloadSound(paddle_bounce_sound);
    UnloadSound(wall_bounce_sound);
    CloseAudioDevice();
}
