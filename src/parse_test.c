#include "parse.h"

int main(void) {
    FILE *file = fopen("schemas.txt", "r");
    file_parse(file);
}
