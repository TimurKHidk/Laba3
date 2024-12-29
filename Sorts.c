#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Header.h"

// ������������� �����
void init_stack(Stack *s)
{
    s->top = NULL;
}

// ���������� �������� � ����
void push(Stack *s, int inf)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        perror("������ ��������� ������");
        exit(EXIT_FAILURE);
    }
    new_node->inf = inf;
    new_node->link = s->top;
    s->top = new_node;
}

// �������� �������� �� �����
int pop(Stack *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "������: ���� ����\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = s->top;
    int inf = temp->inf;
    s->top = temp->link;
    free(temp);
    return inf;
}

// �������� �� ������� �����
int is_empty(Stack *s)
{
    return s->top == NULL;
}

// ������ ������ � ���� �� �����
void read_stack(Stack *s)
{
    printf("������� ������������������ ��������� ����� ������ (��� ���������� ����� ������� Enter):\n");
    char input[1024];
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    while (token != NULL)
    {
        int value = atoi(token);
        push(s, value);
        token = strtok(NULL, " ");
    }
}

// ������ ����� � ����
void write_to_file(Stack *s, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "������ �������� ����� %s\n", filename);
        return;
    }

    Stack temp;
    init_stack(&temp);

    while (!is_empty(s))
    {
        int value = pop(s);
        fprintf(file, "%d ", value);
        push(&temp, value);
    }

    while (!is_empty(&temp))
    {
        push(s, pop(&temp));
    }

    fclose(file);
}

// ������ ����� �� �����
void read_stack_from_file(Stack *s, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "������ �������� ����� %s\n", filename);
        exit(1);
    }

    int value;
    while (fscanf(file, "%d", &value) != EOF)
    {
        push(s, value);
    }

    fclose(file);
}

// ���������� ������� ������� ���������
void insertion_sort(Stack *s)
{
    Stack sorted;
    init_stack(&sorted);

    while (!is_empty(s))
    {
        int current = pop(s);

        while (!is_empty(&sorted) && sorted.top->inf > current)
        {
            push(s, pop(&sorted));
        }
        push(&sorted, current);
    }

    while (!is_empty(&sorted))
    {
        push(s, pop(&sorted));
    }
}

// ���������� ��������
void split_stack(Stack *s, Stack *left, Stack *right)
{
    Stack temp;
    init_stack(&temp);

    int count = 0;
    while (!is_empty(s))
    {
        push(&temp, pop(s));
        count++;
    }

    for (int i = 0; i < count / 2; i++)
    {
        push(left, pop(&temp));
    }
    while (!is_empty(&temp))
    {
        push(right, pop(&temp));
    }
}

void merge_stacks(Stack *left, Stack *right, Stack *result)
{
    Stack temp;
    init_stack(&temp);

    while (!is_empty(left) && !is_empty(right))
    {
        if (left->top->inf <= right->top->inf)
        {
            push(&temp, pop(left));
        }
        else
        {
            push(&temp, pop(right));
        }
    }

    while (!is_empty(left))
    {
        push(&temp, pop(left));
    }
    while (!is_empty(right))
    {
        push(&temp, pop(right));
    }

    while (!is_empty(&temp))
    {
        push(result, pop(&temp));
    }
}

void merge_sort(Stack *s)
{
    if (is_empty(s) || s->top->link == NULL)
    {
        return;
    }

    Stack left, right;
    init_stack(&left);
    init_stack(&right);

    split_stack(s, &left, &right);

    merge_sort(&left);
    merge_sort(&right);

    while (!is_empty(s))
    {
        pop(s);
    }

    merge_stacks(&left, &right, s);
}

