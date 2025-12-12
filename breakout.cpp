#include "assets.h"
#include "ball.h"
#include "game.h"
#include "graphics.h"
#include "level.h"
#include "paddle.h"

#include "raylib.h"

void update()
{
    if (game_state == menu_state) {
        if (IsKeyPressed(KEY_ENTER)) {
            game_state = in_game_state;
            current_level_index = 0;
            current_lives = max_lives;
            load_level();
            SetMusicVolume(background_music, 0.2f);
        }
    } else if (game_state == in_game_state) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            game_state = paused_state;
            SetMusicVolume(background_music, 1.0f);
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            move_paddle(-paddle_speed);
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            move_paddle(paddle_speed);
        }
        move_ball();
        if (!is_ball_inside_level()) {
            current_lives--;
            PlaySound(lose_sound);
            if (current_lives <= 0) {
                game_state = game_over_state;
                SetMusicVolume(background_music, 1.0f);
            } else {
                load_level();
            }
        } else if (current_level_blocks == 0) {
            load_level(1);
            PlaySound(win_sound);
        }
    } else if (game_state == paused_state) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            game_state = in_game_state;
            SetMusicVolume(background_music, 0.2f);
        }
    } else if (game_state == victory_state) {
        if (IsKeyPressed(KEY_ENTER)) {
            game_state = menu_state;
            SetMusicVolume(background_music, 1.0f);
        }
    } else if (game_state == game_over_state) {
        if (IsKeyPressed(KEY_ENTER)) {
            game_state = menu_state;
            SetMusicVolume(background_music, 1.0f);
        }
    }
}

void draw()
{
    if (game_state == menu_state) {
        draw_menu();
    } else if (game_state == in_game_state) {
        draw_level();
        draw_paddle();
        draw_ball();
        draw_ui();
    } else if (game_state == paused_state) {
        draw_pause_menu();
    } else if (game_state == victory_state) {
        draw_victory_menu();
    } else if (game_state == game_over_state) {
        draw_game_over();
    }
}

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Breakout");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    init_graphics();
    load_fonts();
    load_textures();
    load_sounds();

    while (!WindowShouldClose()) {
        UpdateMusicStream(background_music);

        BeginDrawing();

        draw();
        update();

        EndDrawing();
    }
    CloseWindow();

    unload_sounds();
    if (current_level.data != nullptr) {
        unload_level();
    }
    unload_textures();
    unload_fonts();

    return 0;
}
