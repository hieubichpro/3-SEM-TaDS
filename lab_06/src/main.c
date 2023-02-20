#include "tree.h"

int main(void)
{
    FILE *file_in = fopen("input.txt", "r");

    node *binary_tree = NULL;

    int choice = -1;

    node *tree_test = NULL;
    do
    {
        printf("\nУсловие:\n");
        printf("В текстовом файле содержатся слова. Построить ДДП из слова\n");
        printf("файла. Вывести его на экран в виде дерева. \n");
        printf("Определить количество вершин дерева, содержащих слова, начинающиеся на указанную букву.\n");
        printf(" Сравнить время поиска начинающихся на указанную букву слов в дереве и в файле.\n");

        printf("\nМеню:\n");
        printf("[1] - загрузить информацию из файла\n");
        printf("[2] - вывести на экран деревья\n");
        printf("[3] - добавление элемента\n");
        printf("[4] - удаление элемента\n");
        printf("[5] - количество вершин дерева, содержащих слова, начинающиеся на указанную букву\n");
        printf("[6] - Сравнить время поиска\n");

        printf("[0] - выйти из программы\n");
        printf("\nВыберите пункт меню: ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                binary_tree =  read_binary_tree_from_file(file_in);

                if (binary_tree)
                {
                    printf("Бинарное дерево поиска создано!\n");
                }

                break;

            case 2:
                if (binary_tree)
                {
                    FILE *f = fopen("test.gv", "w");

                    btree_export_to_dot(f, "my_tree", binary_tree);

                    fclose(f);

                    system("xdot test.gv");
                }
                else
                {
                    puts("файл не открыт");
                }

                break;

            case 3:
                if (binary_tree)
                {
                    
                    char str[100];
                    printf("\ntype something: ");
                    scanf("%s", str);
                    if (find_node_by_word(binary_tree, str))
                    {
                        printf("this elem does exist in Binary search tree\n");
                    }
                    else
                    {
                        binary_tree = binary_tree_insert(binary_tree, str);

                        printf("Успешно добавлено (%s)", str);

                        FILE *f = fopen("test.gv", "w");

                        btree_export_to_dot(f, "my_tree", binary_tree);

                        fclose(f);

                        system("xdot test.gv");
                    }
                }
                else
                {
                    puts("файл не открыт");
                }

                break;

            case 4:
                if (binary_tree)
                {
                    char word_del[100];
                    printf("Type word you want to delete: ");
                    scanf("%s", word_del);

                    if (!find_node_by_word(binary_tree, word_del))
                    {
                        printf("this word does not exist\n");
                    }
                    else
                    {
                        binary_tree = deleteNode(binary_tree, word_del);

                        FILE *f = fopen("test.gv", "w");

                        btree_export_to_dot(f, "my_tree", binary_tree);

                        fclose(f);

                        system("xdot test.gv");
                    }
                }
                else
                {
                    puts("файл не открыт");
                }
             
            
            case 5:
                if (binary_tree)
                {
                    printf("Введите указанную букву: ");

                    char c = getchar();

                    if (!find_node_by_char(binary_tree, c))
                        printf("IS NOT FOUNDED IN TREE\n");
                    else
                    {
                        FILE *f = fopen("test_search.gv", "w");
                        fprintf(f, "digraph %s {\n", "search_tree");
                        apply_pre(binary_tree, node_to_dot, f);
                        make_color(binary_tree, c, f);
                        fprintf(f, "}\n");
                        fclose(f);
                        system("xdot test_search.gv");
                    }
                }
                break;

             case 6:
                compare_time("test1.txt", 0, tree_test);
                compare_time("test2.txt", 1, tree_test);
                compare_time("test3.txt", 2, tree_test);
                compare_time("test4.txt", 3, tree_test);
                free_tree(tree_test);
                break;

            case 0:
                free_tree(binary_tree);
                break;
            default:
                printf("Пункт меню выбран неверно!\n");
				break;
        }
    } while (choice != 0);
    
    fclose(file_in);
}
