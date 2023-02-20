#include "tree.h"


node *create_node(char info[N])
{
    node *work = malloc(sizeof(node));

    if (work)
    {
        strcpy(work->info, info);
        work->left = NULL;
        work->right = NULL;
    }
    return work;
}

void btree_export_to_dot(FILE *f, const char *tree_name, node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}

void node_to_dot(node *tree, void *param)
{
    FILE *f = param;
    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->info, tree->left->info);
    
    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->info, tree->right->info);
}

void apply_pre(node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

void apply_post(node *tree, ptr_action_t f, void *arg)
{
    apply_post(tree->left, f, arg);
    apply_post(tree->right, f, arg);
    f(tree, arg);
}

node *find_node_by_char(node *tree, char c)
{
    if (tree == NULL)
        return NULL;

    if (c == tree->info[0])
        return tree;
    else if (c < tree->info[0])
        return find_node_by_char(tree->left, c);
    else
        return find_node_by_char(tree->right, c);
}

node *find_node_by_word(node *tree, char *word)
{
    if (tree == NULL)
        return NULL;

    if (!strcmp(word, tree->info))
        return tree;
    else if (strcmp(word, tree->info) < 0)
        return find_node_by_word(tree->left, word);
    else
        return find_node_by_word(tree->right, word);
}

void free_node(node *tree, void *param)
{
    if (tree)
        free(tree);

    tree = NULL;
}

void node_print(node *node, void *param)
{
    const char *fmt = param;

    printf(fmt, node->info);
}

void free_tree(node *tree)
{
    if (tree)
        apply_post(tree, free_node, NULL);
}

node *binary_tree_insert(node *tree, char word[N])
{
    if (tree == NULL)
    {
        node *work = create_node(word);
        return work;
    }
    if (strcmp(word, tree->info) < 0)
        tree->left = binary_tree_insert(tree->left, word);
    else if (strcmp(word, tree->info) > 0)
        tree->right = binary_tree_insert(tree->right, word);

    return tree;
}

void make_color(node *tree, char c, FILE *f)
{
    if (tree == NULL)
        return;
    if (tree->info[0] == c)
        fprintf(f, "%s[color=green]\n", tree->info);
    make_color(tree->left, c, f);
    make_color(tree->right, c, f);
}

node *read_binary_tree_from_file(FILE *f)
{
    rewind(f);

    char word[N];

    node *tree = NULL;

    while (fscanf(f, "%s", word) == 1)
    {
        if (strlen(word))
        {
            tree = binary_tree_insert(tree, word);
        }
    }

    return tree;
}

node *minValueNode(node* root)
{
    node *current = root;
 
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

node *deleteNode(node *root, char *word)
{
    if (root == NULL)
        return root;
 

    if (strcmp(word, root->info) < 0)
        root->left = deleteNode(root->left, word);
 
    else if (strcmp(word, root->info) > 0)
        root->right = deleteNode(root->right, word);
 
    else
    {
        if (root->left == NULL)
        {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        node* temp = minValueNode(root->right);

        strcpy(root->info, temp->info);
 
        root->right = deleteNode(root->right, temp->info);
    }

    return root;
}

int search_in_file(FILE *f, char c)
{
    char buf[N];

    while (fgets(buf, sizeof(buf), f))
        if (buf[0] == c)
        {
            rewind(f);
            return 1;
        }

    return 0;
}

void compare_time(char *name, int lever, node *b_tree)
{
    int reps = 1000;
    struct timeval start, end;
    FILE *f = fopen(name, "r");
    b_tree = read_binary_tree_from_file(f);
    gettimeofday(&start, NULL);
    for (int i = 0; i < reps; i++)
        find_node_by_char(b_tree, 'o');
    gettimeofday(&end, NULL);

    rewind(f);
    double time_tree = ((end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec)) / (double)reps;

    gettimeofday(&start, NULL);
    for (int i = 0; i < reps; i++)
        search_in_file(f, 'o');
    gettimeofday(&end, NULL);

    double time_file = ((end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec)) / (double)reps;
    printf("time search at lever %d in BST node : %lf\n",lever, time_tree);
    printf("time search in file text: %lf\n", time_file);
    printf("use BST beats %lf times\n", (time_file/time_tree));
    printf("\n");
}