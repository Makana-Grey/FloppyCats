#pragma once


//Developing
#define DEPLOY -1 // use it only for release build
#define MENU 0
#define SINGLEPLAYER 1
#define MULTIPLAYER 2
#define GAME_SETTINGS 3
#define MODE MULTIPLAYER


//Media props
#define MEDIA_FOLDER "media"
#define ICON_FILE "icon.png"
#define SPRITE_LIST_FILE "sprite_list.png"

//Data props
#define DATA_FOLDER "data"
#define STUNS_LIST_FILE "stuns.ini"

#define GAME_BACKGROUND_COLOR 0x08000dff

#define MENU_META "space paws. united hearts games"
#define MENU_META_SIDE_PART 70.f

#define MENU_BUTTONS_WIDTH 64
#define MENU_BUTTONS_HEIGHT 32
#define MENU_BUTTONS_START_X 608
#define MENU_BUTTONS_SIDE_PART 7.03125f
#define MENU_SWITCH_DURATION 0.15f

#define LOGO_START_X 416
#define LOGO_WIDTH 192
#define LOGO_HEIGHT 96

#define PLAYER_X 0
#define PLAYER_Y 0
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 24
#define PLAYER_SIDE_PART 18.f
#define PLAYER_ANIM_FRAMES_COUNT 2
#define PLAYER_ANIM_DURATION 0.2f
#define PLAYER_COLOR 0xdfc6ffff
#define PLAYER_Y_OFFSET_PART -10.f
#define PLAYER_JUMP_HEIGHT_SIDE_PART 12.f
#define PLAYER_JUMP_SPEED_HEIGHT_PART 0.8f
#define PLAYER_DROP_SPEED_HEIGHT_PART 0.85f
#define PLAYER_ROTATION_UP_BUOND 15.f
#define PLAYER_ROTATION_UP_SPEED 250.f
#define PLAYER_ROTATION_DOWN_BUOND 30.f
#define PLAYER_ROTATION_DOWN_SPEED 70.f
#define PLAYER_CRASH_FACTOR 1.6f

#define OPPONENT_COLOR 0xc2221790
#define OPPONENT_Y_OFFSET_PART 4.f

#define OBSTACLE_X 64
#define OBSTACLE_Y 0
#define OBSTACLE_WIDTH 32
#define OBSTACLE_HEIGHT 32
#define OBSTACLE_SIDE_PART 18.f
#define OBSTACLE_COLOR 0x09ec7eff
#define OBSTACLE_GAP_FACTOR 5.f
#define OBSTACLE_SPEED_PART 0.7f
#define OBSTACLE_COLLIDE_OFFSET_FACTOR 0.25f

#define FLOOR_X 0
#define FLOOR_Y 96
#define FLOOR_WIDTH 32
#define FLOOR_HEIGHT 32
#define FLOOR_COUNT 27
#define FLOOR_SIDE_PART 12.f
#define FLOOR_SPEED_PART 8.f
#define FLOOR_COLLIDE_OFFSET 3

#define GAMEPLAY_ACTION_DURATION 0.f

#define CHARS_D_X 0
#define CHARS_D_Y 64
#define CHARS_L_X 0
#define CHARS_L_Y 80
#define CHARS_WIDTH 16
#define CHARS_HEIGHT 16

#define CHAR_SPEC_Y 48
#define CHAR_COMMA_X 224
#define CHAR_DOT_X 240
#define CHAR_BRACKET_CLOSE_X 256
#define CHAR_BRACKET_OPEN_X 272
#define CHAR_COLON_X 288
#define CHAR_MINUS_X 304
#define CHAR_PLUS_X 320
#define CHAR_DASH_X 336
#define CHAR_EXCL_X 352
#define CHAR_QUEST_X 368
#define CHAR_PERCENT_X 384
#define CHAR_SLASH_X 400


//Kernel props
#define FIXED_DELTA_TIME 0.025f


//Network props
#define API_PROD ""
#define API_URL "http://localhost"
#define API_PORT 3000
#define API_CONNECTION_CONNECT "game/connection/connect"
#define API_CONNECTION_REFRESH "game/connection/refresh"
#define API_PLAYERS_ALL "game/players/all"
#define API_PLAYERS_SEARCH "game/players/search"
#define API_PLAYERS_POINT "game/players/point"
#define API_PLAYER_PLAY "game/player/play"
#define API_PLAYER_PUBLIC "game/player/public"
#define WAIT_FOR_STUN_RESP_S 3