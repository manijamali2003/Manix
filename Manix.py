'''
    In the name of God, the Compassionate, the Merciful
    Manix (c) 2021 Mani Jamali; Freedom at all
'''
import shutil
import subprocess, os

'''
 In the name of God, the Compassionate, the Merciful
 Manix (c) 2021 Mani Jamali; Freedom at all
 Python based Manix kernel
'''

class Colors:
    Black = '0'
    Blue = '1'
    Green = '2'
    Cyan = '3'
    Red = '4'
    Magenta = '5'
    Brown = '6'
    LightGray = '7'
    Gray = '8'
    LightBlue = '9'
    LightGreen = '10'
    LightCyan = '11'
    LightRed = '12'
    LightMagenta = '13'
    Yellow = '14'
    White = '15'

class Kernel:

    def __init__(self):
        open('kernel.tmp','w')
        pass

    # Print Screen #
    def Print (self,args):
        f = open('kernel.tmp','a')
        f.write(f'Print ("{args}");')
        f.close()

    def PrintChar (self,char):
        f = open('kernel.tmp', 'a')
        f.write(f'PrintChar (\'{char}\');')
        f.close()

    def PrintInt (self,number):
        f = open('kernel.tmp', 'a')
        f.write(f'PrintInt ({str(number)});')
        f.close()

    def PrintLine (self,args):
        f = open('kernel.tmp', 'a')
        f.write(f'PrintLine ("{args}");')
        f.close()

    def Color (self,fgcolor,bgcolor):
        f = open('kernel.tmp', 'a')
        f.write(f'Color ({fgcolor},{bgcolor});')
        f.close()

    def Clear (self):
        f = open('kernel.tmp', 'a')
        f.write(f'Clear ();')
        f.close()

    def Reboot (self):
        f = open('kernel.tmp', 'a')
        f.write(f'Reboot ();')
        f.close()

    def MiniSleep (self,num):
        f = open('kernel.tmp', 'a')
        f.write(f'MiniSleep ({str(num)});')
        f.close()

    def Sleep (self,num):
        f = open('kernel.tmp', 'a')
        f.write(f'Sleep ({str(num)});')
        f.close()

    # Newline #
    def NewLine (self):
        f = open('kernel.tmp', 'a')
        f.write(f'NewLine();')
        f.close()

    # Generate kernel #
    def Generate (self):
        f = open('kernel.tmp','r')
        strv = f.read()
        f.close()

        shutil.copyfile('kernel.c','kernel.c.tmp')

        f = open('kernel.c','w')
        f.write('''#include "manix.h"
void Main(void){Color(0,15);''')
        f.write(strv)
        f.write('}')
        f.close()

        subprocess.call(['nasm', '-f', 'elf32', 'boot.asm', '-o', 'boot.o'])
        subprocess.call(['gcc', '-m32', '-c', 'kernel.c', '-o', 'kernel.o', '--freestanding'])
        subprocess.call(
            ['ld', '-m', 'elf_i386', '-T', 'link.ld', '-o', f'stor/boot/Manix', 'boot.o', 'kernel.o'])
        subprocess.call(['grub-mkrescue', '-o', 'Manix.iso', 'stor/'])
        subprocess.call(['qemu-system-i386', '-cdrom', 'Manix.iso'])

        shutil.copyfile('kernel.c.tmp','kernel.c')

        os.remove('kernel.tmp')
        os.remove('kernel.c.tmp')

