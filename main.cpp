    // 'Guess the random number' 1.1.
    // getline() from http://www.cplusplus.com/forum/articles/6046/ ;
    // cls from http://www.cplusplus.com/forum/beginner/1988/3/#msg10830 ;
    // By zingmars , 25.07.11.
    // Code might be an unoptimized POS, and I adding new features/maintaining it isn't really easy, but note that I'm still learning C++.
    // This compiled fine with Visual Studio 2010 and should with other compilers.
    // A bit of an overkill for such a simple game, but I find this to be more awesome, and more foolproof :)
	
	#include <iostream>
    #include <cstdlib>
    #include <sstream> 
    #include <string> 
    #include <ctime>
    #include <Windows.h>
    #include <algorithm> 
    using namespace std;
   
	int nInput = 0; // User input ( ask(); ). Made it a global variable to avoid it being reinitialized every loop.
	int nGuess = 0; // User input ( nReadInput() ; ). Made it a global variable to avoid it being reinitialized every loop.

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
            number = (rand() % (100000 + 1)) * (rand() % 25 + 1);
			
			if (number > 1000000)
			{number=1000000 - number;}


            return number;
    }


    // Takes input from the player.
	// I'm kind of considering to use switch instead of ifs.
    int nReadInput()
    {
            string sGuess = "";
            nGuess = 0;

            while (true) {

            getline(cin,sGuess);
            transform(sGuess.begin(), sGuess.end(), sGuess.begin(), ::tolower);

            if (sGuess == "exit") // Exit command.
            {
                 exit(0);
            }

			// TODO: CLS command, see README for details.
			/* if (sGuess =="cls")  // CLS command.
			{
				HANDLE hStdout;
				hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
				cls(hStdout);
				cout << "Screen cleared; Enter a number: ";
				break;
			} */

       // This code converts from string to number safely.
       stringstream myStream(sGuess);
       if (myStream >> nGuess)
       {
        return nGuess;
       }
	  
       cout << "Invalid input, please try again: ";
     }
			return 404; // This shouldn't happen unless the code is messed up.
    }
     
	// Input.
    void ask(int nNumber, int nLoop)
    {
            cout << "You've guessed " << nLoop << "/1000 randomly generated numbers!" << endl; 
            cout << "Guess a random number from 1 - 1000000!" << endl;
            cout << "In order to exit the program, please type in 'Exit'!" << endl;
            cout << "Please enter a random number from 1-1000000: ";
			cout << "Debug: " << nNumber << endl; //TODO: Remove later.
            nInput = nReadInput();
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
	        HANDLE hStdout;
		    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			cls(hStdout);
            cout << "You guessed it!!!" << endl << "The number was: " << nNumber << endl << endl;
            nNumber = 0;
    }
     
    int main()
    {
            int nLoop = 0; // Used to show how many numbers you've guessed.
			int nNumber = 0; // Used to hold the number the user has to guess.
			srand ( time(NULL) ); // Random number generator seed.

            while (nLoop != 1000) // Game loop.
            {
            nNumber = nGenerate();
            ask(nNumber,nLoop);
            nLoop++;
            }
			
            // "You won!" message.
            cout << "Whaaat!??? you actually went on and guessed 1000 numbers?" << endl << "Congratulations, you won the game! or something." << endl << "Press any key to exit";
			cin.ignore().get();
            return 0;
    }