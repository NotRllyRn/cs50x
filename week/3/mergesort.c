#include <stdio.h>

int numbers[] = {5, 2, 7, 4, 1, 6, 3, 0};

void sort(int start, int end, int sorted[])
{
    printf("%i %i\n", start, end);
    if (start == end)
    {
        sorted[start] = numbers[start];
        return;
    }

    int half_point = (end - start) / 2;
    int right_index = half_point + 1;

    int left_half[right_index];
    sort(start, half_point, left_half);
    int right_half[right_index];
    sort(right_index, end, right_half);

    int left = 0, right = 0;
    while (1)
    {
        if (left_half[left] > right_half[right])
        {
            sorted[left + right] = left_half[left];
            if (left + 1 != right_index)
            {
                left++;
            }
        }
        else
        {
            sorted[left + right] = right_half[right];
            if (right + 1 != right_index)
            {
                right++;
            }
        }

        if (right + 1 == right_index && left + 1 == right_index)
        {
            break;
        }
    }
}

int main(void)
{
    int sorted[8];
    sort(0, 7, sorted);
    for (int i = 0; i < 8; i++)
    {
        printf("%i\n", sorted[i]);
    }
}