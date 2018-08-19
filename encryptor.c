#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 128
const char *key;
size_t KEY_LENGTH;
char *encrypt_decrypt(char *toEncrypt)
{
    char *result = malloc(BUFFER_SIZE);
    for (int i = 0; i < BUFFER_SIZE; i++)
        result[i] = toEncrypt[i] ^ key[i % KEY_LENGTH];
    return result;
}

int main(int argc, char const *argv[])
{

    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
        fprintf(stderr, "Can't open file %s.\n", argv[1]);
        return EXIT_FAILURE;
    }
    FILE *output = fopen(argv[3], "ab");
    if (!output)
    {
        fprintf(stderr, "Can't open file %s.\n", argv[3]);
        return EXIT_FAILURE;
    }
    char *buffer = malloc(BUFFER_SIZE + 1);
    size_t len;
    key = argv[2];
    KEY_LENGTH = strlen(key);
    while ((len = fread(buffer, 1, BUFFER_SIZE, file)) != 0)
    {
        buffer[len] = 0;
        fwrite(encrypt_decrypt(buffer), len, 1, output);
    }
    free(buffer);
    fclose(file);
    fclose(output);

    return EXIT_SUCCESS;
}
