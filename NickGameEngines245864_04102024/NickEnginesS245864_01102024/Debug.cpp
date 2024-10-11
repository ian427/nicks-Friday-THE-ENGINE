

#include "Debug.h" 

#include <cstdio>  // For FILE, fopen, fprintf, fclose

void DeBug()
{
    // Open the file in append mode to add logs at the end of the file
    FILE* DebugFile = fopen("DebugLogger.txt", "a");

    // Check if the file was successfully opened
    if (DebugFile == nullptr)
    {
        // Handle the error, for example, by printing an error message
        printf("Error: Unable to open DebugLogger.txt\n");
        return;
    }

    // Write some debug information to the file
    fprintf(DebugFile, "Debug log entry\n");

    // Close the file
    fclose(DebugFile);
}

