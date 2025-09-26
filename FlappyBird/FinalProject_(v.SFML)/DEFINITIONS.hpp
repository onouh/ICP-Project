#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 1024

#define SPLASH_STATE_SHOW_TIME 0.0

#define SPLASH_SCENE_BACKGROUND_FILEPATH "images.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "sky.png"
#define GAME_BACKGROUND_FILEPATH "sky.png"
#define GAME_OVER_BACKGROUND_FILEPATH "sky.png"

#define GAME_TITLE_FILEPATH "title.png"
#define PLAY_BUTTON_FILEPATH "PlayButton.png"

#define PIPE_UP_FILEPATH "PipeUp.png"
#define PIPE_DOWN_FILEPATH "PipeDown.png"

#define LAND_FILEPATH "land.png"

#define BIRD_FRAME_1_FILEPATH "bird-01.png"
#define BIRD_FRAME_2_FILEPATH "bird-02.png"
#define BIRD_FRAME_3_FILEPATH "bird-03.png"
#define BIRD_FRAME_4_FILEPATH "bird-04.png"

#define SCORING_PIPE_FILEPATH "InvisibleScoringPipe.png"

#define FLAPPY_FONT_FILEPATH "flappy-font.ttf"

#define GAME_OVER_TITLE_FILEPATH "Game-Over-Title.png"
#define GAME_OVER_BODY_FILEPATH "Game-Over-Body.png"

#define BRONZE_MEDAL_FILEPATH "Bronze-Medal.png"
#define SILVER_MEDAL_FILEPATH "Silver-Medal.png"
#define GOLD_MEDAL_FILEPATH "Gold-Medal.png"
#define PLATINUM_MEDAL_FILEPATH "Platinum-Medal.png"

#define HIT_SOUND_FILEPATH "Hit.wav"
#define POINT_SOUND_FILEPATH "Point.wav"
#define WING_SOUND_FILEPATH "Wing.wav"

#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FREQUENCY 1.5f

#define BIRD_ANIMATION_DURATION 0.4f

#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3

#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f

#define FLYING_DURATION 0.25f

#define ROTATION_SPEED 100.0f

enum GameStates
{
	eReady,
	ePlaying,
	eGameOver
};

#define FLASH_SPEED 1500.0f

#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f

#define BRONZE_MEDAL_SCORE 0
#define SILVER_MEDAL_SCORE 5
#define GOLD_MEDAL_SCORE 25
#define PLATINUM_MEDAL_SCORE 100
