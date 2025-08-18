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

Adding ```SECTION("player")``` at the top of the struct adds it to the generator.

You can optionally default values and constraints to each member:
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
    HEADER "${PROJECT_BINARY_DIR}/parser.h"
    SOURCE "${PROJECT_BINARY_DIR}/parser.c")
```

You can specify as many input files as you want. They  can  be header or source
files. The generator  will  scan each input file and create functions for every
struct it finds.

A  header and source file pair is  generated,  which  you  should  add  to  the
executable/library target.
