#include "csvParser.hpp"

FILE *checkFile(const char *pathname)
{
    FILE *file = fopen(pathname, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file\n");
    }
    return file;
}
void parseCsv(const char *pathname, int mapkeys[])
{
    FILE *file = checkFile(pathname);
    int i = 0;
    char line[MAX_LINE_SIZE];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *tile = strtok(line, ",");

        while (tile != NULL)
        {
            int value = atoi(tile);
            mapkeys[i] = value;
            i++;
            tile = strtok(NULL, ",");
        }
    }

    fclose(file);
}