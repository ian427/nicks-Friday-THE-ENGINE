

#include "Debug.h" 

void DeBug()
{
    FILE* DebugFile;
    DebugFile = fopen("DebugLogger.txt");
    return ;
};

/* FEOF example 
#include <stdio.h>
ifstream file;
int main()
{
    FILE* pFile;
    char buffer[100];

    
    if (pFile == NULL) perror("Error opening file");
    else
    {
        while (!feof(pFile))
        {
            if (fgets(buffer, 100, pFile) == NULL) break;
            fputs(buffer, stdout);
        }
        fclose(pFile);
    }
   
 open(DebugLogger);
    DebugLogger.open("example.txt");
("DebugLogger.txt");

}*/
