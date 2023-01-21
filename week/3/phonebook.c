#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

person people[] = {{ name = "Carter", phone = "+1-617-495-1000" }, { name = "David", number = "+1-949-468-2750" }}

int main(void)
{
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "David") == 0)
        {
            printf("Found %s. %s\n", people[i].name, people[i].number);
            return 0;
        }
    }
    printf("Not found.");
    return 1;
}