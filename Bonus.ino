void Bonus() {
  for (int8_t i = 0; i < Nb_bonus; i++)  {
    Draw_Bonus(i);
    Test_collision_Bonus(i);
  } // end For
} // end Bonus

void Draw_Bonus(int i) {
      bonus[i].by = bonus[i].by + BonusSpeed;

      switch (bonus[i].btype) {
            case 11 :  // Bonus life
            gb.display.drawImage(bonus[i].bx / Demultiplicateur, bonus[i].by/Demultiplicateur, Bonus_vie);
            break;

            case 18 : // Malus life
            gb.display.drawImage(bonus[i].bx/Demultiplicateur, bonus[i].by/Demultiplicateur, Malus_vie);
            break;
      } // end Switch
      delay(2);
} // end Draw_Bonus


void Test_collision_Bonus(int i) {
// Test if bonus touch the Paddle
    if (((bonus[i].bx/Demultiplicateur + BonusWidth) >= paddle.px) && (bonus[i].bx/Demultiplicateur <= paddle.px + paddle.pwidth) && ((bonus[i].by/Demultiplicateur + BonusHeight) >= paddle.py) && (bonus[i].by/Demultiplicateur <= paddle.py + paddle.pheight)) {
        switch (bonus[i].btype) {
            case 11 :  // Bonus life
            lives++;
            Clear_bonus(i);
            gb.sound.fx(SBonus);
            break;

            case 18 : // Malus life
            lives--;
            Clear_bonus(i);
            gb.sound.fx(SLostlife);
            break;
        } // end Switch
    } // enf If
    if (bonus[i].by > 64*Demultiplicateur) Clear_bonus(i);
 } // end Test_collision_Bonus


 void Clear_bonus(int i){
    for (int8_t temp = 0; temp < Nb_bonus; temp++)  {
        bonus[temp].bx =  bonus[temp+1].bx;
        bonus[temp].by =  bonus[temp+1].by;
        bonus[temp].btype = bonus[temp+1].btype;
    } // end For
    Nb_bonus--;
 } // end Clear_bonus


 void Add_bonus(int Type,int BX,int BY){
  // SerialUSB.print("Add bonus - Nb_bonus = "); 

  // SerialUSB.print(Nb_bonus);
  // SerialUSB.print("  - bonus[Nb_bonus].bx = ");
  bonus[Nb_bonus].bx = BX*Demultiplicateur;
  // SerialUSB.print(bonus[Nb_bonus].bx);
  // SerialUSB.print("  - bonus[Nb_bonus].by = ");
  bonus[Nb_bonus].by = BY*Demultiplicateur;
  // SerialUSB.print(bonus[Nb_bonus].by);
  // SerialUSB.print("  - bonus[Nb_bonus].btype = ");
  bonus[Nb_bonus].btype = Type;
  // SerialUSB.println(bonus[Nb_bonus].btype);
  Nb_bonus++;
 }

