/*
* 入力を1行ずつ読み、その逆順で出力する。
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "output_line_in_reverse.h"

int main(int argc, char *argv[])
{
    FILE *fp = NULL;

    if (argc == 2) {
        /* 引数の数が2(ファイル名が指定)の場合 */
        fp = fopen(argv[1], "r");
        if (!fp) {
            fprintf(stderr, "error: file do not open\n");
            exit(1);
        }

        do_output(fp);

        if (fclose(fp) < 0) {
            fprintf(stderr, "error: file do not close\n");
            exit(1);
        }
    } else {
        /* 引数の数が2ではない場合 */
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(1);
    }

    return 0;
}

void do_output(FILE *fp)
{
    char **ptr = NULL;
    int i;
    int j;
    int row_counter = 0;
    int allocation_counter = 0;

    while (TRUE) {
        // 行数が足りない場合は新たに確保
        if (row_counter == DEFAULT_ROW_SIZE * allocation_counter) {
            allocation_counter++;
            char **tmp = (char **)xmalloc(ptr, sizeof(char *) * DEFAULT_ROW_SIZE * allocation_counter);
            if (!tmp)
            {
                // 行数確保失敗したら全解放して終了
                for (i = 0; i < row_counter; i++) {
                    free(ptr[i]);
                }
                free(ptr);
                fprintf(stderr, "error: memory allocation");
                exit(1);
            }
            ptr = tmp;
            tmp = NULL;
            for (i = row_counter; i < DEFAULT_ROW_SIZE * allocation_counter; i++) {
                // 新たに確保したcharへのポインタそれぞれにchar型256バイトの領域を固定で確保
                ptr[i] = (char *)xmalloc(NULL, sizeof(char) * DEFAULT_LINE_SIZE);
                if (!ptr[i]) {
                    // 領域確保失敗したら全解放して終了
                    for (j = 0; j < i; j++) {
                        free(ptr[j]);
                    }
                    free(ptr);
                    fprintf(stderr, "error: memory allocation");
                    exit(1);
                }
            }
        }

        if (fgets(ptr[row_counter], DEFAULT_LINE_SIZE, fp) == NULL)
        {
            // 最後まで読み込んだらループを抜ける
            break;
        }

        row_counter++;
    }

    // 逆順に表示
    output_reverse(ptr, row_counter);
}

void output_reverse(char **ptr, int row)
{
    int i;
    for (i = row - 1; i >= 0; i--) {
        printf("%s", ptr[i]);
    }
}

void *xmalloc(void *ptr, int size)
{
    if (ptr == NULL) {
        return malloc(size);
    } else {
        return realloc(ptr, size);
    }
}

