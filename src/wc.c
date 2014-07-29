/*
    wc.c: print newline, word, and character counts for each file
    Copyright (C) 2014 Joshua Escamilla
    Part of Au, the Alice in Userland project.
    Released under the MIT License.
*/

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// macro to test the equality of two strings
#define streq(x,y) (!strcmp(x,y))

// cumulative line, word, and char counts for all files
static uintmax_t total_lines, total_words, total_chars;

// printing options
static bool print_lines, print_words, print_chars;

// used to make neat columns
static unsigned int number_width;

// format string for printing counts
static const char *number_format;

// number of files successfully opened and read
static unsigned int files_read;

// count how many digits are in a number
static unsigned int ndigits(uintmax_t x)
{
    if (x == 0) {
        return 1;
    } else {
        return (floor(log10(x)) + 1);
    }
}

// compute the optimal number width for the given files
static int compute_number_width(int nfiles, char **files)
{
    uintmax_t total_size = 0;

    for (int i = 0; i < nfiles; i++) {
        if (!streq(files[i], "-")) {
            struct stat st;

            if (stat(files[i], &st) == 0) {
                total_size += st.st_size;
            }
        }
    }

    return ndigits(total_size);
}

// print the number of lines, words, and chars in the file
void print_counts(uintmax_t lines, uintmax_t words, uintmax_t chars,
                  const char *file)
{
    if (print_lines) printf(number_format, number_width, lines);
    if (print_words) printf(number_format, number_width, words);
    if (print_chars) printf(number_format, number_width, chars);

    if (file == NULL) {
        puts("-");
    } else {
        puts(file);
    }
}

// count the number of lines, words, and chars in the file
// if filename is NULL, count from stdin
int count(const char *filename)
{
    FILE *fp;

    if (filename == NULL) {
        fp = stdin;
    } else if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "wc: %s: %s\n", filename, strerror(errno));
        return 1;
    }

    int lines, words, chars;
    lines = words = chars = 0;

    int ch;
    bool in_word = false;

    while ((ch = fgetc(fp)) != EOF) {
        // count lines
        if (ch == '\n') {
            lines++;
        }

        // count words
        if (in_word && !isspace(ch)) {
            in_word = false;
        } else if (!in_word && isspace(ch)) {
            in_word = true;
            words++;
        }

        // count chars
        chars++;
    }

    if (fp != stdin) fclose(fp);
    files_read++;

    print_counts(lines, words, chars, filename);

    total_lines += lines;
    total_words += words;
    total_chars += chars;

    return 0;
}

int main(int argc, char *argv[])
{
    // default option values
    print_lines = print_words = print_chars = false;

    // parse options
    while ((argc > 1) && (argv[1][0] == '-') && (!streq(argv[1], "-"))) {
        if (streq(argv[1], "-l") || streq(argv[1], "--lines")) {
            print_lines = true;
        } else if (streq(argv[1], "-w") || streq(argv[1], "--words")) {
            print_words = true;
        } else if (streq(argv[1], "-c") || streq(argv[1], "--chars")) {
            print_chars = true;
        }

        argv++;
        argc--;
    }

    // if no options were specified, print everything
    if (!(print_lines || print_words || print_chars)) {
        print_lines = print_words = print_chars = true;
    }

    number_width = compute_number_width(argc - 1, argv + 1); // could be clearer
    number_format = "%*" PRIuMAX " ";

    // if no args were given, count from stdin
    if (argc == 1) {
        count(NULL);
    } else {
        for (int i = 1; i < argc; i++) {
            if (streq(argv[i], "-")) {
                count(NULL);
            } else {
                count(argv[i]);
            }
        }
    }

    // print total counts if there was more than one file
    if (files_read > 1) {
        print_counts(total_lines, total_words, total_chars, "total");
    }

    return 0;
}
