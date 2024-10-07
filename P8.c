#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h> 
#include <stdlib.h>
#include "our_ints.h" 
#include "our_doubles.h" 
#include "our_strings.h" 

char *first_word(const char *s, char *a)
{ 
    int result = 0;
    int i = 0;
    while(s[i] != ' ' && s[i] != '\0')
    {
        a[result++] = s[i];
        i++;
    }
    a[result] = '\0';
    return a;
}

int first_names(const char **a, int n, const char **b)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        char temp[1000];
        b[result++] = strdup(first_word(a[i], temp));
    }
    return result;
}

void test_first_names(void)
{
    const char *a[10000];
    const char *b[10000];
    int n = strings_get(a);
    int t = first_names(a, n, b);
    strings_print_basic(b, t);
}

int str_cmp_v(const void *p, const void *q)
{
    return strcmp(*(char **)p, *(char **)q);
}

void test_first_names_sorted(void)
{
    const char *a[10000];
    const char *b[10000];
    //const char *b_unique[10000];
    int n = strings_get(a);
    int m = first_names(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    strings_print_basic(b, m);
}

int strings_solitary(const char **a, int n, const char **b)
{
    int result = 0;
    int i = 0;
    while(i < n)
    {
        int z = strings_count_while(a + i, n - i, a[i]);
        if(z == 1)
            b[result++] = a[i];
        i += z;
    }
    return result;
}

void test_solitary(void)
{
    const char *a[10000];
    const char *b[10000];
    const char *b_unique[10000];
    int n = strings_get(a);
    int m = first_names(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    int d = strings_solitary(b, m, b_unique);
    strings_print_basic(b_unique, d);
}

int select_with_solitary_first_word(const char **a, int n, const char **b, int m, const char **c)
{
    int result = 0;
    for(int i = 0; i < n; i++)
        {
            char temp[1000];
            if(strings_bfind(b, m, first_word(a[i], temp)) != -1)
                c[result++] = a[i];
        }
    return result;
}

void test_select_with_solitary_first_word(void)
{
    const char *a[10000];
    const char *b[10000];
    const char *b_unique[10000];
    const char *c[10000];
    int n = strings_get(a);
    int m = first_names(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    int d = strings_solitary(b, m, b_unique);
    int f = select_with_solitary_first_word(a, n, b_unique, d, c);
    strings_print_basic(c, f);
}

char* str_append( char *r, const char *s)
{
    int n = strlen(r);
    for (int i = 0; s[i]; i++)
        r[n++] = s[i];
    r[n] = '\0';
    return r;
}

int nicolau_1(const char **a,int n,const char **b, int m, const char **c)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        char temp[1000];
        char temp2[1000];
        if(strings_bfind(b, m, first_word(a[i], temp)) != -1)
        {
            //c[result++]=a[i];//guarda no array c os nomes completos quando são únicos (porque existem no array b)
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, temp);
            c[result++] = str_dup(temp2);
        }
        else
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, a[i]);
            c[result++] = str_dup(temp2);
        }
        //printf("%d",strings_bfind(b, m, first_word(a[i], temp)));
    }
    return result;  
}

void test_nicolau_1(void)
{
    const char *a[10000];
    const char *b[10000];
    const char *b_unique[10000];
    const char *c[10000];
    int n = strings_get(a);
    int m = first_names(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    //strings_print_basic(b, m);
    int d = strings_solitary(b, m, b_unique);
    int f = nicolau_1(a, n, b_unique, d, c);
    strings_print_basic(c, f);
}

/////////////////////////////////////////////////B

char *first_word2(const char *s, char *a)
{
    int result = 0;
    int i = 0;
    int space = 0;
    while((space != 1 || s[i] != ' ') && s[i] != '\0')
    {
        if (s[i] == ' ')
        {
            space++;
            a[result++] = s[i];
        }
        else
            a[result++] = s[i];
        i++;
    }
    a[result] = '\0';
    return a;
}

int double_name(const char **a, int n, const char **b)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        char temp[1000];
        b[result++] = strdup(first_word2(a[i], temp));
    }
    return result;
}

void test_double_name(void)
{
    const char *a[10000];
    const char *b[10000];
    int n = strings_get(a);
    int t = double_name(a, n, b);
    strings_print_basic(b, t);
}

void test_double_name_sorted(void)
{
    const char *a[10000];
    const char *b[10000];
    //const char *b_unique[10000];
    int n = strings_get(a);
    int m = double_name(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    strings_print_basic(b, m);
}

int strings_solitary2(const char **a, int n, const char **b)
{
    int result = 0;
    int i = 0;
    while(i < n)
    {
        int z = strings_count_while(a + i, n - i, a[i]);
        if(z == 1)
            b[result++] = a[i];
        i += z;
    }
    return result;
}

void test_solitary2(void)
{
    const char *a[10000];
    const char *b[10000];
    const char *b_unique[10000];
    int n = strings_get(a);
    int m = double_name(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    int d = strings_solitary2(b, m, b_unique);
    strings_print_basic(b_unique, d);
}

int nicolau_2(const char **a, int n, const char **b1, const char **b2, int m1, int m2, const char **c)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        char temp[1000];
        char temp2[1000];
        if(strings_bfind(b1, m1, first_word(a[i], temp)) != -1)
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, temp);
            c[result++] = str_dup(temp2);
        }
        else if(strings_bfind(b2, m2, first_word2(a[i], temp)) != -1)
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, temp);
            c[result++] = str_dup(temp2);
        }
        else
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, a[i]);
            c[result++] = str_dup(temp2);
        }
    }
    return result;  
}


