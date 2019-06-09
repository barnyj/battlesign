#include <stdio.h>

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

bs_node_link *file_parse(FILE *file);
