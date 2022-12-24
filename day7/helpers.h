#define MAX_LEN 255
#define MAX_FILE_SIZE 100000

typedef struct Node
{
    int size;
    int totalSize; // own size + size of all sub-dirs
    struct Node *parent;
    struct Node *children[30];
    int childrenCount;
    char name[100];

} Node;

int build_tree(Node **nodes);
int get_size(Node *node);
void push(Node **arr, Node *node, int *length);
int extract_size(char *str);
void dealloc(Node **nodes, int length);