void test_nicolau_2(void)
{
    const char *a[10000];
    const char *b[10000];
    const char *bdouble[10000];
    const char *b_double_unique[10000];
    const char *b_unique[10000];
    const char *cfinal[10000];

    int n = strings_get(a);
    int m = first_names(a, n, b);
    int mdouble = double_name(a, n, bdouble);

    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    qsort(bdouble, (size_t)mdouble, sizeof(char*), str_cmp_v);
    //strings_print_basic(b, m);
    //strings_print_basic(bdouble, mdouble);

    int d = strings_solitary(b, m, b_unique);
    int v = strings_solitary2(bdouble, mdouble, b_double_unique);
    int f = nicolau_2(a, n, b_unique, b_double_unique, d, v, cfinal);
    //strings_print_basic(b_double_unique, v);
    strings_print_basic(cfinal, f);
}

//////////////////////////////////C

int last(const char *a)
{
    int result = 0;
    int n = str_len(a);
    for(int i = n - 1; a[i] != ' '; i--)
        result++;
    return n - result;
}

char *first_word3(const char *s, char *a)
{ 
    int result = 0;
    for(int i = 0; s[i]; i++)
    {
        if(s[i] == ' ')
        {
            a[result++] = s[i];
            i = last(s) - 1;
        }
        else   
            a[result++] = s[i];
    }
    a[result] = '\0';
    return a;
}

int pro_name(const char **a, int n, const char **b)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        char temp[1000];
        b[result++] = strdup(first_word3(a[i], temp));
    }
    return result;
}

void test_pro_name(void)
{
    const char *a[10000];
    const char *b[10000];
    int n = strings_get(a);
    int t = pro_name(a, n, b);
    strings_print_basic(b, t);
}

void test_pro_name_sorted(void)
{
    const char *a[10000];
    const char *b[10000];
    //const char *b_unique[10000];
    int n = strings_get(a);
    int m = pro_name(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    strings_print_basic(b, m);
}

void test_solitary3(void)
{
    const char *a[10000];
    const char *b[10000];
    const char *b_unique[10000];
    int n = strings_get(a);
    int m = pro_name(a, n, b);
    //strings_print_basic(b, m);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    int d = strings_solitary2(b, m, b_unique);
    strings_print_basic(b_unique, d);
}

int nicolau(const char **a, int n, const char **b1, const char **b2, const char **b3, int m1, int m2, int m3, const char **c)
{
    int result = 0;
    for(int i = 0; i < n; i++)
    {
        char temp[1000];
        char temp2[1000];
        if(strings_bfind(b1, m1, first_word(a[i], temp)) != -1)
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, temp);
            c[result++] = str_dup(temp2);
        }
        else if(strings_bfind(b2, m2, first_word2(a[i], temp)) != -1)
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, temp);
            c[result++] = str_dup(temp2);
        }
        else if(strings_bfind(b3, m3, first_word3(a[i], temp)) != -1)
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, temp);
            c[result++] = str_dup(temp2);
        }
        else
        {
            str_cpy(temp2, a[i]);
            str_append(temp2, ",");
            str_append(temp2, a[i]);
            c[result++] = str_dup(temp2);
        }
    }
    return result;  
}

void test_nicolau(void)
{
    const char *a[10000];
    const char *b[10000];
    const char *bdouble[10000];
    const char *blast[10000];
    const char *b_double_unique[10000];
    const char *b_unique[10000];
    const char *b_last_unique[10000];
    const char *cfinal[10000];

    int n = strings_get(a);
    int m = first_names(a, n, b);
    int mdouble = double_name(a, n, bdouble);
    int mlast = pro_name(a, n, blast);
    //strings_print_basic(blast, mlast);
    qsort(b, (size_t)m, sizeof(char*), str_cmp_v);
    qsort(bdouble, (size_t)mdouble, sizeof(char*), str_cmp_v);
    qsort(blast, (size_t)mlast, sizeof(char*), str_cmp_v);
    //strings_print_basic(b, m);
    //strings_print_basic(bdouble, mdouble);

    int d = strings_solitary(b, m, b_unique);
    int v = strings_solitary2(bdouble, mdouble, b_double_unique);
    int u = strings_solitary2(blast, mlast, b_last_unique);
    int f = nicolau(a, n, b_unique, b_double_unique, b_last_unique, d, v, u, cfinal);
    //strings_print_basic(b_double_unique, v);
    strings_print_basic(cfinal, f);
}

/////////////////////////////////////D
/*
#define MAX_RACES 21
#define MAX_COLUMNS 100

typedef struct
{
    const char *circuit;
    int placement;
    const char *position;
    int points; 
} StringInt;

StringInt stringint(const char *circuit, int placement, const char *position)
*/
int main(int argc, char **argv) 
{
    int x = 'F';
    if (argc > 1)
        x = *argv[1];
    if (x == 'F')
        test_first_names();
    else if (x == 'G')
       test_first_names_sorted();
    else if (x == 'H')
        test_solitary();
    else if (x == 'I')
        test_select_with_solitary_first_word();
    else if (x == 'A')
        test_nicolau_1();
    else if (x == 'J')
        test_double_name();
    else if (x == 'K')
        test_double_name_sorted();
    else if (x == 'L')
        test_solitary2();
    else if (x == 'B')
        test_nicolau_2();
    else if (x == 'M')
        test_pro_name();
    else if (x == 'N')
        test_pro_name_sorted();
    else if (x == 'O')
        test_solitary3();
    else if (x == 'C')
        test_nicolau();
}