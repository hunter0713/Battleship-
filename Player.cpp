#include "Player.h"
Player::Player()
{

}
Player::Player(int shipNums,string name)
  {
      numShips = shipNums;
      ownShips = new Ship[shipNums];
      for (int i = 1; i <= shipNums; i++)
      {
        Ship tempShip(i);
        ownShips[i-1] = tempShip;
      }
      placeShips();
      namee = name;
  }
Player::~Player()
{
  delete[] ownShips;
}
Board Player::getBoard(char choice)
{
  if(choice == 'o')//if choice is own board, return own board.
  {
    return(ownBoard);
  }
  else //if choice is enemy board, return enemy board.
  {
    return(enemyBoard);
  }

}
void Player::placeShips()
  {
    char tempOrient = '$';
    string tempCoord = "";
    for(int i = 0; i < numShips; i++)
    {
      int xVal =0;
      int yVal =0;
      bool validX = true;
      bool validY = true;
      do
      {
        cout<<"Placing Ship of Size: "<<(i+1);
        while (tempOrient != 'h' && tempOrient != 'v')
        {
        cout<<"\nPlease input an orientation (v for Vertical or h for Horizontal): ";
        cin>>tempOrient;
        if (tempOrient != 'h' && tempOrient != 'v')
          {
            cout<<"Pick a valid option this time.\n";
          }
        }
        ownShips[i].setOrientation(tempOrient);
      validX = true;
      validY = true;
      char xTemp = ' ';
      string playerShot = "";
      bool validInput= 1;
      do
      {
      LOOP:cout<<"Input a position for the front of the ship: ";
      cin >> playerShot;
      validInput= 1;
        try
        {
          xTemp = tolower(playerShot.at(0));
          yVal = playerShot.at(1);
        }
        catch(...)
        {
          cout<<"Position must be in format: 'a1'\n";
          validInput = 0;
        }
      }while(validInput == 0);
          switch (xTemp)
      	{
                 case 'a':
      		xVal = 0;
      		break;
      	         case 'b':
      		xVal = 1;
      		break;
                 case 'c':
      		xVal = 2;			//switch block tcout <<"\nstart of player constructor.\n";ransforms first char in input string from the player into integer value.
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
        if(tempOrient == 'v')
        {
          if (yVal + i + 1 > 8)
          {
            cout<<"Ship out of bounds!\n";
            validY = false;
          }
          else
          {
            for(int k =0; k<i+1; k++)
            {
              try
              {
                if(ownBoard.getPos(yVal+k,xVal) == 's')
                {
                  cout<<"\nCannot Stack Ships!\n";
                  goto LOOP;
                }
                ownBoard.setPos(yVal+k,xVal,'s');
              } catch (const exception& e) {cout << "an error occured on ship place" << e.what() << endl;}
            }
          }
        }
        else if (tempOrient == 'h')
        {
          if (xVal + i + 1 > 8)
          {
            cout<<"Ship out of bounds!\n";
            validX = false;
          }
          else
          {
            for(int k =0; k<i+1; k++)
            {
              try
              {
                if(ownBoard.getPos(yVal,xVal+k) == 's')
                {
                  cout<<"\nCannot Stack Ships!\n";
                  goto LOOP;
                }
                ownBoard.setPos(yVal,xVal+k,'s');
              } catch (const exception& e) {cout << "an error occured on ship place" << e.what() << endl;}
            }
          }
        }
        tempOrient = 'n'; //sets tempOrient to meaningless val for while loop.
      }
      while (!validX || !validY);
      ownShips[i].setPositions(xVal, yVal);
      ownBoard.printBoard();

    }
  }
bool Player::fireShot(int row, int col, Player &target)
{
    if(target.getBoard('o').getPos(col,row) == 's') //where s represents a ships presence. 'o represents the targets "ownBoard"'
    {
        target.receiveHit(row, col);
        enemyBoard.setPos(col,row, 'h');//h represents a ship turned into a hit
        return true;
    }
    else if(target.getBoard('o').getPos(col,row) == '|')// '|' represents empty water
    {
      enemyBoard.setPos(col,row,'m');//m represents a miss that landed in water.
      return false;
    }
    return false;
}

void Player::receiveHit(int xPos, int yPos)
{
ownBoard.setPos(yPos, xPos, 'h');
  for (int i = 0; i < numShips; i++)
  {
    if (ownShips[i].coordCheck(xPos, yPos))
    {
      ownShips[i].addHit();
      break;
    }
  }
}

bool Player::isDead()
{
  bool tempDead = true;
  for (int i = 0; i < numShips; i++)
  {

    if (ownShips[i].isSunk() == false)
    {
      tempDead = false;
    }
  }
  return tempDead;
}
string Player::getName()
{
    return(namee);
}
