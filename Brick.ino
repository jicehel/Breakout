void Brick() {
  //Bounce off Bricks
  SerialUSB.println("Do Brick");
  for (int8_t row = 0; row < ROWS; row++) {
    for (int8_t column = 0; column < COLUMNS; column++) {
      if (!isHit[row][column] ) {
        // Manage brick and ball collision
        if (type_brick[row][column] > 0) {
          draw_brick(type_brick[row][column], BrickWidth * column, BrickHeight * row + Ytop);
          if (balle.y <= (BrickHeight * (ROWS + 1) + Ytop)) {
            //If a collison has occured
            if (balle.y <= (BrickHeight * (row + 1) + Ytop) && balle.y >= (BrickHeight * row - balle.BSize + Ytop) &&
                balle.x <= (BrickWidth * (column + 1)) && balle.x >= (BrickWidth * column - balle.BSize)) {
              if (type_brick[row][column] > 1) {
                brickCount++;
                score = score + NbPointsBrick;
                isHit[row][column] = true;
              }

             // Test vertical collision
              if (balle.y <= (BrickHeight * row  + Ytop - balle.moveY-1)) {
                 if (balle.moveY > 0) Y_bounce(); 
              } else if (balle.y >= (BrickHeight * (row + 1) - balle.BSize + Ytop - balle.moveY+1))   {
                 if (balle.moveY < 0) Y_bounce();
              }
              //Test hoizontal collision
              else if (balle.x <= (BrickWidth * (column + 1) - balle.moveX+1)) {
                if (balle.moveX < 0) X_bounce();
              } else if (balle.x >= (BrickWidth * column  - balle.BSize - balle.moveX -1)) {
                if (balle.moveX > 0) X_bounce();
              
              }  // -- End horizontal collision
            } // -- End test of collision occurred
          } // -- End test Y (Ball in Brick zone)
        }  // -- End brique > 0
      }  // -- End test isHit
    } // -- End for Column
  } // --End for Row
} // -- End Brick()


// Draw the defined brick
void draw_brick(int8_t BrickType, int8_t XB, int8_t YB) {
  if (BrickType > 10) BrickType = defaultBonusBrick;
  gb.display.drawImage(XB, YB, BR[BrickType - 1]);
}

void Y_bounce() {
  //Only bounce once each ball move
  if (!bounced) {
    balle.moveY = - balle.moveY + random(-1, 1) / 6;
    Bounce();
  }
}

void X_bounce() {
  //Only bounce once each ball move
  if (!bounced) {
    balle.moveX = - balle.moveX + random(-1, 1) / 6;
    Bounce();
  }
}

void Bounce() {
    delay(15);
    bounced = true;
    gb.sound.tone(261, 200);
}

