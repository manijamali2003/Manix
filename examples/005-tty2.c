/*
    In the name of God, the Compassionate, the Merciful
    Manix (c) 2021 Mani Jamali; Freedom at all
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
    char a = ReadInt ();
    NewLine();
    switch (a){
        case '\0':
            Clear();
            break;
        case 'H':
            PrintLine (" Hello Iam Manix kernel");
            break;
        case 'W':
            PrintLine (" Welcome to Manix!");
            break;
        case 'V':
            PrintLine (" Manix v0.0.3 - 1400/02/12");
            break;
        case 'R':
            Reboot();
            break;
        default:
            PrintLine (" Commands are:\n 1- Hi\n 2- Welcome\n 3- Version\n 4- Reboot");
            break;
    }
  }
}