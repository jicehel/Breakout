//---------------------------------------------------------------------------
// Data for the levels
//---------------------------------------------------------------------------

#include "declarations.h"

// COLUMNS: 10   ROW: 5   BRICK: 8 x 4
// Briques
// 0: absence de brique            11: vie 
// 1: brique grise incassable      12: taille paddle ++
// 2: brique bleue foncée          13: taille paddle --
// 3: brique bleu moyen            14: glue
// 4: brique bleu claire           15: accélère balle
// 5: brique verte                 16: ralenti balle
// 6: brique jaune                 17: mini raquète
// 7: brique orange                18: perd une vie
// 8: brique rose                  19: taille de la balle --
// 9: brique marron                20: taille de la balle ++
// 10: brique violette             21: balle d'acier (traverse les briques)
//---------------------------------------------------------------------------

int8_t level_brick[NB_LEVEL][ROWS * COLUMNS + 1] = { 
  
  { 4, 4,  4,  6,  6,  6,  4,  6, 4,  6,
    6, 3,  6,  6,  6,  3,  6,  6, 3,  6,
   20, 3, 17,  3, 17,  3, 12,  7, 3, 12,
    2, 2,  7, 14,  7,  2,  7, 18, 2,  7,
    9, 2,  9,  9,  9,  9,  2,  9, 2,  2, 7 }, 
    
  { 9, 9, 19,  7,  7, 6, 6, 6, 6, 6,
   11, 7,  7, 11, 20, 6, 6, 6, 6, 6,
   18, 7, 16,  7, 18, 6, 6, 6, 6, 6,
    6, 6,  6,  6,  6, 6, 6, 6, 6, 6,
    6, 6,  6,  6,  6, 6, 6, 6, 6, 6, 7 },
    
  { 5, 10,  1,  7,  7,  7,  7, 1, 10,  5,
    5, 10,  1, 16,  7,  7, 16, 1, 10,  5,
    1, 10,  1,  7, 12, 12,  7, 1, 10,  1,
    2, 10,  2,  2,  2,  2,  2, 2, 10,  2,
    2, 10,  2,  2,  2,  2,  2, 2, 10,  2, 7 }};
//---------------------------------------------------------------------------




