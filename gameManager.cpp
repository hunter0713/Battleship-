#include "gameManager.h"
#include <cctype>
using namespace std;


gameManager::gameManager()
  {
    start = false;
    run();
  }

gameManager::~gameManager()
  {

  }

void gameManager::run()
{
  playerMenu();
  if(start == true)
  {
    gameLoop();
  }
}

void gameManager::playerMenu()
{
  playerChoice = 'f';
  char playerInput = ' ';
  cout << "\n===============================================================\n===============================================================\n";
  cout << "===WELCOME TO BATTLESHIP!======================================" << endl <<
  "===============================================================\n===============================================================\n";
  while(start != true && !(isdigit(playerInput)))
    {
      cout<< "\n===============================================================";
      cout<< "\n1.) Start Game" << endl <<
      "2.) Set Number of Ships" << endl <<
      "3.) Close Game\n===============================================================" << endl;
      cout<<">> ";

      cin >> playerInput;
      /*if (playerInput.length() > 1)
      {
        cout<< "Input too long, just 1 character please!\n";
      }*/

        playerChoice = playerInput;


      if(playerChoice == '1')
        {
           start = true;
        }
     else if(playerChoice == '2')
       {
         do{
            cout << "Please input new number of ships to play (must be between 1 and 5): ";
            cin >> numOfShips;

            if (numOfShips < 1 || numOfShips > 5 || cin.fail())
            {
              cout<<"\nERROR: Invalid Input!\n";
              cin.clear();
              cin.ignore();
            }
          } while(numOfShips < 1 || numOfShips > 5);

        cout<< "\nNumber of ships in game: " << numOfShips << endl;

       }
    else if(playerChoice == '3')
       {
         cout<<"Thanks for playing!" << endl;
         exit(-1);
       }
    else
      {
        cout << "Invalid Menu Choice! Please Choose Again.\n>> ";
        cin >> playerChoice;
      }
    }
  if(start == true)
  {
    gameLoop();
  }
}
void gameManager::gameLoop()
{
  string s = "";
  cout<< "Player 1, Set Your Ships!\n";
  Player p1(numOfShips,"Player 1");
  //BUNCH OF NEW LINES SO PLAYERS BOARDS Stay PRIVATE in FULLSCREEN GAMEPLAY
  cout << "Press any key(AND ENTER) to begin setting up player 2's board: \n";
  cin >> s;
  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  //BUNCH OF NEW LINES SO PLAYERS BOARDS Stay PRIVATE in FULLSCREEN GAMEPLAY
  cout<< "Player 2, Set Your Ships!\n";
  Player p2(numOfShips ,"Player 2");
  //BUNCH OF NEW LINES SO PLAYERS BOARDS Stay PRIVATE in FULLSCREEN GAMEPLAY
  cout << "Press any key(AND ENTER) to finish board setup: \n";
  cin >> s;
  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  while(!p1.isDead() && !p2.isDead())
  {
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Press any key(AND ENTER) to begin Player 1's turn: \n";
    cin >> s;
    cout<< "=======================\nPlayer One: it's your turn!\n=======================";
    //BUNCH OF NEW LINES SO PLAYERS BOARDS Stay PRIVATE in FULLSCREEN GAMEPLAY
    playerTurn(p1, p2);
    if (p2.isDead())
    {
      gameOver(p1);
      break;
    }
    cout << "Press any key(AND ENTER) to end Player 1's turn: \n";
    cin >> s;
    //BUNCH OF NEW LINES SO PLAYERS BOARDS Stay PRIVATE in FULLSCREEN GAMEPLAY
      cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Press any key(AND ENTER) to begin Player 2's turn: \n"; //dont know how to make accept just keypress.
    cin >> s;
    cout<< "=======================\nPlayer Two: it's your turn!\n=======================";
    playerTurn(p2, p1);
    if (p1.isDead())
    {
      gameOver(p2);
      break;
    }
    cout << "Press any key(AND ENTER) to end Player 2's turn: \n"; //same as comment above. (WIP)
    cin >> s;
      cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  }
  playerMenu();
}
void gameManager::playerTurn(Player &p, Player &opponent)
{
  cout << '\n';
  cout<<"YOUR BOARD: \n";
  p.getBoard('o').printBoard(); //'o' represents "own board"
  cout<<"\nTARGET BOARD: \n";
  p.getBoard('e').printBoard(); //'e' represents "enemy board"
  cout << '\n';
  int xVal =0;
  int yVal =0;
  bool validX = true;
  bool validY = true;
do
{
  validX = true;
  validY = true;
  char xTemp = ' ';
  string playerShot = "";
  cout << "Enter space to fire at: ";
  cin >> playerShot;
  while(playerShot.length() != 2)
  {
    cout << "Enter a valid space to fire at (valid spaces follow format 'a1'): ";
    cin >> playerShot;
  }
  xTemp = tolower(playerShot.at(0));
  yVal = playerShot.at(1);
    switch (xTemp)
	{
           case 'a':
		xVal = 0;
		break;
	         case 'b':
		xVal = 1;
		break;
           case 'c':
		xVal = 2;			//switch block transforms first char in input string from the player into integer value.
		break;
	         case 'd':
		xVal = 3;
		break;
           case 'e':
		xVal = 4;
		break;
	         case 'f':
		xVal = 5;
		break;
           case 'g':
		xVal = 6;
		break;
	         case 'h':
		xVal = 7;
		break;
	         default:
		cout <<"X Position Out of Bounds!\n";
    validX = false;
		break;
  }
    switch (yVal)
	{
           case '1':
		yVal = 0;
		break;
	         case '2':
		yVal = 1;
		break;
           case '3':
		yVal = 2;			//switch block transforms second char into integer value for grid.
		break;
	         case '4':
		yVal = 3;
		break;
           case '5':
		yVal = 4;
		break;
	         case '6':
		yVal = 5;
		break;
           case '7':
		yVal = 6;
		break;
	         case '8':
		yVal = 7;
		break;
	         default:
		cout <<"Y Position Out of Bounds!\n";
    validY = false;
		break;
	}
  if (p.getBoard('e').getPos(yVal, xVal) == 'm' || p.getBoard('e').getPos(yVal, xVal) == 'h')
  {
    cout << "Already fired here!\n";
    validX = false;
    validY = false;
  }
} while (!validX || !validY);

if(p.fireShot(xVal,yVal, opponent))
{
  opponent.receiveHit(xVal, yVal);
}
cout<<"TARGET BOARD: \n";
p.getBoard('e').printBoard();


}

void gameManager::gameOver(Player winner)
{
  playerChoice = 17;
  start = false;
  cout<<"============\nGAME OVER\n============\n";
  {
    if(winner.getName() == "Player 1")
    {
      cout<<"\nPlayer 1 Wins!\n";
    }
    else if(winner.getName() == "Player 2")
    {
      cout<< "\nPlayer 2 Wins!\n";
    }
    else
    {
    cout<<"Whoops!  Something's not right here.\n";
    }
  }
}
