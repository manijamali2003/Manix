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
    char a = ReadChar ();
    PrintChar (a);
    NewLine();
    switch (a){
        case '\0':
            Clear();
            break;
        case 'h':
            PrintLine (" Hello Iam Manix kernel");
            break;
        case 'w':
            PrintLine (" Welcome to Manix!");
            break;
        case 'v':
            PrintLine (" Manix v0.0.3 - 1400/02/12");
            break;
        case 'r':
            Reboot();
            break;
        default:
            PrintLine (" Commands are:\n h- Hi\n w- Welcome\n v- Version\n r- Reboot");
            break;
    }
  }
}