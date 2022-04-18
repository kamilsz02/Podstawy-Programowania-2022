#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N1 9
#define N2 10
#define N 5

void reverse(int t1[], int len){
        for(int i = 0; i < (len / 2); i++){
            int tmp = t1[i];
            t1[i] = t1[len - 1 - i];
            t1[len - 1 - i] = tmp;
        }
    }

int one_two(int t1[], int len1, int t2[], int len2, int res[]){
    int i = 0, j = 0, itr = 0;
    while((i < N1) && (j < N2)){
        if(t1[i] < t2[j]){
            if(itr > 0 && res[itr - 1] != t1[i]){
                res[itr] = t1[i];
                itr++;
            }
            else if(itr == 0){
                res[itr] = t1[i];
                itr++;
            }
            i++;
        }
        else{
            if(itr > 0 && res[itr - 1] != t2[j]){
                res[itr] = t2[j];
                itr++;
            }
            else if(itr == 0){
                res[itr] = t2[j];
                itr++;
            }
            j++;   
        }
    }

    while(i < len1){
        if(res[itr - 1] != t1[i]){
            res[itr] = t1[i];
            itr++;
        }
        i++;
    }

    while(j < len2){
        if(res[itr - 1] != t2[j]){
            res[itr] = t2[j];
            itr++;
        }
        j++;
    }

    return itr;
}

int cmp(const void *e1, const void *e2){
    return (*(int*)e1 - *(int*)e2);
}

void fill(int t1[], int len, int range, int neg){
    if(neg == 1){
        for(int i = 0; i < len; i++){
            t1[i] = random() % 2 == 0 ? (random() % (range + 1)) : ((random() % (range + 1)) * (-1));
        }
    }
    else{
        for(int i = 0; i < len; i++){
            t1[i] = (random() % range) + 1;
        }
    }
}

void show_array(int t1[], int len){
    for(int i = 0; i < len; i++){
        printf("%d%s", t1[i], " ");
    }
    printf("\n");
}

void test_one_two(int t1[], int len1, int t2[], int len2, int res[]){
    qsort(t1, N1, sizeof(int), cmp);
    qsort(t2, N2, sizeof(int), cmp);
    int res_size = one_two(t1, N1, t2, N2, res);

    show_array(res, res_size);
}

void calc_stats(int T[], int len, int range){
    int *stats = malloc((2 * range + 1) * sizeof(int));

    for(int i = 0; i < len; i++){
        stats[T[i] + 10]++;
    }

    for(int i = 0; i < 2 * range + 1; i++){
        printf("%d: %.2f%%\n", i - range, (stats[i] / (float)len) * 100);
    }

    free(stats);
}

int main(){
    
    srandom(time(NULL));
    int t1[N1];
    int t2[N2];
    int res[N1 + N2];
    int T[N];

    fill(t1, N1, 10, 0);
    fill(t2, N2, 10, 0);

    fill(T, N, 10, 1);
    show_array(T, N);
    calc_stats(T, N, 10);

    
    //show_array(t1, N1);
    //show_array(t2, N2);

    //reverse(t1, N1);

    //show_array(t1, N1);

    
    //test_one_two(t1, N1, t2, N2, res);

    return 0;
}