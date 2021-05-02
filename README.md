# Manix Kernel
### Loader Os based on Manix kernel

### How to compile C Kernel?

1. Edit `kernel.c`
```c
#include "manix.h"

void Main(void){
    Color(BLACK,WHITE);
    PrintLine ("Manix kernel wriiten in C!");
}
```
2. Run
```shell
sh build.sh
```
3. Copy `Manix.iso`

### How to compile Python kernel?

1. Edit `kernel.py` ; this file can be renamed
```python
from Manix import Kernel, Colors

class Main (Kernel):

    def __init__(self):
        self.PrintLine("Manix kernel written in Python!")
        self.Generate()

if __name__ == '__main__':
    main = Main()
```
2. Run `kernel.py`:
```shell
python kernel.py
```
3. Copy `Manix.iso`

### VGA functions

- Print
- PrintLine
- PrintInt
- NewLine
- Clear
- PrintChar
- Color

### System functions

- Reboot

### Colors

- BLACK
- BLUE
- GREEN
- CYAN
- RED
- MAGENTA
- BROWN
- LIGHT_GRAY
- GRAY
- LIGHT_BLUE
- LIGHT_GREEN
- LIGHT_CYAN
- LIGHT_RED
- LIGHT_MAGENTA
- YELLOW
- WHITE