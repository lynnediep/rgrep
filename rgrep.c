//
//  rgrep.c
//  Project_1
//
//  Created by Lynne Diep on 2/21/16.
//  Copyright © 2016 Lynne Diep. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
    // Implement if desire
    
    return 0;
}

/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
    int l_i = 0, p_i = 0; //i = index
    int l_l = strlen(line), p_l = strlen(pattern); //l = length

    while (pattern[p_i] != '\0' && line[l_i] != '\0') { 
       if (pattern[p_i] == '.') {
            l_i++;
            p_i++;
                if (p_i == p_l) {
                   return 1;
                }
       }
       else if (pattern[p_i] == '+') {
                while(line[l_i] == pattern[p_i-1]) {
                    l_i++;
                }
                p_i++;
            if (pattern[p_i] == line[l_l]) {
                return 1;
            }
       }
       else if (pattern[p_i] == '?') {
            while(line[l_i] != pattern[p_i]) {
                    l_i++;
                }
                l_i++;
                p_i++;
            if(pattern[p_i] == line[l_l]) {
                return 1;
            }
        }
        else if (line[l_i] == pattern[p_i]) {
            p_i++;
            l_i++;
            if (pattern[p_i] == '\0') {
                return 1;
            }
        }
        else if (pattern[p_i] == '\\') {
            while(line[l_i] == pattern[p_i]) {
                line[l_i+1] = l_i;
                p_i++;
            }
            l_i++;
            p_i++;
            if(pattern[p_i] == '\0') {
                return 1;
            }
        }
        else {
            l_i++;
        }
       }

       return 0;
    }   


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }
    
    /* we're not going to worry about long lines */
    char buf[MAXSIZE];
    
    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }
    
    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }
    
    return 0;
}
