#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


// Defines byte and block size
typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

// Function prototype
bool check_signature(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // Checks for correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover [file]\n");
        return 1;
    }
    // Opens file and returns if unable to open
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    // Buffer for the file reader
    BYTE buffer[BLOCK_SIZE];

    // Counter and string buffer to construct file names
    int counter = 0;
    char s[8];

    // State boolean
    bool writing = false;

    // Initalizes file
    FILE *out;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file))
    {

        if (check_signature(buffer)) // Checks for jpeg signature
        {
            if (writing) // State boolean helps to indicate if a file is currently being written
            {
                fclose(out); // If new jpeg found, close the previous file
            }

            if (counter > 9) // Constructs file name
            {
                sprintf(s, "0%i.jpg", counter);
            }
            else
            {
                sprintf(s, "00%i.jpg", counter);
            }

            // Opens file for writing, with name as constructed in s
            out = fopen(s, "w");

            // Handles states
            counter++;
            writing = true;
        }
        if (writing)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, out);
        }
    }
}

bool check_signature(BYTE buffer[])
{
    // Checks for the jpeg signature
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
    {
        for (int i = 0; i <= 15; i++)
        {
            if (buffer[3] == 224 + i) // Since 0xe0 = 224, 0xe0 through 0xef is 224 through 239
            {
                return true;
            }
        }
    }
    return false;
}