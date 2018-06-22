//----------------------------------------------------------------------    
//                     Breakout by Jicehel
//             
//----------------------------------------------------------------------    

#include <Gamebuino-Meta.h>
#include "declarations.h"

int8_t gamestatus = Titlescreen;          // gamestatus the game for tilescreen
float moveX;               // Horizontal movement of ball
float moveY;               // Vertical movement of ball
float ballX;               // Ball horizontal position
float ballY;               // Ball vertical position
boolean Free;              // True if the ball is free of the paddle
int8_t xPaddle;            // Horizontal position of the paddle
int8_t YPaddle;            // Vertical position of the paddle
boolean isHit[ROWS][COLUMNS];//Array of gamestatuss of the bricks (hit or not)
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

const Gamebuino_Meta::Sound_FX LoseLife[] = {
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,184,0,-19,96,11},
};

void Paddle() {
  SerialUSB.println("Do Paddle");
  if (xPaddle < WIDTH - paddlewidth) if (gb.buttons.repeat(BUTTON_RIGHT,0)) xPaddle = xPaddle + paddlespeed;
  if (xPaddle > 0) if (gb.buttons.repeat(BUTTON_LEFT,0)) xPaddle = xPaddle - paddlespeed;
  if (xPaddle < 1) xPaddle = 0;
  if (xPaddle > WIDTH - paddlewidth) xPaddle = WIDTH - paddlewidth;
  gb.display.setColor(GRAY);
  // gb.display.drawRect(xPaddle, YPaddle, paddlewidth, YPaddle + paddleheight -1);
  gb.display.drawImage(xPaddle, YPaddle, PaddlePicture);
}


void resetlevel() {
  SerialUSB.println("Do resetlevel");
  xPaddle = 50;
  brickCount = 0;
  Free = false;
  ballY = 60;
  for (int8_t row = 0; row < ROWS; row++)
    for (int8_t column = 0; column < COLUMNS; column++)
      isHit[row][column] = false;
}


void newgame() {
  SerialUSB.println("Do newgame"); 
  level = 1;
  lives = 3;
  score = 0;
  resetlevel();
  gamestatus = Running;
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
  YPaddle = 62;
  midPaddle = ((paddlewidth - (BallSize/2))/2);
  initHighscore();
}


void loop() {
  if (!gb.update()) return;
  gb.display.clear();
  SerialUSB.print(gamestatus);
  switch (gamestatus) {
    case 0: // Titlescreen
        gb.display.drawImage(0, 0, StartScreen);
        if (gb.buttons.pressed(BUTTON_A) || gb.buttons.pressed(BUTTON_B)) newgame();
        break;

    case 1: // Running
          Paddle();
          Ball();
          Brick();
          ShowInfos();
          if (gb.buttons.pressed(BUTTON_MENU) )  gamestatus = Pause;
          break;

    case 2: // Gameover
        saveHighscore(score);
        break;

    case 3: // Restart    
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
