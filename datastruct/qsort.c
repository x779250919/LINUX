#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdbool.h>
int main()
{
    srand(1);
    int i;
    for (i = 0; i < 10; i++)
    printf("%d, ", rand()%11); 
} 
/* issort */
int issort(void *data, int size, int esize, int (*compare)(const void *key1,
   const void *key2))
{
   char               *a=data;
   void               *key;
   int                i,
                      j;
   /* Allocate storage for the key element. */
   if ((key=(char *)malloc(esize))== NULL)
      return -1;
   /* Repeatedly insert a key element among the sorted elements. */
   for (j=1; j < size; j++)
   {
      memcpy(key, &a[j * esize], esize);
      i=j - 1;
      /* Determine the position at which to insert the key element. */
      while (i >= 0 && compare(&a[i * esize], key) > 0)
      {
         memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
         i--;
      }
      memcpy(&a[(i + 1) * esize], key, esize);
   }
   /* Free the storage allocated for sorting. */
   free(key);
   return 0;
}

/* qksort.c */

/* compare_int */
static int compare_int(const void *int1, const void *int2)
{
    /* Compare two integers (used during median-of-three partitioning). */
    if (*(const int *)int1 > *(const int *)int2)
       return 1;
    else if (*(const int *)int1 < *(const int *)int2)
       return -1;
    else
       return 0;
}
/* partition */
static int partition(void *data, int esize, int i, int k, int (*compare)
   (const void *key1, const void *key2))
{
    char               *a=data;
    void               *pval,
                       *temp;
    int                r[3];
    /* Allocate storage for the partition value and swapping. */
    if ((pval=malloc(esize))== NULL)
       return -1;
    if ((temp=malloc(esize))== NULL)
    {
    free(pval);
       return -1;
    }
    /* Use the median-of-three method to find the partition value. */
    r[0]=(rand() % (k - i + 1))+ i;
    r[1]=(rand() % (k - i + 1))+ i;
    r[2]=(rand() % (k - i + 1))+ i;
    issort(r, 3, sizeof(int), compare_int);
    memcpy(pval, &a[r[1] * esize], esize);
    /* Create two partitions around the partition value. */
    i--;
    k++;
    while (1)
    {
       /* Move left until an element is found in the wrong partition. */
       do
       {
          k--;
       } while (compare(&a[k * esize], pval) > 0);
       /* Move right until an element is found in the wrong partition. */
       do
       {
          i++;
       } while (compare(&a[i * esize], pval) < 0);
       if (i >= k)
       {
          /* Stop partitioning when the left and right counters cross. */
          break;
       }
       else
       {
          /* Swap the elements now under the left and right counters. */
          memcpy(temp, &a[i * esize], esize);
          memcpy(&a[i * esize], &a[k * esize], esize);
          memcpy(&a[k * esize], temp, esize);
       }
    }
    /* Free the storage allocated for partitioning. */
    free(pval);
    free(temp);
    /* Return the position dividing the two partitions. */
    return k;
    }
    /* qksort */
    int qksort(void *data, int size, int esize, int i, int k, int (*compare)
       (const void *key1, const void *key2))
    {
    int                j;
    /* Stop the recursion when it is not possible to partition further. */
    while (i < k)
    {
       /* Determine where to partition the elements. */
       if ((j=partition(data, esize, i, k, compare)) < 0)
          return -1;
       /* Recursively sort the left partition. */
       if (qksort(data, size, esize, i, j, compare) < 0)
          return -1;
       /* Iterate and sort the right partition. */
       i=j + 1;
    }
    return 0;
}
