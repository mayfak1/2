#include "fiodict.h"

mkDict *rand_gen_struct_in_container(size_t n, unsigned int *val)
{

    Point3d **p = malloc(sizeof(Point3d *) * n);
    mkDict *dict = dict_create();

    for (int i = 0; i < n; i++)
    {

        *(p + i) = rand_point();
        rand_atom(val);
        char *key = malloc(50);
        snprintf(key, 50, "key%029zu", (size_t)i);

        dict_put(dict, (void *)key, (void *)(*(p + i)));
    }

    free(p);
    return dict;
}
Point3d **rand_gen_struct(size_t n, unsigned int *val)
{
    Point3d **p = malloc(sizeof(Point3d *) * n);

    for (int i = 0; i < n; i++)
    {

        *(p + i) = rand_point();
        rand_atom(val);
        char *key = malloc(50);
        snprintf(key, 50, "key%029zu", (size_t)i);
    }

    return p;
}
void save_def(FILE *f, mkDict *dt, unsigned int *val)
{
    mkPair *pr = get_head(dt);

    for (int i = 0; i < dt->size; i++)
    {
        fprintf(f, "%s\t:\t%.f\t%.f\t%.f\t\t%d %d %d %d\n",
                (char *)pr->key,

                ((Point3d *)pr->value)->a, ((Point3d *)pr->value)->b, ((Point3d *)pr->value)->c, (*val) & NUMBER_MASK,
                ((*val) & GROUP_MASK) >> GROUP_MASK_SHIFT,
                ((*val) & LINE_MASK) >> LINE_MASK_SHIFT,
                ((*val) & METAL_MASK) >> METAL_MASK_SHIFT);
        pr = pr->next;
    }
}
mkDict *load_def(FILE *f, unsigned int *val, int count_el)
{
    char **words = malloc(sizeof(char *) * count_el);
    if (words == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < count_el; i++)
    {
        words[i] = malloc(sizeof(char) * 300);
    }
    for (int i = 0; i < count_el; i++)
    {
        fgets(*(words + i), 300, f);

        // printf("%s\n", *(words + i));
    }
    mkDict *dict = load_struct_dict(words, count_el, val);
    for (int i = 0; i < count_el; i++)
    {
        free(*(words + i));
    }
    free(words);
    return dict;
}
void list_f(FILE *f, unsigned int *val, int count_el)
{
    char **words = malloc(sizeof(char *) * count_el);
    if (words == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < count_el; i++)
    {
        words[i] = malloc(sizeof(char) * 300);
        if (words[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(words[j]);
            }
            free(words);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < count_el; i++)
    {
        fgets(*(words + i), 300, f);

        printf("%s\n", *(words + i));
    }

    for (int i = 0; i < count_el; i++)
    {
        free(*(words + i));
    }
    free(words);
}
mkDict *load_struct_dict(char **words, int count_el, unsigned int *val)
{
    int **numbers = malloc(sizeof(int *) * count_el);
    for (int i = 0; i < count_el; i++)
    {
        numbers[i] = malloc(sizeof(int) * 7);
    }
    Point3d **p = malloc(sizeof(Point3d *) * count_el);
    mkDict *dict = dict_create();

    for (int i = 0; i < count_el; i++)
    {
        int count = 0;
        const char *line = *(words + i);
        if (line == NULL)
        {
            continue;
        }

        while (*line != '\0' && count < 7)
        {
            if (sscanf(line, "%d", (numbers[i] + count)) == 1)
                count++;

            while (*line != ' ' && *line != '\t' && *line != '\0')
                line++;

            while (*line == ' ' || *line == '\t')
                line++;
        }
        *(p + i) = constructor(numbers[i][0], numbers[i][1], numbers[i][2]);
        char key_buf[300];
        sscanf(*(words + i), "%s", key_buf);
        char *key = strdup(key_buf);

        (*(p + i))->atom = constructor_atom(val, numbers[i][3], numbers[i][4], numbers[i][5], numbers[i][6]);
        dict_put(dict, (void *)key, (void *)*(p + i));
        // print_point(*(p + i), val);
        //  dict_feach(dict);
    }
    free(p);

    for (int i = 0; i < count_el; i++)
    {
        free(numbers[i]);
    }
    free(numbers);
    return dict;
}
void get_element_from_text_file(FILE *f, int index)
{
    char buffer[512];
    int current = 0;

    while (fgets(buffer, sizeof(buffer), f))
    {
        if (current == index)
        {
            printf(" %s", buffer);
            return;
        }
        current++;
    }

    printf("выход за границы\n");
}
void save_bin(FILE *f, mkDict *dt, unsigned int *val)
{
    mkPair *current = get_head(dt);

    for (int i = 0; i < dt->size; i++)
    {
        char *key = (char *)current->key;
        Point3d *pt = (Point3d *)current->value;

        int len = strlen(key);
        fwrite(&len, sizeof(len), 1, f);
        fwrite(key, sizeof(char), len, f);

        fwrite(&(pt->a), sizeof(double), 1, f);
        fwrite(&(pt->b), sizeof(double), 1, f);
        fwrite(&(pt->c), sizeof(double), 1, f);

        fwrite(val, sizeof(unsigned int), 1, f);
        // int res = sizeof(len) + sizeof(char) * len + sizeof(double) * 3 + sizeof(unsigned int);
        // currentintf("%s - %d\n", key, res);
        current = current->next;
    }
}
mkDict *load_bin(FILE *f, unsigned int *val)
{
    mkDict *dt = dict_create();
    while (!feof(f))
    {
        int len;
        if (fread(&len, sizeof(len), 1, f) != 1)
            break;

        char *key = malloc(len + 1);

        fread(key, sizeof(char), len, f);
        key[len] = '\0';

        Point3d *pt = malloc(sizeof(Point3d));
        fread(&(pt->a), sizeof(double), 1, f);
        fread(&(pt->b), sizeof(double), 1, f);
        fread(&(pt->c), sizeof(double), 1, f);

        fread(val, sizeof(unsigned int), 1, f);

        dict_put(dt, (void *)key, (void *)pt);
    }
    return dt;
}

void get_element_from_binar_file(FILE *f, int index, size_t element_size, unsigned int *val, int count_el)
{
    if (index + 1 > count_el)
    {
        printf("out of range");
        return;
    }
    fseek(f, 0, SEEK_SET);
    int position = index * element_size;
    fseek(f, position, SEEK_SET);
    // long n = ftell(f);
    // printf("%ld", n);
    int len;
    if (fread(&len, sizeof(len), 1, f) != 1)
        return;
    char *key = malloc(len + 1);
    fread(key, sizeof(char), len, f);
    key[len] = '\0';
    Point3d *pt = malloc(sizeof(Point3d));
    fread(&(pt->a), sizeof(double), 1, f);
    fread(&(pt->b), sizeof(double), 1, f);
    fread(&(pt->c), sizeof(double), 1, f);

    fread(val, sizeof(unsigned int), 1, f);
    print_point(pt, val);
    free(key);
}
