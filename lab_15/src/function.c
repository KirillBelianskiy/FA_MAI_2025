#include "../include/function.h"

#include <stdlib.h>
#include <string.h>

int formatting(FILE* inp_file, FILE* outp_file)
{
    char line_buffer[4096];

    while (fgets(line_buffer, sizeof(line_buffer), inp_file) != NULL)
    {
        line_buffer[strcspn(line_buffer, "\n")] = 0;

        if (strlen(line_buffer) == 0)
        {
            continue;
        }

        char* line_words[41];
        int word_count = 0;
        int len_res_str = 0;

        char* word = strtok(line_buffer, " \t");

        while (word != NULL)
        {
            int len_new_word = strlen(word);
            if (len_new_word > 80) return -1;

            if (len_res_str + len_new_word + word_count <= 80)
            {
                line_words[word_count] = malloc(len_new_word + 1);
                strcpy(line_words[word_count], word);
                word_count++;
                len_res_str += len_new_word;
            }
            else
            {
                if (word_count == 1)
                {
                    fprintf(outp_file, "%s\n", line_words[0]);
                    free(line_words[0]);
                }
                else if (word_count > 1)
                {
                    int num_gaps = word_count - 1;
                    int total_spaces = 80 - len_res_str;

                    int base_spaces = total_spaces / num_gaps;
                    int extra_spaces = total_spaces % num_gaps;

                    for (int i = 0; i < word_count; i++)
                    {
                        fprintf(outp_file, "%s", line_words[i]);
                        free(line_words[i]);

                        if (i < word_count - 1)
                        {
                            for (int j = 0; j < base_spaces; j++)
                            {
                                fputc(' ', outp_file);
                            }
                            if (extra_spaces > 0)
                            {
                                fputc(' ', outp_file);
                                extra_spaces--;
                            }
                        }
                    }
                    fprintf(outp_file, "\n");
                }

                word_count = 1;
                len_res_str = len_new_word;
                line_words[0] = malloc(len_new_word + 1);
                strcpy(line_words[0], word);
            }

            word = strtok(NULL, " \t");
        }

        if (word_count == 1)
        {
            fprintf(outp_file, "%s\n", line_words[0]);
            free(line_words[0]);
        }
        else if (word_count > 1)
        {
            int num_gaps = word_count - 1;
            int total_spaces = 80 - len_res_str;

            int base_spaces = total_spaces / num_gaps;
            int extra_spaces = total_spaces % num_gaps;

            for (int i = 0; i < word_count; i++)
            {
                fprintf(outp_file, "%s", line_words[i]);
                free(line_words[i]);

                if (i < word_count - 1)
                {
                    for (int j = 0; j < base_spaces; j++)
                    {
                        fputc(' ', outp_file);
                    }
                    if (extra_spaces > 0)
                    {
                        fputc(' ', outp_file);
                        extra_spaces--;
                    }
                }
            }
            fprintf(outp_file, "\n");
        }
    }

    return 0;
}