/*
    In the name of God, the Compassionate, the Merciful
    Manix (c) 2021 Mani Jamali; Freedom at all
*/

#include "manix.h"

void Main()
{
  Color(BLACK, WHITE);

  Print ("a = ");
  Sleep(2);
  uint16 a = ReadInt ();

  Print ("b = ");
  Sleep(2);
  uint16 b = ReadInt ();

  Print ("c = a + b => ");
  PrintInt (a+b);

}