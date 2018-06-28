//----------------------------------------------------------------------    
//                     Breakout by Jicehel
//             
//----------------------------------------------------------------------    

#include <Gamebuino-Meta.h>
#include "declarations.h"

int8_t gamestatus = Titlescreen;          // gamestatus the game for tilescreen
boolean isHit[ROWS][COLUMNS];//Array of gamestatuss of the bricks (hit or not)
int8_t type_brick[ROWS][COLUMNS];//Array of type of the bricks of the level (color / bonus)
boolean bounced = false;   // Used to fix double bounce glitch
int8_t lives;              // Amount of lives
int8_t level;              // Current level
int16_t score;             // Score for the game
int16_t brickCount;        // Amount of bricks hit
int8_t WIDTH;
int8_t HEIGHT;
int8_t midPaddle;
uint8_t red;
uint8_t green;
uint8_t blue;
float anim_start_menu;
int   dir_anim_menu;
int8_t defaultBonusBrick;

struct s_balle{float x; float y; float moveX; float moveY; boolean Free; float pas; int BSize;};
struct s_paddle{int px; int py; int pwidth; int pheight; int pspeed;};

s_balle balle;
s_paddle paddle;

const Gamebuino_Meta::Sound_FX LoseLife[] = {
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,184,0,-19,96,11},
};

void Paddle() {
  SerialUSB.println("Do Paddle");
  if (paddle.px < WIDTH - paddle.pwidth) if (gb.buttons.repeat(BUTTON_RIGHT,0)) paddle.px = paddle.px + paddle.pspeed;
  if (paddle.px > 0) if (gb.buttons.repeat(BUTTON_LEFT,0)) paddle.px = paddle.px - paddle.pspeed;
  if (paddle.px < 1) paddle.px = 0;
  if (paddle.px > WIDTH - paddle.pwidth) paddle.px = WIDTH - paddle.pwidth;
  if (paddle.pwidth > paddlewidthmin) {
  gb.display.setColor(WHITE);
  gb.display.drawLine( paddle.px+2 , paddle.py , paddle.px + paddle.pwidth - 2 , paddle.py );
  gb.display.setColor(GRAY);
  gb.display.drawLine( paddle.px+2 , paddle.py + 1 , paddle.px + paddle.pwidth - 2 , paddle.py +1 );
  }
  gb.display.drawImage(paddle.px, paddle.py, Paddle_cg);
  gb.display.drawImage(paddle.px+paddle.pwidth-2, paddle.py, Paddle_cd);
}


void resetlevel() {
  SerialUSB.println("Do resetlevel");
  paddle.pwidth = paddleDefaulSize;
  paddle.px = (WIDTH - paddle.pwidth)/2;
  midPaddle = ((paddle.pwidth - (balle.BSize/2))/2);
  brickCount = 0;
  balle.Free = false;
  balle.y = paddle.py - balle.BSize;
  balle.BSize = 3;
  defaultBonusBrick = level_brick[level-1][50] ;
  for (int8_t row = 0; row < ROWS; row++)
    for (int8_t column = 0; column < COLUMNS; column++) {
      isHit[row][column] = false;
      type_brick[row][column] = level_brick[level-1][row * COLUMNS + column];
    }
}


void newgame() {
  SerialUSB.println("Do newgame"); 
  level = 1;
  lives = 3;
  score = 0;
  resetlevel();
  balle.BSize = 3;
  gamestatus = Running;
  paddle.pheight = 2;
  paddle.pspeed = 3;
}


void ShowInfos() {
  SerialUSB.println("Do ShowInfos");
  gb.display.setCursor(1, 1);
  gb.display.setColor(WHITE);
  gb.display.print("Lev:");
  gb.display.setColor(YELLOW);
  gb.display.print(level);
  gb.display.setCursor(25, 1);
  gb.display.setColor(WHITE);
  gb.display.print("Liv:");
  gb.display.setColor(YELLOW);
  gb.display.print(lives);
  gb.display.setCursor(48, 1);
  gb.display.setColor(WHITE);
  gb.display.print("S:");
  gb.display.setColor(YELLOW);
  gb.display.print(score);
  if (brickCount == ROWS * COLUMNS)  {
    resetlevel();
    level = level + 1;
    if (level > NB_LEVEL) level = 1;
  }
  if (lives <= 0) {
    delay(500);
    gamestatus = Gameover;
  }
}


void setup() {
  gb.begin();
  gb.setFrameRate(40);
  gb.pickRandomSeed();
  SerialUSB.println("Do setup");
  gb.sound.tone(987, 160);
  delay(160);
  gb.sound.tone(1318, 400);
  WIDTH = gb.display.width();
  HEIGHT = gb.display.height();
  paddle.py = 62;
  anim_start_menu = 3; 
  dir_anim_menu = -1;
  initHighscore();
}


void loop() {
  if (!gb.update()) return;
  gb.display.clear();
  SerialUSB.print(gamestatus);
  switch (gamestatus) {
    case 0: // Titlescreen
        gb.display.drawImage(0, 0, StartScreen);
        anim_start_menu = anim_start_menu + dir_anim_menu * 0.10;
        if (anim_start_menu < -0.25) dir_anim_menu = 1;
        if (anim_start_menu > 3.25) dir_anim_menu = -1; 
        gb.lights.drawPixel(0, anim_start_menu, YELLOW);gb.lights.drawPixel(1, anim_start_menu, YELLOW);
        delay(15);
        gb.lights.fill(BLACK);
        if (gb.buttons.pressed(BUTTON_A) || gb.buttons.pressed(BUTTON_B)) newgame();
        break;

    case 1: // Running
          Paddle();
          Ball();
          Brick();
          ShowInfos();
          gb.lights.fill(BLACK);
          if (gb.buttons.pressed(BUTTON_MENU) )  gamestatus = Pause;
          break;

    case 2: // Gameover
        saveHighscore(score);
        break;

    case 3: // Restart 
        anim_start_menu = 3; dir_anim_menu = -1;  
        gamestatus = Titlescreen;
        break;

    case 4: 
        gb.display.setCursor(17, 30);
        gb.display.setFontSize(2);
        gb.display.setColor(RED);
        gb.display.print("PAUSE");
        if (gb.buttons.pressed(BUTTON_A))  gamestatus = Running;
       break;
  }
}
