
#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H
#include <iostream>
// Declare the DeBug function in the header
class DeBug
{
	static DeBug * _Log;
	FILE* DebugFile;
	std::string ERRORMSG = "NULL";
	std::string ERRORFILE = "NULL";
	enum Verbosity
	{
		none, // not classed
		error_red, //system|game breaking/ could cause crash
		error_yellow,//error visiable to player
		error_green,// error not visiable to player
		warning,// happened recovered from
		note// thing has happened


	};
    DeBug();
	~DeBug();
public:
	int ERRORNUM = 0;
	static DeBug* Log();
	void printDebug(std::string ERRORMSG, ...);
};
	

#endif