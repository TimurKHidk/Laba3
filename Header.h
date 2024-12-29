#ifndef HEADER_H
#define HEADER_H

typedef struct Node
{
    int inf;
    struct Node *link;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

void init_stack(Stack *s);
void push(Stack *s, int inf);
int pop(Stack *s);
int is_empty(Stack *s);

void read_stack(Stack *s);
void write_to_file(Stack *s, const char *filename);
void read_stack_from_file(Stack *s, const char *filename);

void insertion_sort(Stack *s);
void merge_sort(Stack *s);

double measure_sort_time(Stack *s, int sort_method);

void generate_test_files(const char *base_filename, int sizes[], int num_sizes);
void compare_sorting_methods(const char *base_filename, int sizes[], int num_sizes);

void process_file_input(const char *filename, int sort_method);
void print_stack(Stack *s);
void print_stack_for_original_order(Stack *s);


#endif



