#include "c-ini.h"
#include "example3/player_ini.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

SECTION("sprite")
struct sprite
{
    struct sprite* next IGNORE();
    char*               name;
    int frames          DEFAULT(1);
    int tile_x          DEFAULT(1), tile_y DEFAULT(1);
    char                layer[32];
    float               x, y;
    float scale         DEFAULT(1);
};

SECTION("player")
struct player_data
{
    char*                  name;
    struct sprite* sprites IGNORE();
};

static const char* overlay =
    "[sprite]\n"
    "name = \"body\"\n"

    "[sprite]\n"
    "name = \"head\"\n"
    "scale = 2\n"

    "[client]\n"
    "username = \"Bob\"\n";

static int on_section(struct c_ini_parser* p, void* user_ptr)
{
    struct player_data* player = user_ptr;
    struct sprite*      sprite = malloc(sizeof *sprite);
    sprite_init(sprite);
    sprite->next = player->sprites;
    player->sprites = sprite;
    return sprite_parse_section(sprite, p);
}

int main(int argc, char* argv[])
{
    struct player_data player;
    struct sprite*     sprite;
    (void)argc, (void)argv;

    player_data_init(&player);

    sprite_parse_all("<stdin>", overlay, strlen(overlay), on_section, &player);

    player_data_fwrite(&player, stdout);
    for (sprite = player.sprites; sprite; sprite = sprite->next)
        sprite_fwrite(sprite, stdout);

    player_data_deinit(&player);

    return 0;
}
