#include <bits/stdc++.h>

using namespace std;

typedef struct
{
    int cnt;
    int pos[2]; // first two positions of duplicated number
}f_t;

int findDuplicate(int* nums, int numsSize) {
    int ans = 0;
    int n = numsSize - 1, i = 0;
    f_t freq[n + 1];
    // initialise:
    for(i = 0; i <= n; ++i)
    {
        freq[i].cnt = 0;
        freq[i].pos[0] = -1;
        freq[i].pos[1] = -1;
    }

    for(i = 0; i <= n; ++i)
    {
        ++freq[nums[i]].cnt;
        if(freq[nums[i]].cnt > 1)
        {
            ans = nums[i];
            i = n + 1; // break for loop
        }
    }
    return ans;
}

void display(int *a, int len)
{
    int i = 0;
    printf("array:\t\t");
    for(i = 0; i < len; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("positions:\t");
    for(i = 1; i <= len; ++i)
    {
        printf("%d ", i);
    }
    printf("\n");
}

f_t findDuplicate2(int* nums, int numsSize) {
    //int ans = 0;
    f_t ans = {0,{0,0}};

    int n = numsSize - 1, i = 0;

    f_t freq[n + 1]; // frequency vector
    f_t *f = NULL; // used to avoid code duplicates

    display(nums, numsSize);

    // initialise:
    for(i = 0; i <= n; ++i)
    {
        f = freq + i;
        f->cnt = 0;
        f->pos[0] = -1;
        f->pos[1] = -1;
    }
    // solve:
    for(i = 0; i <= n; ++i)
    {
        f = freq + nums[i];
        ++f->cnt;

        // save position
        if(f->pos[0] == -1)
        {
            f->pos[0] = i;
        }
        else if(f->pos[1] == -1)
        {
            f->pos[1] = i;
        }
        // check
        if(f->cnt > 1)
        {
            f->cnt = nums[i]; // cnt stores the number instead of its count.
            ans = *f;
            i = n + 1; // break for loop
        }
    }
    return ans;
}

int main()
{
   //int a[] = {3,1,3,4,2};
   int a[] = {1,3,4,2,2};
   int n = sizeof(a) / sizeof(int);
   cout << findDuplicate(a, n) << endl;
   f_t x = findDuplicate2(a, n);
   printf("duplicated number: %d ", x.cnt);
   printf("at positions: %d, %d\n", x.pos[0] + 1, x.pos[1] + 1);

   return 0;
}
