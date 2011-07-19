    // 'Guess the random number' 1.1.
    // getline() from http://www.cplusplus.com/forum/articles/6046/ ;
    // cls from http://www.cplusplus.com/forum/beginner/1988/3/#msg10830 ;
    // By zingmars , 18.07.11.
    // There might be some wrongs in the code (it works though), some misspellings or something, bu't they can easily be fixed by someone not so good.
    // This compiled fine with Visual Studio 2010 and should with other compilers.
    // A bit of an overkill for such a simple game (~120 lines of code o_O), but I find this to be more functional :)
	
	#include <iostream> // needed for cout (outputting text).
    #include <cstdlib> // needed for exit();
    #include <sstream> // needed for stringstream
    #include <string> // needed for String; getline()
    #include <ctime> // needed to use time thingie, which is used to generate a "random" seed for the random number.
    #include <Windows.h> // used to perform clearscreen
    #include <algorithm>  //to lowercase (for nReadInput)
    using namespace std; //For cout, so I don't have to type std:: in front of the cout's!
   
	////////////////////////////////////////////////////////////////////////////////////////
	//Clearscreen
	////////////////////////////////////////////////////////////////////////////////////////
    void cls( HANDLE hConsole )
    {
       COORD coordScreen = { 0, 0 };
       DWORD cCharsWritten;
       CONSOLE_SCREEN_BUFFER_INFO csbi;
       DWORD dwConSize;
       if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
          return;
       dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
       if( !FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
          dwConSize, coordScreen, &cCharsWritten ))
          return;
       if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
          return;
       if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
          dwConSize, coordScreen, &cCharsWritten ))
          return;
       SetConsoleCursorPosition( hConsole, coordScreen );
    }
    ////////////////////////////////////////////////////////////////////////////////////////     


	// Generates a random number. If you want to change the max number generated, this is where to do it.
    int nGenerate()
    {
            int number;
            number = (rand() % (1000000 + 1)) * (rand() % 8 + 1);
			if (number > 1000000)
			{number=1000000-number;}
            return number;
    }


    // Reads the input from the player, and 'fault-checks' it. This way is a bit more complicated, but way better than cin << ;.
	// I'm kind of considering to use switch instead of the way how the code is right now.
    int nReadInput()
    {
            string sGuess = "";
            int nGuess = 0;
            while (true) {
            getline(cin,sGuess);
            transform(sGuess.begin(), sGuess.end(), sGuess.begin(), ::tolower);
            if (sGuess == "exit") // well, there are cases when we want to exit the application.
            {
                 exit(0);
            }
			// CLS command, see README for details.
			/* if (sGuess =="cls") 
			{
				HANDLE hStdout;
				hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
				cls(hStdout);
				cout << "Screen cleared; Enter a number: ";
				break;
			}
			*/
       // This code converts from string to number safely.
       stringstream myStream(sGuess);
       if (myStream >> nGuess)
       {
        return nGuess;
       }
	  
       cout << "Invalid input, please try again: ";
     }
			return 0; //If something goes wrong, then it will return SOMETHING. I should probably have it output an error message though.
    }
     

    // Asks for input and displays the text related.
    void ask(int nNumber, int nLoop)
    {
            cout << "You've guessed " << nLoop << "/1000 randomly generated numbers!" << endl; 
            cout << "Guess a random number from 1 - 1000000!" << endl;
            cout << "In order to exit the program, please type in 'Exit'!" << endl;
            cout << "Please enter a random number from 1-1000000: ";
			cout << "Debug: " << nNumber << endl;
            int nInput = nReadInput();
            while (nInput != nNumber) //TODO: colder-hotter. (see README)
            {
                    if (nInput > nNumber)
                    {
                            cout << "Nope, It's smaller. ";
                            nInput = nReadInput();
                    }
                    else if (nInput < nNumber)
                    {
                            cout << "Nope, It's bigger. ";
                            nInput = nReadInput();
                    }
            }
            //This gets executed if nInput is equal to the generated number.
        HANDLE hStdout;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        cls(hStdout);
            cout << "You guessed it!!!" << endl << "The number was: " << nNumber << endl << endl;
            nNumber = 0;
    }
     
    int main()
    {
            // nLoop is more for statistical info, to see how many loops I've been through.
            int nLoop = 0;
			srand ( time(NULL) );
            while (nLoop != 1000) // Used a loop, because I want the player to try and guess multiple numbers in a row ;)
								  // 1000 is simply a random number. To be honest - you have to be extremely dedicated to
								  // guess 1000 numbers in a row, without closing the application.
            {
            int nNumber = nGenerate();
            ask(nNumber,nLoop);
            nLoop++;
            }
			
            // If the player has no life (or he cheated and edited the source code), this is what's displayed.
            cout << "Whaaat!??? you actually went on and guessed 1000 numbers?" << endl << "Congratulations, you won the game! or something." << endl << "Press any key to exit";
			cin.ignore().get(); //Give them time to actually read the message.
            return 0;
    }