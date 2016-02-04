/*
	Once completed, this program will act as a backend server
	with the following aims

	1) communicate with a user logged on a terminal
	   using smaller "command" programs.
	2) communicate with a user using TCP
	3) send and receive data from the Spartan 6

*/
// ini libraries
#define INI_INLINE_COMMENT_PREFIXES "%" // Change this to change what is a comment
#include "inih/cpp/INIReader.cpp"
#include "inih/ini.c"

// contains variables and function declarations
#include "main.h"

using namespace std;


// All the parameters coming from the parser can be declared here
time_t startTime, endTime;
int waveform, band;



int main(int argc, char *argv[])
{
	string command = "\0";
	int i = 0;  // You may use this in a for loop

	
	// Displays the splash screen
	dispSplash();
	
	printf("\n");
	
	// This is where the CLI gets displayed
	for(;;)
	{
		cout << ">> ";
		cin >> command;
		
		// ---------------------------------------------------------------------- //
		//       The following if statement finds out what the user wants         //
		// ---------------------------------------------------------------------- //
		
		// Quits the program
		// Stop any processes that may have been started
		//if(strcmp(command,"exit") == 0 || strcmp(command,"quit") == 0 || strcmp(command,"q") == 0 || strcmp(command,"e") == 0)
		if(command == "exit" || command == "quit" || command == "e" || command == "q")
		{
			return 1;
		}
		else if(command == "p" || command == "parse")
		{
		    string filename;
		    cout << "File name: ";
		    cin >> filename;
		    //if(filename.size() == 0) filename = "header.ini"; // Default filename
		    int success = importExperiment(filename);
		}
		else if(command == "h" || command == "help")
		{
		    dispHelp();
		}
	}
	
  return 0;
}

// Splash screen shown at startup
void dispSplash(void)
{
	cout << "\nWelcome to the Pentek Parser CLI for the Industrial Computer!\n\n";
//	printf("-------------------------------------------------------------\n");
	dispHelp();
}

// Displays the command list
void dispHelp(void)
{
	cout << "Below is a list of the available commands:\n";
	cout << "------------------------------------------\n";
	cout << "(h)elp\t\tdisplays this screen.\n";
	cout << "(p)arse\t\tretrieve parameters from header file\n";
	cout << "(e)xit(q)\t\tquits the program.\n\n";
}

// Imports the header file
int importExperiment(string fileName)
{
    INIReader reader(fileName);
    struct tm tm;   // Used for converting string to time
    
    
    //n = reader.GetInteger("settings", "UniquePulses", 1);
    //m = reader.GetInteger("settings", "Repeats", 1);
    
    // Extracts waveform number
    waveform = reader.GetInteger("pentek", "waveform", -1);
    cout << "waveform number is: " << waveform << "\n";
    
    // Extracts band number
    band = reader.GetInteger("pentek", "band", -1);
    cout << "band number is: " << band << "\n";    
    
    // Extracts starting time
    strptime(reader.Get("settings", "StartTime", "01-01-1971 12:00:00").c_str(), "%d-%m-%Y %H:%M:%S", &tm);
    startTime = mktime(&tm);
    
    cout << "start time is: " << startTime << "\n";
    
    // Extracts end time
    strptime(reader.Get("settings", "EndTime", "01-01-1971 12:00:00").c_str(), "%d-%m-%Y %H:%M:%S", &tm);
    endTime = mktime(&tm);
    
    cout << "end time is: " << endTime << "\n";

    // TODO: return error if file does not exist
    return 1;

}

