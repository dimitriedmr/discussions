#include <bits/stdc++.h>

#define LEN (int)1e5 + 1 // 100001

using namespace std;

typedef struct
{
    int cnt;
    int pos[LEN]; // first two positions of duplicated number
}f_t;

typedef struct Nod
{
    int value;
    Nod* next;
}l_t;

typedef struct
{
    int cnt;
    l_t *pos; // list of numbers
}fl_t;

int fr[LEN];

int findDuplicate(int* nums, int numsSize)
{
    int ans = 0;
    int i = 0;

    for(i = 0; i < numsSize; ++i)
    {
        ++fr[nums[i]];
        if(fr[nums[i]] > 1)
        {
            ans = nums[i];
            i = numsSize; // break loop
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

f_t freq[LEN]; // frequency vector

f_t findDuplicate_with_2positions(int* nums, int numsSize)
{
    // initialize
    f_t ans = {0,{0,0}};

    int i = 0;

    // initialise:
    for(i = 0; i < numsSize; ++i)
    {
        freq[i].cnt = 0;
        freq[i].pos[0] = -1;
        freq[i].pos[1] = -1;
    }
    // solve:
    for(i = 0; i < numsSize; ++i) // iterate over nums
    {

        ++freq[nums[i]].cnt; // increase counter for nums[i]

        // save position
        if(freq[nums[i]].pos[0] == -1) // no position is saved
        {
            freq[nums[i]].pos[0] = i;
        }
        else if(freq[nums[i]].pos[1] == -1) // there's one position saved
        {
            freq[nums[i]].pos[1] = i;
        }
        // check
        if(freq[nums[i]].cnt > 1)
        {
            freq[nums[i]].cnt = nums[i]; // cnt stores the number instead of its count.
            ans = freq[nums[i]];
            i = numsSize; // break for loop
        }
    }
    return ans;
}

f_t findDuplicate_with_positions(int* nums, int numsSize)
{
    f_t ans;
    int i = 0, j = 0;

    // initialise:
    for(i = 0; i < numsSize; ++i)
    {
        freq[i].cnt = 0;
        ans.cnt = 0;
        for(j = 0; j < LEN; ++j)
        {
            freq[i].pos[j] = -1;
            ans.pos[j] = -1;
        }
    }
    // solve:
    for(i = 0; i < numsSize; ++i) // iterate over nums
    {

        ++freq[nums[i]].cnt; // increase counter for nums[i]

        // save position
        j = 0;
        while(freq[nums[i]].pos[j] != -1)
        {
            ++j;
        }
        freq[nums[i]].pos[j] = i;
        // check
        if(freq[nums[i]].cnt > 1)
        {
            freq[nums[i]].cnt = nums[i]; // cnt stores the number instead of its count.
            ans = freq[nums[i]];
            i = numsSize; // break for loop
        }
    }
    return ans;
}

Nod* create_list(int x)
{
   Nod *l = new Nod;
   l->value = x;
   l->next = NULL;
   cout << "create " << endl;
   return l;
}

Nod* add_to_list(int x, Nod* li = NULL) // add at the beginning of the list
{
    Nod* l = create_list(x);
    l->next = li;
    cout << "add " << x << endl;
    return l;
}

void test_list(int *a, int len)
{
   cout << "vector to list: ";

   l_t* li = NULL;
   li = add_to_list(a[0]);

   for(int i = 1; i < len; ++i)
   {
       li = add_to_list(a[i], li);
   }

   while(li != NULL)
   {
       cout << li->value << ' ';
       li = li->next;
   }
   cout << " end\n";
}

fl_t findDuplicate_with_list(int* nums, int numsSize)
{
    fl_t fv[LEN]; // frequency vector

    fl_t ans;
    int i = 0;

    // initialise:
    for(i = 0; i < numsSize; ++i)
    {
        fv[i].cnt = 0;
        fv[i].pos = NULL;
        ans.cnt = 0;
    }
    // solve:

    for(i = 0; i < numsSize; ++i) // iterate over nums
    {

        ++fv[nums[i]].cnt; // increase counter for nums[i]

        // save position

        fv[nums[i]].pos = add_to_list(i, fv[nums[i]].pos);
        // check
        if(fv[nums[i]].cnt > 1)
        {
            fv[nums[i]].cnt = nums[i]; // cnt stores the number instead of its count.
            ans = fv[nums[i]];
            i = numsSize; // break for loop
        }
    }
    return ans;
}

int main()
{
   int a[] = {1,3,4,2,2};
   int n = sizeof(a) / sizeof(int);
   display(a, n);
   cout << "1duplicated number: " << findDuplicate(a, n) << endl;

   f_t x = findDuplicate_with_2positions(a, n);
   printf("2duplicated number: %d ", x.cnt);
   printf("at positions: %d, %d\n", x.pos[0] + 1, x.pos[1] + 1);

   int b[] = {3,1,3,4,2};
   n = sizeof(b) / sizeof(int);
   display(b, n);
   x = findDuplicate_with_positions(b, n);
   printf("3duplicated number: %d at positions:", x.cnt);
   n = 0;
   while(x.pos[n] != -1)
   {
      cout << x.pos[n] << ' ';
      ++n;
   }
   cout << endl;

   int c[] = {3,3,3,3,3};
   n = sizeof(c) / sizeof(int);
   test_list(c, n);
   display(c, n);
   //fl_t xx = findDuplicate_with_list(c, n);
   //printf("3duplicated number: %d ", xx.cnt);

   return 0;
}
