    // 'Guess the random number' 1.0-FINAL.
    // getline() from http://www.cplusplus.com/forum/articles/6046/ ;
    // cls from http://www.cplusplus.com/forum/beginner/1988/3/#msg10830 ;
    // By zingmars , 27.05.11.
    // There might be some wrongs in the code (it works though), some misspellings or something, bu't they can easily be fixed by someone not so good.
    // This compiled fine with Visual Studio 2010 and should with other compilers.
    // A bit of an overkill for such a simple game (~120 lines of code o_O), but I find this to be more functional :)
    #include <iostream> //Cout
    #include <cstdlib> //exit();
    #include <sstream> //stringstream
    #include <string> //String; getline()
    #include <ctime> //time (random seed)
    #include <Windows.h> //clearscreen
    #include <algorithm>  //to lowercase (for nReadInput)
    using namespace std;
    //Clearscreen
    void cls( HANDLE hConsole )
    {
       COORD coordScreen = { 0, 0 };    // home for the cursor
       DWORD cCharsWritten;
       CONSOLE_SCREEN_BUFFER_INFO csbi;
       DWORD dwConSize;
     
        // Get the number of character cells in the current buffer.
     
       if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
          return;
       dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
     
       // Fill the entire screen with blanks.
     
       if( !FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
          dwConSize, coordScreen, &cCharsWritten ))
          return;
     
       // Get the current text attribute.
     
       if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
          return;
     
       // Set the buffer's attributes accordingly.
     
       if( !FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
          dwConSize, coordScreen, &cCharsWritten ))
          return;
     
       // Put the cursor at its home coordinates.
     
       SetConsoleCursorPosition( hConsole, coordScreen );
    }
           
    // Generates a random number. If you wan't to change the max number generated, this is where to do it.
    int nGenerate()
    {
            int number;
            number = rand() % 100 + 1;
            return number;
    }
    // Reads the input from the player, and 'fault-checks' it. This way is a bit more complicated, but way better than cin << ;.
    int nReadInput()
    {
            string sGuess = "";
            int nGuess = 0;
            while (true) {
            getline(cin,sGuess);
            transform(sGuess.begin(), sGuess.end(), sGuess.begin(), ::tolower);
            if (sGuess == "exit") // an exception.
            {
                    exit(0);
            }
       // This code converts from string to number safely.
       stringstream myStream(sGuess);
       if (myStream >> nGuess)
       {
        return nGuess;
       }
       cout << "Invalid input, please try again: ";
     }
    }
     
    // Asks for imput and displays the text related.
    void ask(int nNumber, int nLoop)
    {
            cout << "You've guessed " << nLoop << "/1000 randomly generated numbers!" << endl;
            cout << "Guess a random number from 1 - 100!" << endl;
            cout << "In order to exit the program, please type in 'Exit'!" << endl;
            //cout << "The number is:" << nNumber << endl; //Debug code
            cout << "Please enter a random number from 1-100: ";
            int nInput = nReadInput();
            while (nInput != nNumber)
            {
                    if (nInput > nNumber)
                    {
                            cout << endl << "Nope, It's smaller. ";
                            nInput = nReadInput();
                    }
                    else if (nInput < nNumber)
                    {
                            cout << endl << "Nope, It's bigger. ";
                            nInput = nReadInput();
                    }
            }
            //This gets executed if nInput is equal to the generated number. Also the screen is cleared.
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
     
            while (nLoop != 1000) //Used a loop, because I want the player to try and guess multiple numbers in a row ;)
            {
            srand ( time(NULL) );
            int nNumber = nGenerate();
            ask(nNumber,nLoop);
            nLoop++;
            }
     
            // If the player has no life (or he cheated and edited the source code), this is what's displayed.
            cout << "Whaaat!??? you actually went on and guess 1000 numbers?" << endl << "Congratulations, you won the game! or something." << endl << "Press any key to exit";
            cin.ignore().get(); //Give them time to actually read the message.
            return 0;
    }