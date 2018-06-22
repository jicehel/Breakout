#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_

#define NUM_HIGHSCORE 5
#define NAMELENGTH 12

#define COLUMNS        16   // Columns of bricks
#define ROWS           10   // Rows of bricks
#define paddlewidth    10
#define paddleheight   2
#define paddlespeed    2
#define BallSize       3
#define Ytop           12
#define BrickWidth     5
#define BrickHeight    2
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
extern bool drawNewHighscore(unsigned int newscore);
extern Image PaddlePicture;
extern Image BallPicture;
extern Image StartScreen;
extern const Gamebuino_Meta::Sound_FX LoseLife[];

#endif _DECLARATIONS_H_
