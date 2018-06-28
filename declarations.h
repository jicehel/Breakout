#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_

#define NUM_HIGHSCORE 5
#define NAMELENGTH 12
#define NB_LEVEL 3
#define LightSides 0
#define LightPaddle 0
#define LightBrick 0
#define paddleDefaulSize 10

#define COLUMNS        10   // Columns of bricks
#define ROWS           5    // Rows of bricks
#define paddlewidthmin    4
#define paddlewidthmax    30

#define MaxXSpeed      1.7

#define Ytop           12
#define BrickWidth     8
#define BrickHeight    4
#define NbPointsBrick  10

// Game states
#define Titlescreen   0
#define Running       1
#define Gameover      2
#define Restart       3
#define Pause         4

extern void initHighscore();
extern void drawHighScores();
extern void saveHighscore(unsigned int test_score);
extern void Ball();
extern void Brick();
extern int16_t score;
extern const byte font5x7[];
extern int highscore[NUM_HIGHSCORE];
extern int8_t level_brick[NB_LEVEL][ROWS * COLUMNS + 1];
extern bool drawNewHighscore(unsigned int newscore);
extern Image BallPicture;
extern Image StartScreen;
extern Image Paddle_cg;
extern Image Paddle_cd;
extern Image Ball2;
extern Image Ball3;
extern Image Ball4;
extern Image Ball5;
extern Image BR[12];
extern int8_t defaultBonusBrick;

extern const Gamebuino_Meta::Sound_FX LoseLife[];

#endif _DECLARATIONS_H_
