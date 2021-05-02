/*
    In the name of God, the Compassionate, the Merciful
    Manix (c) 2021 Mani Jamali; Freedom at all
*/

#include "kernel.h"
#include "utils.h"
#include "char.h"
char get_ascii_char(uint8 key_code)
{
  switch(key_code){
    case KEY_A : return 'A';
    case KEY_B : return 'B';
    case KEY_C : return 'C';
    case KEY_D : return 'D';
    case KEY_E : return 'E';
    case KEY_F : return 'F';
    case KEY_G : return 'G';
    case KEY_H : return 'H';
    case KEY_I : return 'I';
    case KEY_J : return 'J';
    case KEY_K : return 'K';
    case KEY_L : return 'L';
    case KEY_M : return 'M';
    case KEY_N : return 'N';
    case KEY_O : return 'O';
    case KEY_P : return 'P';
    case KEY_Q : return 'Q';
    case KEY_R : return 'R';
    case KEY_S : return 'S';
    case KEY_T : return 'T';
    case KEY_U : return 'U';
    case KEY_V : return 'V';
    case KEY_W : return 'W';
    case KEY_X : return 'X';
    case KEY_Y : return 'Y';
    case KEY_Z : return 'Z';
    case KEY_1 : return '1';
    case KEY_2 : return '2';
    case KEY_3 : return '3';
    case KEY_4 : return '4';
    case KEY_5 : return '5';
    case KEY_6 : return '6';
    case KEY_7 : return '7';
    case KEY_8 : return '8';
    case KEY_9 : return '9';
    case KEY_0 : return '0';
    case KEY_MINUS : return '-';
    case KEY_EQUAL : return '=';
    case KEY_SQUARE_OPEN_BRACKET : return '[';
    case KEY_SQUARE_CLOSE_BRACKET : return ']';
    case KEY_SEMICOLON : return ';';
    case KEY_BACKSLASH : return '\\';
    case KEY_COMMA : return ',';
    case KEY_DOT : return '.';
    case KEY_FORESLHASH : return '/';
    case KEY_SPACE : return ' ';
    default : return 0;
  }
}

uint32 strlen(const char* str)
{
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

int atoi(char* s)
{
  int len = strlen(s);
  int i = len - 1;
  int num = 0, pos = 1;
  while(i >= 0){
    num += (s[i] - '0') * pos;
    pos *= 10;
    i--;
  }
  return num;
}

uint32 vga_index;
uint16 cursor_pos = 0, cursor_next_line_index = 1;
static uint32 next_line_index = 1;
uint8 g_fore_color = 15, g_back_color = 0;

// if running on VirtualBox, VMware or on raw machine,
// change CALC_Sleep following to greater than 4
// for qemu it is better for 1
#define CALC_Sleep 1

/*
this is same as we did in our assembly code for vga_PrintChar

vga_PrintChar:
  mov di, word[VGA_INDEX]
  mov al, byte[VGA_CHAR]

  mov ah, byte[VGA_BACK_COLOR]
  sal ah, 4
  or ah, byte[VGA_FORE_COLOR]

  mov [es:di], ax

  ret

*/
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color)
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for(i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 1;
  vga_index = 0;
}

void Clear()
{
  clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  cursor_pos = 0;
  cursor_next_line_index = 1;
}

void Color(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}

uint8 inb(uint16 port)
{
  uint8 data;
  asm volatile("inb %1, %0" : "=a"(data) : "Nd"(port));
  return data;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

void move_cursor(uint16 pos)
{
  outb(0x3D4, 14);
  outb(0x3D5, ((pos >> 8) & 0x00FF));
  outb(0x3D4, 15);
  outb(0x3D5, pos & 0x00FF);
}

void move_cursor_next_line()
{
  cursor_pos = 80 * cursor_next_line_index;
  cursor_next_line_index++;
  move_cursor(cursor_pos);
}

void gotoxy(uint16 x, uint16 y)
{
  vga_index = 80*y;
  vga_index += x;
  if(y > 0){
    cursor_pos = 80 * cursor_next_line_index * y;
    cursor_next_line_index++;
    move_cursor(cursor_pos);
  }
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void MiniSleep(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void Sleep(uint32 timer_count)
{
  MiniSleep(timer_count*0x02FFFFFF);
}

void NewLine()
{
  if(next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
  move_cursor_next_line();
}

void PrintChar(char ch)
{
  vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
  vga_index++;
  move_cursor(++cursor_pos);
}

void Print(char *str)
{
  uint32 index = 0;
  while(str[index]){
    if(str[index] == '\n'){
      NewLine();
      index++;
    }else{
      PrintChar(str[index]);
      index++;
    }
  }
}

void PrintLine (char* value)
{
    Print(value);
    NewLine();
}

void PrintInt(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  Print(str_num);
}

int ReadInt()
{
  char ch = 0;
  char keycode = 0;
  char data[32];
  int index = 0;
  do{
    keycode = get_input_keycode();
    if(keycode == KEY_ENTER){
      data[index] = '\0';
      NewLine();
      break;
    }else{
      ch = get_ascii_char(keycode);
      PrintChar(ch);
      data[index] = ch;
      index++;
    }
    MiniSleep(2000000);
    //Sleep(CALC_Sleep);
  }while(ch > 0);

  return atoi(data);
}

char ReadChar()
{
  char ch = '\0';
  char keycode = 0;
  char data[32];
  int index = 0;
  do{
    keycode = get_input_keycode();
    if(keycode == KEY_ENTER){
      data[index] = '\0';
      NewLine();
      break;
    }else{
      ch = get_ascii_char(keycode);
      PrintChar(ch);
      data[index] = ch;
      index++;
    }
    MiniSleep(2000000);
    //Sleep(CALC_Sleep);
  }while(ch > 0);
  return ch;
}

char getchar()
{
  char keycode = 0;
    //MiniSleep(1000);
  keycode = get_input_keycode();
   // MiniSleep(1000);
  return get_ascii_char(keycode);
}

void Reboot ()
{
    asm ("ljmpw $0xFFFF, $0x0000");
}