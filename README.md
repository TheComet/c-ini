# No Bullshit INI parser for C

## Example

```c
#include "c-ini.h"

SECTION("player")
struct player_data
{
    char* name;
    int health;
    float x, y, z;
};

static const char* config =
    "[player]\n"
    "name = \"Bob\"\n"
    "health = 80\n";

int main(void)
{
    struct player_data player;
    player_data_init(&player);  /* Sets default values */
    player_data_parse(&player, "<stdin>", config, strlen(config));
    player_data_fwrite(&player, stdout);
    player_data_deinit(&player);

    return 0;
}
```

Adding ```SECTION("player")``` at the top of the struct makes it visible to the
code generator.

You can optionally add default values and constraints to each member:
```c
SECTION("player")
struct player_data
{
    char* name DEFAULT("Player");
    int health DEFAULT(100) CONSTRAIN(0, 100);
    float x, y, z;
};
```

```DEFAULT()``` modifies the ```_init()``` function to use the custom default values.

```CONSTRAIN()``` adds  checks  to the ```_parse()``` function. If the INI file
contains  a  value  outside  of  the  constrained  range,  then it will  error.

## With CMake

If  you  are  using  a  CMake  project,  simply  ```add_subdirectory()```  this
repository. This will give you a new CMake function:

```cmake
c_ini_generate (
    INPUT
        "struct1.h"
        "struct2.h"
        "struct3.h"
    OUTPUT_HEADER "${PROJECT_BINARY_DIR}/parser.h"
    OUTPUT_SOURCE "${PROJECT_BINARY_DIR}/parser.c")

add_executable (my_application
    "${PROJECT_BINARY_DIR}/parser.h"
    "${PROJECT_BINARY_DIR}/parser.c")
target_link_liraries (my_application PRIVATE c_ini)
```

You can specify as many input files  as  you want. They can be header or source
files. The  code  generator  will scan each input file and create functions for
every struct it finds.

A  header and source file pair is  generated,  which  you  should  add  to  the
executable/library target.

Note that you need to include "c-ini.h" so that macros such  as ```SECTION()```
are  defined. The CMake target ```c_ini``` provides the include  path  to  this
header.

## Use directly

If you are not using CMake, no worries. The code generator consists of a single
C source file, which you can compile with:

```sh
gcc -o c_ini_generator c-ini/c-ini.c
```

Now you can generate  header/source file pairs from a list of input files with:

```sh
./c_ini_generator \
    --input struct1.h struct2.h struct3.h \
    --output-header parser.h \
    --output-source parser.c
```

Finally, you can compile  ```parser.h``` and ```parser.c``` files and link them
with  your application. Note that you will need to ```#include "c-ini.h"```  so
that macros such as ```SECTION()``` are defined:

```sh
gcc -I./c-ini/ -c parser.c -o parser.o
gcc -I./c-ini/ -c main.c -o main.o
gcc -o application parser.o main.o
```

