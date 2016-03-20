#ifndef _BF_H_
#define _BF_H_

#include <stdio.h>
#include <stdint.h>

void bf_compile(char* out_file, uint32_t memsize, char* code, uint32_t len) {
    FILE* fp = fopen(out_file, "w");
    uint32_t i, c;
    char last = 0;
    fprintf(fp, "#include <stdio.h>\n");
    fprintf(fp, "char mem[%u] = {0};\n", memsize);
    fprintf(fp, "int main(){\n");
    fprintf(fp, "char *p = mem;\n");
    for(i=0; i<len; i++){
        if(code[i] != last){
            switch(last){
            case '+':
                fprintf(fp, "*p += %u;\n", c);
                break;
            case '-':
                fprintf(fp, "*p -= %u;\n", c);
                break;
            case '<':
                fprintf(fp, "p -= %u;\n", c);
                break;
            case '>':
                fprintf(fp, "p += %u;\n", c);
                break;
            }
            c = 0;
        }
        last = 0;
        switch(code[i]){
        case '+':
        case '-':
        case '<':
        case '>':
            last = code[i];
            c++;
            break;
        case '[':
            fprintf(fp, "while(*p){\n");
            break;
        case ']':
            fprintf(fp, "}\n");
            break;
        case '.':
            fprintf(fp, "putchar(*p);\n");
            break;
        case ',':
            fprintf(fp, "*p = getchar();\n");
            break;
        }
    }
    fprintf(fp, "return 0;\n}\n");
}

#endif
