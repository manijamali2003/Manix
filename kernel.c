/*
    In the name of God, the Compassionate, the Merciful
    Manix (c) 2021 Mani Jamali; Freedom at all
    C based Manix kernel
*/

#include "manix.h"

void Main()
{
  Color(BLACK, WHITE);

  PrintLine ("  In the name of God, the Compassionate, the Merciful");
  PrintLine ("  Manix (c) 2021 Mani Jamali. Freedom at all");

  for (;;){
    NewLine();
    Print (">> ");
    int a = ReadInt ();
    NewLine();
    switch (a){
        case 0:
            Clear();
            break;
        case 1:
            PrintLine (" Hello Iam Manix kernel");
            break;
        case 2:
            PrintLine (" Welcome to Manix!");
            break;
        case 3:
            PrintLine (" Manix v0.0.3 - 1400/02/12");
            break;
        case 4:
            Reboot();
            break;
        default:
            PrintLine (" Commands are:\n 1- Hi\n 2- Welcome\n 3- Version\n 4- Reboot");
            break;
    }
  }
}