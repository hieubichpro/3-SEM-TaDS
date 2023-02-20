#include "include/tree_utils.h"

tree_node *create_node(char *val)
{
    tree_node *node = malloc(sizeof(tree_node));

    node->val = malloc(sizeof(char *) * (strlen(val) + 1));
    strcpy(node->val, val);
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

tree_node *insert(tree_node *node, char *val)
{
    if (node == NULL)
    {
        return create_node(val);
    }

    if (strcmp(val, node->val) < 0)
        node->left = insert(node->left, val);
    else if (strcmp(val, node->val) > 0)
        node->right = insert(node->right, val);

    return node;
}

void fill_tree(tree_node **root, FILE *f)
{
    char buffer[STR_SIZE];

    fgets(buffer, STR_SIZE, f);
    if (buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
    }

    *root = insert(*root, buffer);

    while (fgets(buffer, STR_SIZE, f) != NULL)
    {
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        insert(*root, buffer);
    }

    rewind(f);
}

void print_tree(tree_node *root, int space)
{
    if (root == NULL)
    {
        return;
    }

    space += SPACING;

    print_tree(root->right, space);

    printf("\n");
    for (int i = SPACING; i < space; i++)
    {
        printf(" ");
    }
    printf("%s\n", root->val);

    print_tree(root->left, space);
}

void tree_depth(tree_node *root, int *vrtxs, int *cmprs, int depth)
{
    if (!root)
    {
        return;
    }
    (*vrtxs)++;
    (*cmprs) += depth;

    tree_depth(root->right, vrtxs, cmprs, depth + 1);
    tree_depth(root->left, vrtxs, cmprs, depth + 1);
}

void push_back(dynarr_t *arr, tree_node *to_add)
{
    arr->size++;
    if (arr->size >= arr->mem_size)
    {
        arr->mem_size *= 2;
        arr->arr = realloc(arr->arr, arr->mem_size * sizeof(tree_node *));
    }

    for (int i = arr->size; i > 0; i--)
    {
        arr->arr[i] = arr->arr[i - 1];
    }

    arr->arr[0] = to_add;
}

void store_nodes(tree_node *root, dynarr_t *arr)
{
    if (root == NULL)
    {
        return;
    }

    store_nodes(root->left, arr);
    push_back(arr, root);
    store_nodes(root->right, arr);
}

tree_node *build_tree(dynarr_t *arr, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    int mid = (start + end) / 2;
    tree_node *root = arr->arr[mid];

    root->right = build_tree(arr, start, mid - 1);
    root->left = build_tree(arr, mid + 1, end);

    return root;
}

tree_node *balance_tree(tree_node *root, int *unique)
{
    dynarr_t arr;
    arr.mem_size = 8;
    arr.size = 0;
    arr.arr = malloc(sizeof(tree_node *) * arr.mem_size);
    store_nodes(root, &arr);

    int n = arr.size;
    *unique = n;

    tree_node *r = build_tree(&arr, 0, n - 1);

    free(arr.arr);

    return r;
}

void free_tree(tree_node *node)
{
    if (node == NULL)
    {
        return;
    }

    free_tree(node->left);
    free_tree(node->right);

    free(node);
}

void btree_export_to_dot(FILE *f, const char *tree_name, tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}

void node_to_dot(tree_node *tree, void *param)
{
    FILE *f = param;
    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->val, tree->left->val);
    
    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->val, tree->right->val);
}

void apply_pre(tree_node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

int whatheight(tree_node *head)
{
    return head ? head->height : 0;
}

void newheight(tree_node *head)
{
    int hl = whatheight(head->left);
    int hr = whatheight(head->right);
    head->height = ((hl > hr) ? hl : hr) + 1;
}

int factorlr(tree_node *head)
{
    return whatheight(head->right) - whatheight(head->left);
}

tree_node *returnright(tree_node *head)
{
    tree_node *buf = head->left;
    head->left = buf->right;
    buf->right = head;
    newheight(head);
    newheight(buf);

    return buf;
}

tree_node *returnleft(tree_node *head)
{
    tree_node *buf = head->right;
    head->right = buf->left;
    buf->left = head;

    newheight(head);
    newheight(buf);

    return buf;
}

tree_node *balancenode(tree_node *head)
{
    newheight(head);
    if (factorlr(head) == 2)
    {
        if (factorlr(head->right) < 0)
        {
            head->right = returnright(head->right);
        }
        return returnleft(head);
    }
    if (factorlr(head) == -2)
    {
        if (factorlr(head->left) > 0)
        {
            head->left = returnleft(head->left);
        }
        return returnright(head);
    }

    return head;
}

tree_node *insertbalance(tree_node *head, tree_node *node)
{
    if (head == NULL)
    {
        return node;
    }
    
    if (strcmp(node->val, head->val) < 0)
    {
        head->left = insertbalance(head->left, node);
    }
    else if (strcmp(node->val, head->val) > 0)
    {
        head->right = insertbalance(head->right, node);
    }
    else if (strcmp(node->val, head->val) == 0)
    {
        return head;
    }

    return balancenode(head);
}