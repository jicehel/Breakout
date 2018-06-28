void Ball() {
  SerialUSB.println("Do Ball");
  if (balle.Free) {
    //Move ball
    balle.x = balle.x + balle.moveX;
    balle.y = balle.y + balle.moveY;
    //Bounce off top edge
    if (balle.y <= Ytop) {
      balle.y = Ytop;
      balle.moveY = -(balle.moveY);
      gb.sound.tone(523, 200);
      if (LightSides) { gb.lights.drawPixel(0, 0, YELLOW);gb.lights.drawPixel(1, 0, YELLOW); }
      delay(15);
    }
    //Lose a life if bottom edge hit
    if (balle.y > paddle.py - balle.BSize) {
      // gb.sound.play("LoseALife.wav");
      gb.lights.fill(RED);
      gb.sound.fx(LoseLife);
      delay(300);
      balle.y = paddle.py - balle.BSize;
      balle.Free = false;
      lives = lives - 1;
    }
    //Bounce off left side
    if (balle.x < 1) {
      balle.x = 1;
      balle.moveX = -(balle.moveX);
      gb.sound.tone(523, 200);
      if (LightSides) { gb.lights.drawPixel(0, 0, YELLOW);gb.lights.drawPixel(0, 1, YELLOW);gb.lights.drawPixel(0, 2, YELLOW);gb.lights.drawPixel(0, 3, YELLOW); }
      delay(15);
    }
    //Bounce off right side
    if (balle.x > WIDTH - balle.BSize) {
      balle.x = WIDTH - balle.BSize;
      balle.moveX = -(balle.moveX);
      gb.sound.tone(523, 200);
      if (LightSides) { gb.lights.drawPixel(1, 0, YELLOW);gb.lights.drawPixel(1, 1, YELLOW);gb.lights.drawPixel(1, 2, YELLOW);gb.lights.drawPixel(1, 3, YELLOW); }
      delay(15);
    }
    //Bounce off paddle
    if (((balle.x + balle.BSize) >= paddle.px) && (balle.x <= paddle.px + paddle.pwidth) && ((balle.y + balle.BSize) >= paddle.py) && (balle.y <= paddle.py + paddle.pheight)) {
      balle.moveY = -balle.moveY;
      balle.moveX = balle.moveX  - (paddle.px + midPaddle - balle.x + random(-1, 1)) / 4; //Applies spin on the ball
      //limit horizontal speed
      if (balle.moveX < -MaxXSpeed) balle.moveX = -MaxXSpeed;
      if (balle.moveX > MaxXSpeed)  balle.moveX =  MaxXSpeed;
      gb.sound.tone(200, 200);
      if (LightSides) { gb.lights.drawPixel(0, 3, YELLOW);gb.lights.drawPixel(1, 3, YELLOW); }
      delay(20);
    } // end bounce off paddle
    //Reset Bounce
    bounced = false;
  } // End of Ball free
    else {
    //Ball follows paddle (not free)
    balle.x = paddle.px + midPaddle ;
    balle.y = paddle.py - balle.BSize;
    //Release ball if FIRE pressed
    if (gb.buttons.pressed(BUTTON_A)) {
      balle.Free = true;
      if (gb.buttons.pressed(BUTTON_LEFT) || gb.buttons.pressed(BUTTON_RIGHT)) {
        if (gb.buttons.pressed(BUTTON_LEFT)) balle.moveX = 0.5;
        else balle.moveX = -0.5;
      } else balle.moveX = random(-1, 1) / 2;
      balle.moveY = -1;
    }
  }
  gb.display.setColor(YELLOW);
  // gb.display.drawRect(ballX, floor(ballY), BallSize, BallSize);
  gb.display.drawImage(balle.x, balle.y, Ball3);
}
