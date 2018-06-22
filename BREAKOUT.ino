//----------------------------------------------------------------------    
//                     Breakout by Jicehel
//             
//----------------------------------------------------------------------    

#include <Gamebuino-Meta.h>

#define COLUMNS        10   // Columns of bricks
#define ROWS           6    // Rows of bricks
#define paddlewidth    16
#define paddleheight   2
#define paddlespeed    2
#define YPaddle        62
#define BallSize       2
#define Ytop           12
#define BrickWidth     8
#define BrickHeight    4
#define NbPointsBrick  10

int8_t state = 0;          // State the game is in
float moveX;               // Horizontal movement of ball
float moveY;               // Vertical movement of ball
float ballX;               // Ball horizontal position
float ballY;               // Ball vertical position
boolean Free;              // True if the ball is free of the paddle
int8_t xPaddle;            // Horizontal position of paddle
boolean isHit[ROWS][COLUMNS];//Array of states of the bricks (hit or not)
boolean bounced = false;   // Used to fix double bounce glitch
int8_t lives;              // Amount of lives
int8_t level;              // Current level
int16_t score;             // Score for the game
int16_t brickCount;        // Amount of bricks hit
int8_t WIDTH;
int8_t HEIGHT;
int8_t midPaddle;



void Paddle() {
  SerialUSB.println("Do Paddle");
  if (xPaddle < WIDTH - paddlewidth) if (gb.buttons.repeat(BUTTON_RIGHT,0)) xPaddle = xPaddle + paddlespeed;
  if (xPaddle > 0) if (gb.buttons.repeat(BUTTON_LEFT,0)) xPaddle = xPaddle - paddlespeed;
  if (xPaddle < 1) xPaddle = 0;
  if (xPaddle > WIDTH - paddlewidth) xPaddle = WIDTH - paddlewidth;
  gb.display.setColor(GRAY);
  gb.display.drawRect(xPaddle, YPaddle, paddlewidth, 1);
}


void Ball() {
  SerialUSB.println("Do Ball");
  if (Free) {
    //Move ball
    ballX = ballX + moveX;
    ballY = ballY + moveY;
    //Bounce off top edge
    if (ballY <= Ytop) {
      ballY = Ytop;
      moveY = -moveY;
      gb.sound.tone(523, 200);
    }
    //Lose a life if bottom edge hit
    if (ballY >= HEIGHT) {
      gb.sound.tone(175, 200);
      delay(250);
      ballY = YPaddle - BallSize;
      Free = false;
      lives = lives - 1;
    }
    //Bounce off left side
    if (ballX < 1) {
      ballX = 1;
      moveX = -moveX;
      gb.sound.tone(523, 200);
    }
    //Bounce off right side
    if (ballX > WIDTH - BallSize) {
      ballX = WIDTH - BallSize;
      moveX = -moveX;
      gb.sound.tone(523, 200);
    }
    //Bounce off paddle
    if (((ballX + BallSize) >= xPaddle) && (ballX <= xPaddle) + paddlewidth && ((ballY + BallSize) >= YPaddle) && (ballY <= YPaddle)) {
      moveY = -moveY;
      moveX = moveX  - (xPaddle + midPaddle - ballX) / 4; //Applies spin on the ball
      //limit horizontal speed
      if (moveX < -1.5) moveX = -1.5;
      if (moveX > 1.5)  moveX =  1.5;
      gb.sound.tone(200, 200);
    }
    //Reset Bounce
    bounced = false;
  } else {
    //Ball follows paddle
    ballX = xPaddle + midPaddle ;
    ballY = YPaddle - BallSize;
    //Release ball if FIRE pressed
    if (gb.buttons.pressed(BUTTON_A)) {
      Free = true;
      if (gb.buttons.pressed(BUTTON_LEFT) || gb.buttons.pressed(BUTTON_RIGHT)) {
        if (gb.buttons.pressed(BUTTON_LEFT)) moveX = 0.5;
        else moveX = -0.5;
      } else moveX = random(-1, 1) / 2;
      moveY = -1;
    }
  }
  gb.display.setColor(YELLOW);
  gb.display.drawRect(ballX, floor(ballY), BallSize, BallSize);
}


