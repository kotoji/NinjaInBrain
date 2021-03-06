//
//  Config.h
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/23.
//
//

#ifndef NinjaInBrain_Config_h
#define NinjaInBrain_Config_h

#define PNG_PLAYER "ninja.png"
#define PNG_BACKGROUND "background.png"
#define PNG_PLATE_LONG "plate_long.png"
#define PNG_PLATE_MID "plate_mid.png"
#define PNG_PLATE_SHORT "plate_short.png"

#define KEY_HIGHSCORE "highscore"

#define PI 3.1415926f
#define INIT_POS_X 0.15
#define PLATE_SPEED_COEF 0.01f
#define G 0.005f
#define MOVE_TIME_UNIT 1.0f / 30.0f
#define JUMP_SPEED_COEF 0.065f
#define BASE_SCORE 10

// sprintf(args...)のようなもの、const char* を返す
#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()

#endif
