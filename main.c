#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IsInAlfabet(char a, char* alfabet, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(a == alfabet[i])
            return 1;
    }
    return 0;
}


typedef struct {
    int size;
    char *context;
} word;

int NumOfConsonants(word a)
{
        char Consonantsalfabet[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z',
                                    'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};
        int len = sizeof(Consonantsalfabet) / sizeof(Consonantsalfabet[0]);

        int res = 0;
        int temp = 0;

        for(int i = 0; i < a.size; i++)
        {
            if( IsInAlfabet(a.context[i], Consonantsalfabet, len))
            {
                temp++;
                if(temp > res)
                    res = temp;
            }
            else
                temp = 0;
        }

        return res;
}

int ifWordsSimilar(word a, word b)
{
        if(a.size != b.size)
            return 0;

        for(int i = 0; i < a.size; i++)
        {
            if(a.context[i] != b.context[i])
                return 0;
        }
        return 1;
}

int main()
{
    FILE* ptr;
    char ch;

    ptr = fopen("test1.txt", "r");
    if (NULL == ptr)
    {
        printf("file can't be opened \n");
        return 0;
    }

    char alfabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int len = sizeof(alfabet) / sizeof(alfabet[0]);



    word *text;
    text = (word*) malloc(100 * sizeof(word));

    int num_words = 0;
    text[0].size = 0;
    text[0].context = (char*) malloc(31 * sizeof(char));

    do
    {
        ch = fgetc(ptr);
        if(IsInAlfabet(ch, alfabet, len))
        {
            text[num_words].size++;
            text[num_words].context[0] = ch;
            int j = 1;
            ch = fgetc(ptr);
            while(IsInAlfabet(ch, alfabet, len))
            {
                text[num_words].size++;
                text[num_words].context[j] = ch;
                j++;
                ch = fgetc(ptr);
            }
            text[num_words].context[j] = '0';
            num_words++;
            text[num_words].size = 0;
            text[num_words].context = (char*) malloc(31 * sizeof(char));

            if((num_words % 100) == 99)
            {
                text = realloc(text, (num_words+101)* sizeof(word));
            }

        }
    } while (ch != EOF);

    /*for(int i = 0; i < num_words; i++)
    {
        printf("%d) ", i);
        for(int j = 0; j < text[i].size; j++)
        {
            printf("%c", text[i].context[j]);
        }
        printf(" %d", NumOfConsonants(text[i]));
        printf("%c", '\n');
    }*/


    int max = NumOfConsonants(text[0]);
    int *list_max = (int*) malloc(1 * sizeof(int));
    list_max[0] = 0;
    int size_list_max = 1;

    for(int i = 1; i < num_words; i++)
    {

        if(NumOfConsonants(text[i]) > max)
        {
            free(list_max);
            list_max = (int*) malloc(1 * sizeof(int));
            list_max[0] = i;
            size_list_max = 1;
            max = NumOfConsonants(text[i]);
        }
        else
        {
            if(NumOfConsonants(text[i]) == max)
            {
            size_list_max++;
            list_max = realloc(list_max, size_list_max * sizeof(int));
            list_max[size_list_max - 1] = i;
            }
        }
    }

    /*printf("List_max: ");
        for(int h = 0; h < size_list_max; h++)
        {
            printf("%d ", list_max[h]);
        }*/


    printf("Result:\n");

    for(int i = 0; i < size_list_max; i++)
    {
        int check = 1;
        for(int j = 0; j < i; j++)
        {
            if(ifWordsSimilar(text[list_max[i]], text[list_max[j]]))
                check = 0;
        }
        if(check)
        {
            for(int j = 0; j < text[list_max[i]].size; j++)
                {
                    printf("%c", text[list_max[i]].context[j]);
                }
            printf("%c", ' ');
        }

    }



    free(list_max);
    for(int i = 0; i < num_words; i++)
    {
        free(text[i].context);
    }
    free(text);
    /*char *word;
    word = (char*) malloc(100 * sizeof(char));

    if(word == NULL)
    {
        printf("Memory not allocated.\n");
        return 1;
    }
    for(int i = 0; i < 100; i++)
    {
        printf("%c", word[i]);
    }
    printf("%c", '\n');

    free(word);*/








    fclose(ptr);
    return 0;
}
