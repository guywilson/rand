#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void printUsage()
{
    printf("\nUsage:\n");
    printf("\trand [options]\n");
    printf("\t\t-o <output file>\n");
    printf("\t\t-s <size in bytes>\n\n");

    return;
}

int main(int argc, char * argv[])
{
    char        szOutputFileName[256];
    uint32_t    numBytes = 256;
    uint32_t    byteCounter;
    int         i;
    FILE *      fptrRand;
    FILE *      fptrOutput;

    if (argc > 1) {
        for (i = 1;i < argc;i++) {
            if (argv[i][0] == '-') {
                if (argv[i][1] == 'o') {
                    strncpy(szOutputFileName, &argv[i+1][0], 255);
                }
                else if (argv[i][1] == 's') {
                    numBytes = strtoul(&argv[i+1][0], NULL, 10);
                }
                else {
                    printUsage();
                    exit(-1);
                }
            }
        }
    }
    else {
        printUsage();
        exit(0);
    }

    if (strlen(szOutputFileName) == 0) {
        printUsage();
        exit(-1);
    }

    printf("Writing %u bytes to '%s'\n", numBytes, szOutputFileName);

    fptrRand = fopen("/dev/urandom", "rb");

    if (fptrRand == NULL) {
        printf("FATAL: Failed to open random device\n\n");
        exit(-1);
    }

    fptrOutput = fopen(szOutputFileName, "wb");

    if (fptrOutput == NULL) {
        printf("FATAL: Failed to open output file '%s'\n\n", szOutputFileName);
        exit(-1);
    }

    byteCounter = 0;

    while (byteCounter < numBytes) {
        fputc(fgetc(fptrRand), fptrOutput);
        byteCounter++;
    }

    fclose(fptrRand);
    fclose(fptrOutput);

    return 0;
}
