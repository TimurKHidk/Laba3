#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "Header.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");

    if (argc < 2)
    {
        printf("������������� ���������:\n");
        printf("Laba3 --compare <�������_���_�����> <������1> <������2> ...: ���������� �������� ����� � ���������� ������ ����������.\n");
        printf("Laba3 --file <��� �����> <1|2>: ���� ������ � ���������� (1 - ������ ���������, 2 - �������).\n");
        return 0;
    }

    if (strcmp(argv[1], "--file") == 0)
    {
        if (argc != 4)
        {
            printf("�������������: %s --file <��� �����> <1|2>\n", argv[0]);
            return 1;
        }

        const char *filename = argv[2];
        int sort_method = atoi(argv[3]);

        if (sort_method != 1 && sort_method != 2)
        {
            printf("������: ����� ���������� ������ ���� 1 (������ ���������) ��� 2 (�������).\n");
            return 1;
        }

        process_file_input(filename, sort_method);
    }
    else if (strcmp(argv[1], "--compare") == 0)
    {
        if (argc < 3)
        {
            printf("�������������: %s --compare <�������_���_�����> <������1> <������2> ...\n", argv[0]);
            return 1;
        }

        const char *base_filename = argv[2];
        int sizes[argc - 3];
        for (int i = 3; i < argc; i++)
        {
            sizes[i - 3] = atoi(argv[i]);
        }
        int num_sizes = argc - 3;

        compare_sorting_methods(base_filename, sizes, num_sizes);
    }
    else
    {
        printf("����������� ��������. ����������� --file ��� --compare.\n");
        return 1;
    }

    return 0;
}







