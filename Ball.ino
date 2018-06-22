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
      // gb.sound.play("LoseALife.wav");
      gb.sound.fx(LoseLife);
      delay(300);
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
    if (((ballX + BallSize) >= xPaddle) && (ballX <= xPaddle + paddlewidth) && ((ballY + BallSize) >= YPaddle) && (ballY <= YPaddle + paddleheight)) {
      moveY = -moveY;
      moveX = moveX  - (xPaddle + midPaddle - ballX + random(-1, 1)) / 4; //Applies spin on the ball
      //limit horizontal speed
      if (moveX < -1.5) moveX = -1.5;
      if (moveX > 1.5)  moveX =  1.5;
      gb.sound.tone(200, 200);
    } // end bounce off paddle
    //Reset Bounce
    bounced = false;
  } else {
    //Ball follows paddle (not free)
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
  // gb.display.drawRect(ballX, floor(ballY), BallSize, BallSize);
  gb.display.drawImage(ballX, ballY, BallPicture);
}