void Brick() {
  //Bounce off Bricks
  SerialUSB.println("Do Brick");
  for (int8_t row = 0; row < ROWS; row++) {
    for (int8_t column = 0; column < COLUMNS; column++) {
      if (!isHit[row][column]) {
        // Manage brick and ball collision
        gb.display.setColor(column + 1 + row);
        gb.display.fillRect(BrickWidth * column, BrickHeight * row + Ytop, BrickWidth, BrickHeight);
        //If A collison has occuRED
        if (ballY <= (BrickHeight * (row + 1) + Ytop) && ballY >= (BrickHeight * row - BallSize + Ytop) &&
            ballX <= (BrickWidth * (column + 1)) && ballX >= (BrickWidth * column - BallSize)) {
          score = score + NbPointsBrick;
          brickCount++;
          isHit[row][column] = true;
          // Manage if the ball have to change of vertical direction to avoid crazy moves
          if (ballY <= (BrickHeight * (row + 1) + Ytop) && ballY >= (BrickHeight * row - BallSize + Ytop) &&
            ballX <= (BrickWidth * (column + 1)) && ballX >= (BrickWidth * column - BallSize)) {
            //Only bounce once each ball move
            if (!bounced) {
              moveX = - moveX;
              moveY = - moveY;
              bounced = true;
              gb.sound.tone(261, 200);
            }
          }  
          else if (ballY <= (BrickHeight * (row + 1) + Ytop) && (ballY >= (BrickHeight * row - BallSize + Ytop))) {
            //Only bounce once each ball move
            if (!bounced) {
              moveY = - moveY;
              bounced = true;
              gb.sound.tone(261, 200);
            }
          }
          //Hoizontal collision
          else if (ballX < (BrickWidth * (column + 1)) && (ballX >= (BrickWidth * column - BallSize))) {
            //Only bounce once brick each ball move
            if (!bounced) {
              moveX = - moveX;
              bounced = true;
              gb.sound.tone(261, 200);
            }
          }
        }
      }
    }
  }
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


void resetGame() {
  SerialUSB.println("Do resetGame");
  resetlevel();
  level = 1;
  lives = 3;
  score = 0;
  state = 1;
}


void Statistics() {
  SerialUSB.println("Do Statistics");
  gb.display.setCursor(1, 1);
  gb.display.setColor(WHITE);
  gb.display.print("Lev:");
  gb.display.setColor(YELLOW);
  gb.display.print(level);
  gb.display.setCursor(28, 1);
  gb.display.setColor(WHITE);
  gb.display.print("Liv:");
  gb.display.setColor(YELLOW);
  gb.display.print(lives);
  gb.display.setCursor(55, 1);
  gb.display.setColor(WHITE);
  gb.display.print("S:");
  gb.display.setColor(YELLOW);
  gb.display.print(score);
  if ((brickCount == ROWS * COLUMNS) && level < 2) {
    resetlevel();
    level = level + 1;
  }
}



void setup() {
  gb.begin();
  gb.setFrameRate(30);
  gb.pickRandomSeed();
  SerialUSB.println("Do setup");
  gb.sound.tone(987, 160);
  delay(160);
  gb.sound.tone(1318, 400);
  WIDTH = gb.display.width();
  HEIGHT = gb.display.height();
  midPaddle = ((paddlewidth - (BallSize/2))/2);
}


void loop() {
  if (!gb.update()) return;
  gb.display.clear();
  SerialUSB.print(state);
  switch (state) {
    case 0: 
        gb.display.setCursor(8, 12);
        gb.display.setFontSize(2);
        gb.display.setColor(YELLOW);
        gb.display.print("BREAKOUT");
        gb.display.setFontSize(1);
        gb.display.setCursor(8, 46);
        gb.display.setColor(WHITE);
        gb.display.print("PRESS <A> or <B>");
        if (gb.buttons.pressed(BUTTON_A) || gb.buttons.pressed(BUTTON_B)) {
          state = 1;
          xPaddle = 50;
        }
        break;

    case 1: 
        if (lives > 0) {
          Paddle();
          Ball();
          Brick();
          Statistics();
        } else {
          delay(3000);
          resetlevel();
          state = 2;
        }
        if (gb.buttons.pressed(BUTTON_MENU) ) {
          state = 4;
        }
        break;

    case 2:
        resetGame();
        break;

    case 4: 
        gb.display.setCursor(17, 30);
        gb.display.setFontSize(2);
        gb.display.setColor(RED);
        gb.display.print("PAUSE");
        if (gb.buttons.pressed(BUTTON_A)) {
          state = 1;
        }
        if (gb.buttons.pressed(BUTTON_MENU)) {
         resetGame();
       }
       break;
  }
}
