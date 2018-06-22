void Brick() {
  //Bounce off Bricks
  SerialUSB.println("Do Brick");
  for (int8_t row = 0; row < ROWS; row++) {
    for (int8_t column = 0; column < COLUMNS; column++) {
      if (!isHit[row][column]) {
        // Manage brick and ball collision
        red = 255 - (row + 2) * 6; green = column * 10; blue = (column + row * 1.5) * 8;
        gb.display.setColor(gb.createColor(red, green, blue));
        gb.display.fillRect(BrickWidth * column, BrickHeight * row + Ytop, BrickWidth, BrickHeight);
        //If A collison has occuRED
        if (ballY <= (BrickHeight * (row + 1) + Ytop) && ballY >= (BrickHeight * row - BallSize + Ytop) &&
            ballX <= (BrickWidth * (column + 1)) && ballX >= (BrickWidth * column - BallSize)) {
          score = score + NbPointsBrick;
          brickCount++;
          isHit[row][column] = true; 
          // Manage if the ball have to change of vertical direction to avoid crazy moves
         if (ballY <= (BrickHeight * (row + 1) + Ytop) && (ballY >= (BrickHeight * row - BallSize + Ytop))) {
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