// ����� ������� ����������
double measure_sort_time(Stack *s, int sort_method)
{
    clock_t start = clock();

    if (sort_method == 1)
    {
        insertion_sort(s);
    }
    else
    {
        merge_sort(s);
    }

    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// ��������� �������� ������
void generate_test_files(const char *base_filename, int sizes[], int num_sizes)
{
    srand(time(NULL));

    for (int i = 0; i < num_sizes; i++)
    {
        int size = sizes[i];
        char filename[256];
        snprintf(filename, sizeof(filename), "%s_%d.txt", base_filename, size);

        FILE *file = fopen(filename, "w");
        if (file == NULL)
        {
            fprintf(stderr, "������ ��� �������� ����� %s\n", filename);
            continue;
        }

        for (int j = 0; j < size; j++)
        {
            int random_number = rand() % 1000;
            fprintf(file, "%d ", random_number);
        }

        fclose(file);
        printf("���� %s ������ � %d ����������.\n", filename, size);
    }
}

// ��������� ������� ����������
void compare_sorting_methods(const char *base_filename, int sizes[], int num_sizes)
{
    generate_test_files(base_filename, sizes, num_sizes);

    for (int i = 0; i < num_sizes; i++)
    {
        char filename[256];
        snprintf(filename, sizeof(filename), "%s_%d.txt", base_filename, sizes[i]);

        printf("\n��������� ���������� ��� �����: %s\n", filename);

        Stack s1, s2;
        init_stack(&s1);
        init_stack(&s2);

        read_stack_from_file(&s1, filename);
        read_stack_from_file(&s2, filename);

        double time_insertion = measure_sort_time(&s1, 1);
        double time_merge = measure_sort_time(&s2, 2);

        printf("������: %d, ������ ���������: %.6f �, �������: %.6f �\n", sizes[i], time_insertion, time_merge);
    }
}

// ����� �����
void print_stack(Stack *s)
{
    Stack temp;
    init_stack(&temp);

    while (!is_empty(s))
    {
        int value = pop(s);
        printf("%d ", value);
        push(&temp, value);
    }
    printf("\n");

    while (!is_empty(&temp))
    {
        push(s, pop(&temp));
    }
}

// ����� �������� ������������������
void print_stack_for_original_order(Stack *s)
{
    Stack temp;
    init_stack(&temp);

    while (!is_empty(s))
    {
        push(&temp, pop(s));
    }

    while (!is_empty(&temp))
    {
        int value = pop(&temp);
        printf("%d ", value);
        push(s, value);
    }
    printf("\n");
}

// ��������� --file
void process_file_input(const char *filename, int sort_method)
{
    Stack s;
    init_stack(&s);

    // ��������� ������ �� �������
    read_stack(&s);

    // ��������� ���� ��� ������
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "������ �������� ����� %s\n", filename);
        return;
    }

    // ������ ��������� ���� ��� ���������� �������
    Stack temp;
    init_stack(&temp);

    // ��������� �������� ���� ��� ������ � ������ � ���� � ���������� �������
    Stack original_stack;
    init_stack(&original_stack);

    // �������� �������� �� ��������� ����� �� ��������� ���� ��� ����������� �������
    while (!is_empty(&s))
    {
        int value = pop(&s);
        push(&temp, value);        // ��������� ���� ��� ��������������
        push(&original_stack, value); // ����� ��� ��������� �������
    }

    // ��������������� �������� ���� �� ����������
    while (!is_empty(&temp))
    {
        push(&s, pop(&temp));
    }

    // ���������� � ������� �������� ������������������
    printf("�������� ������������������: ");
    fprintf(file, "�������� ������������������: ");
    while (!is_empty(&original_stack))
    {
        int value = pop(&original_stack);
        printf("%d ", value);
        fprintf(file, "%d ", value);
    }
    printf("\n");
    fprintf(file, "\n");

    // ��������� ����������
    if (sort_method == 1)
    {
        insertion_sort(&s);
        printf("���������� ������� ������� ���������: ");
        fprintf(file, "���������� ������� ������� ���������: ");
    }
    else if (sort_method == 2)
    {
        merge_sort(&s);
        printf("���������� ������� �������: ");
        fprintf(file, "���������� ������� �������: ");
    }

    // ���������� � ������� ��������������� ������������������
    while (!is_empty(&s))
    {
        int value = pop(&s);
        printf("%d ", value);
        fprintf(file, "%d ", value);
        push(&temp, value); // ��������� ������� � ������ �������������
    }
    printf("\n");
    fprintf(file, "\n");

    // ��������������� ���� ����� ���������� (���� ����� ��� ����������� �������������)
    while (!is_empty(&temp))
    {
        push(&s, pop(&temp));
    }

    fclose(file); // ��������� ����
    printf("������ �������� � ���� %s\n", filename);
}














