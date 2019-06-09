#include <stdio.h>

char *_UNDEFINED_BS_CHARACTER = "!^UNDEFINED^!";

typedef struct GAMESTATE {
  char *player;
  char *enemy;
} bs_gamestate;

bs_gamestate init_gamestate() {
  bs_gamestate new_gamestate = {_UNDEFINED_BS_CHARACTER, _UNDEFINED_BS_CHARACTER};
  return new_gamestate;
}

void start_message() {
  puts("Welcome to battlesign.");
}

void end_message() {
  puts("Finished. Exiting battlesign.");
}

void game_init(bs_gamestate *gamestate) {
  puts("Type name of player:");
  char buf[100];
  fgets(buf, 100, stdin);
  printf("Name of player: %s\n", buf);
  gamestate->player = buf;
}

int main(void) {
  start_message();
  bs_gamestate gamestate = init_gamestate();
  game_init(&gamestate);
  end_message();
  return 0;
}
