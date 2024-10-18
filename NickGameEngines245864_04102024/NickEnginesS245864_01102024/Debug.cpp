#include <string> 
#include "Debug.h" 
#include <cstdio>  
#include <cstdarg>
#define _CRT_SECURE_NO_WARNINGS
DeBug::DeBug()
{    
    
    // Open 
    fopen_s(&DebugFile ,"DebugLogger.txt", "a");

    //error check
    if (DebugFile == nullptr)
    {
      
        printf("Error: Unable to open DebugLogger.txt\n");
        return;
    }
  fprintf(DebugFile, "New  Log \n");
    
   

    
}
DeBug* DeBug::_Log = NULL;

DeBug* DeBug::Log()
{
    
    if (!_Log)
    {
        _Log = new DeBug();
        //_Log->Init();
    }

    return _Log;
}


 void DeBug::printDebug(std::string ERRORMSG, ...)//called to write log entry
{
     switch (Verbosity)
     {
     case 1 :

     default:

       break;
     }:()

     //format
     va_list args_list;
     va_start(args_list, ERRORMSG);
     char MessageBuffer[256];
     vsnprintf(MessageBuffer, 256, ERRORMSG.c_str(), args_list); 
    va_end(args_list);



    ERRORNUM++;
    fprintf(DebugFile, "Error %d: %s \n", ERRORNUM, MessageBuffer);
    printf("Error %d: %s \n",ERRORNUM, MessageBuffer);

}


 DeBug::~DeBug()
 {
     // Close the file
     fclose(DebugFile);
 }