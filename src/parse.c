#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define NC '\0'

typedef enum bs_node_type bs_node_type;

struct bs_simple_node;
typedef struct bs_simple_node bs_simple_node;

struct bs_complex_node;
typedef struct bs_complex_node bs_complex_node;

struct bs_node_link;
typedef struct bs_node_link bs_node_link;

enum bs_node_type { UNASSIGNED = -1, TERMINAL_LINK = 0, SIMPLE_NODE = 1, COMPLEX_NODE = 2 };

struct bs_simple_node {
    char *type;
    char *value;
};

struct bs_complex_node {
    char *type;
    bs_node_link *link;
};

struct bs_node_link {
    bs_node_link *next_link;
    bs_node_type node_type;
    bs_simple_node *simple_node;
    bs_complex_node *complex_node;
};

void init_link(bs_node_link *link) {
    link->next_link = NULL;
    link->node_type = UNASSIGNED;
    link->simple_node = NULL;
    link->complex_node = NULL;
}

void init_term_link(bs_node_link *link) {
    link->next_link = NULL;
    link->node_type = TERMINAL_LINK;
    link->simple_node = NULL;
    link->complex_node = NULL;
}

bs_node_link *file_parse(FILE *file) {
    int depth = -1;
    // max_depth = 10;
    puts("Starting file_parser");
    puts("Beginning allocation of work variables");
    bs_node_link *start_link = malloc(sizeof(bs_node_link));
    init_term_link(start_link);

    bs_node_link **links = calloc(10, sizeof(bs_node_link **));
    int x;
    for (x = 0; x < 10; x++) {
        links[x] = NULL;
    }
    int pos = 0;

    char *content = calloc(120, sizeof(char));

    puts("Starting iteration");
    int c;
    while ( ( c = getc(file) ) != EOF ) {
        if ( c == '\n' ) {
            break;
        }
        if ( c == '{' ) {
            printf("%d\n", depth);
            puts(">> Open node");
            if ( ( depth == -1 ) && ( links[depth + 1] == NULL ) ) {
                puts("Adding to starting node");

                bs_node_link *current_link = start_link;
                bs_node_link *new_link = malloc(sizeof(bs_node_link));
                init_link(new_link);

                current_link->next_link = new_link;
                links[depth + 1] = new_link;
                depth++;
            } else if ( links[depth + 1] == NULL ) {
                puts("New root");

                puts("Adding complex node to link");
                bs_node_link *current_link = links[depth];
                current_link->complex_node = malloc(sizeof(bs_complex_node));
                current_link->node_type = COMPLEX_NODE;

                puts("Complex node type defined");
                int t;
                for (t = 0; t < pos && content[t] != ':'; t++) {
                    //Do nothing
                }
                char *type = realloc(content, t + 1);
                type[t] = NC;
                current_link->complex_node->type = type;
                content = calloc(120, sizeof(char));
                pos = 0;
                printf("Type: %s\n", type);

                puts("Complex node is new link root, adding link");
                bs_node_link *new_link = malloc(sizeof(bs_node_link));
                init_link(new_link);
                links[depth + 1] = new_link;
                depth++;
            } else {
                puts("Elongating chain");
                bs_node_link *current_link = links[depth + 1];
                bs_node_link *new_link = malloc(sizeof(bs_node_link));
                init_link(new_link);
                current_link->next_link = new_link;
                links[depth + 1] = new_link;

                depth++;
            }
            puts("<< Open node");
        } else if ( c == '}' ) {
            printf("%d\n", depth);
            puts(">> Close node");
            bs_node_link *current_link = links[depth];
            if (current_link->node_type != COMPLEX_NODE) {
                current_link->node_type = SIMPLE_NODE;
                bs_simple_node *simple_node = malloc(sizeof(bs_simple_node));
                simple_node->type = calloc(120, sizeof(char *));
                simple_node->value = calloc(120, sizeof(char *));
                current_link->simple_node = simple_node;
                content[pos] = NC;
                char *current_content = realloc(content, (pos + 1) * sizeof(char));

                int pos_max = pos + 1;
                int y = 0;
                int d;

                while ( ( y < pos_max ) && ( ( d = current_content[y] ) != ':' ) ) {
                    simple_node->type[y++] = d;
                }
                simple_node->type[y++] = NC;
                if ( !( y < pos_max ) ) {
                    // TODO: break?
                }
                int i = 0;
                while ( y < pos_max ) {
                    d = current_content[y++];
                    simple_node->value[i++] = d;
                }
                simple_node->value[i] = NC;
                printf("Type: %s, Value: %s\n", simple_node->type, simple_node->value);

                pos = 0;
                content = calloc(120, sizeof(char));

                links[depth + 1] = NULL;
            }
            depth--;
            puts("<< Close node");
        } else if ( depth != -1 ) {
            content[pos] = c;
            pos++;
        }
    }
    return start_link;
}
