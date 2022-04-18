#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_DIGRAMS (LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR)

int count[MAX_DIGRAMS] = {0};

// function to be used as comparator to qsort (compares counters and thes sorts
// alphabetically when equal)
int cmp(const void *a, const void *b)
{
    int va = *(int *)a;
    int vb = *(int *)b;
    if (count[va] == count[vb])
        return va - vb; // sort alphabetically if counts equal
    return count[vb] - count[va];
}

// function to be used as comparator to qsort for digrams (compares counters and
// thes sorts alphabetically when equal)
int cmp_di(const void *a, const void *b)
{
    int va = *(int *)a;
    int vb = *(int *)b;
    // sort according to second char if counts and the first char equal
    if (count[va] == count[vb] && va / MAX_CHARS == vb / MAX_CHARS)
        return va % MAX_CHARS - vb % MAX_CHARS;
    // sort according to first char if counts equal
    if (count[va] == count[vb])
        return va / MAX_CHARS - vb / MAX_CHARS;
    return count[vb] - count[va];
}

#define MAX_LINE 128

int read_line()
{
    char line[MAX_LINE];
    int n;

    fgets(line, MAX_LINE, stdin); // to get the whole line
    sscanf(line, "%d", &n);
    return n;
}

// count how many times each character from [FIRST_CHAR, LAST_CHAR) occurs
// in the text read from stdin. Sort chars according to their respective
// cardinalities (decreasing order). Set n_char and cnt to the char_no - th char
// in the sorted list and its cardinality respectively
void char_count(int char_no, int *n_char, int *cnt)
{
    int res[128] = {0};
    char* buffer = calloc(MAX_LINE, sizeof(char));
    size_t size = 0;
    while(1){
        int val = getline(&buffer, &size, stdin);
        if(val == -1){
            break;
        }
        else{
            for(int i = 0; i < size; i++){
                if((int)(buffer[i]) >= FIRST_CHAR && (int)(buffer[i]) < LAST_CHAR){
                    res[((int)buffer[i])]++;
                }
            }
        }
    }
    int mx = -1;
    int mx_index = 0;
    while(char_no > 1){
        mx = -1;
        for(int i = 0; i < 128; i++){
            if(res[i] > mx){
                mx = res[i];
                mx_index = i;
            }
        }
        res[mx_index] = 0;
        char_no--;
    }

    /*for(int i = 0; i < 128; i++){
        if(res[i] > mx){
            mx = res[i];
            mx_index = i;
        }
    }*/

    *n_char = mx_index;
    *cnt = res[mx_index];
}

// count how many times each digram (a pair of characters, from [FIRST_CHAR,
// LAST_CHAR) each) occurs in the text read from stdin. Sort digrams according
// to their respective cardinalities (decreasing order). Set digram[0] and
// digram[1] to the first and the second char in the digram_no - th digram_char
// in the sorted list. Set digram[2] to its cardinality.
void digram_count(int digram_no, int digram[])
{
}

int main(void)
{
    int to_do;
    int nl, nw, nc, char_no, n_char, cnt;
    int line_comment_counter, block_comment_counter;
    int digram[3];

    to_do = read_line();
    switch (to_do)
    {

    case 2: // char_count()
        char_no = read_line();
        char_count(char_no, &n_char, &cnt);
        printf("%c %d\n", n_char, cnt);
        break;
    case 3: // digram_count()
        char_no = read_line();
        digram_count(char_no, digram);
        printf("%c%c %d\n", digram[0], digram[1], digram[2]);
        break;
    default:
        printf("NOTHING TO DO FOR %d\n", to_do);
        break;
    }
    return 0;
}
