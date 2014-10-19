/* 
 * File:   main.cpp
 * Author: Oscar Martinez
 *
 * Created on October 11, 2014, 5:22 PM
 * 
 * ==========
 * randHit
 * ==========
 * Purpose: 
 * chose two random digits and shoot at that location
 * keeps chooses two more  digits if the location has been shot at
 * 
 * ==========
 * smartHit
 * ==========
 * Purpose: 
 * Once randHit hits an enemy target, it implements smartHit
 * firstHitX and firstHitY store the coordinates of the original hit. 
 * xCoord and yCoord are used to manipulate the coordinates being shot at. 
 * the function starts shooting clockwise, once it makes a hit, it continues 
 * firing in that direction. 
 * 
 * yet to implement: 
 * the function will keep firing in the same direction until the ship is  sunk 
 *    or the shot is a miss. 
 * if the shot is a miss and the ship has not been sunk it should return to the 
 *      firstHitX and firstHitY coordinates and start firing in the opposite direction 
 *      than what it was firing. 
 * if the ship has been sunk the function should start all oven and use randHit 
 *      to find another ship. 
 * 
 * *****************************************************************************
 * 
 * =======================================
 *  Version2
 * =======================================
 * Function now is able to change directions once it encounters the end of the ship
 * Once it changes direction and encounters the opposite end it will exit out 
 *      and call randHit() until another ship is hit. 
 * 
 * =============================
 *  Bug Report
 * =============================
 * I am working on a solution to the following bugs: 
 * Causes a segmentation fault when the first hit it makes is to the top of the 
 *      rightmost vertical ship(Aircraft Carrier). 
 * If a coordinate adjacent to a ship has been shot at previously by randHit() 
 *      and the ship is then hit, it will not skip over these coordinates. 
 * When switching directions on Aircraft Carrier, it will occasionally shoot through shots already fired.
 * Occasionally it will exit and call randHit() without sinking the ship. 
 * 
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int SIZE = 10; 
void shoot(); 
void printGrid(char grid[][SIZE]); 
void randHit(char grid [][SIZE],char enemyGrid[][SIZE], int &, int &);
void smartHit(char grid [][SIZE],char enemyGrid[][SIZE], int &, int &, int &, int &, int &, int &, int &);

int main(int argc, char** argv) {
    //seed randon number
    srand(time(NULL)); 
    
    //coordinate variables
    
    char nextTurn; 
    int x = -1; 
    int y = -1; 
    int firstHitX; 
    int firstHitY; 
    int direction = 0; 
    int xCoord; 
    int yCoord; 
    //declare grid
    const int SIZE = 10; 
    char grid[SIZE][SIZE]; 
    
    //opponents grid 
    char enemyGrid[SIZE][SIZE]= {{'~','~','~','~','~','~','~','~','~','~'},
                            {'~','o','~','~','~','~','o','o','o','~'},
                            {'~','o','~','~','~','~','~','~','~','~'},
                            {'~','~','~','~','~','~','~','~','~','~'},
                            {'~','~','~','~','~','~','~','~','o','~'},
                            {'~','~','o','o','o','~','~','~','o','~'},
                            {'~','~','~','~','~','~','~','~','o','~'},
                            {'~','~','~','o','o','o','o','~','o','~'},
                            {'~','~','~','~','~','~','~','~','o','~'},
                            {'~','~','~','~','~','~','~','~','~','~'}};
    //fill grid 
    for(int i=0; i<SIZE; i++){ 
        for(int j=0; j<SIZE; j++){ 
            grid[i][j]= '~'; 
        }
    }
    printGrid(enemyGrid); 
    do{ 
    //shoot
        if(grid[x][y]!='@'){
           randHit(grid,enemyGrid, x, y); 
            
        }
            
        printGrid(grid);
        
        if(grid[x][y]== '@'){ 
            cout << "X: " <<x <<" Y: " << y <<endl; 
            cout << "About to enter smartHit" <<endl; 
            smartHit(grid, enemyGrid, x, y, firstHitX, firstHitY, direction, xCoord, yCoord); 
        }
        cout << "X: " <<x <<" Y: " << y <<endl; 
        printGrid(grid); 
        
        cout <<"Display another turn? "; 
        cin >> nextTurn; 
        cout <<endl; 
    }while(nextTurn == 'Y' || nextTurn == 'y'); 
    return 0;
}
void smartHit(char grid [][SIZE], char enemyGrid[][SIZE], int &x, int &y, 
              int &firstHitX, int &firstHitY, int &direction, int &xCoord, int &yCoord){ 
    //cout << "x: " <<x <<" y: " <<y <<" Fhx: " << firstHitX << " Fhy: " <<firstHitY << endl;
    if(firstHitX!=x && firstHitY!= y){ 
        firstHitX = x; 
        firstHitY = y; 
        xCoord = x; 
        yCoord = y; 
        return; 
    }
    if(direction == 0){ 
        //Checks if coordinate is an enemy target and changes player grid if it is
        //Keeps going in same direction if it keeps hitting targets
        if(enemyGrid[xCoord][yCoord+1]=='o'){ 
            grid[xCoord][yCoord+1]='@';
            yCoord+= 1; 
            //cout <<"dir0 if fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
            return; 
        }
        //If shot is a miss, changes direction (clockwise) or go in opposite direction 
        //      if it encounters end of ship. 
        else{
            grid[xCoord][yCoord+1] = 'X';
            //If it encounters the end of the ship it will go to the first shot fired on 
            //  that ship and will start shooting in the opposite direction. 
            if(direction == 0 && grid[xCoord][yCoord+1] == 'X' && grid[xCoord][yCoord] == '@' && grid[xCoord][yCoord-1]!='~'){ 
                yCoord = firstHitY; 
                direction = 1; 
            }
            direction++; 
            //cout <<"dir0 else fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
        }
    }
    else if(direction == 1){ 
        //Checks if coordinate is an enemy target and changes player grid if it is
        //Keeps going in same direction if it keeps hitting targets
        if(enemyGrid[xCoord+1][yCoord]=='o'){ 
            grid[xCoord+1][yCoord]='@';
            xCoord+=1; 
            //cout <<"dir1 if fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
            return; 
        }
        //If shot is a miss, changes direction (clockwise) or go in opposite direction 
        //      if it encounters end of ship. 
        else{
            grid[xCoord+1][yCoord] = 'X';
            //If it encounters the end of the ship it will go to the first shot fired on 
            //  that ship and will start shooting in the opposite direction.
            if(direction == 1 && grid[xCoord+1][yCoord] == 'X' && grid[xCoord][yCoord] == '@' && grid[xCoord-1][yCoord]!='~'){ 
                xCoord == firstHitX; 
                direction = 2; 
            }
            direction++; 
            //cout <<"dir1 else fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
        }
    }
    else if(direction == 2){ 
        //Checks if coordinate is an enemy target and changes player grid if it is
        //Keeps going in same direction if it keeps hitting targets
        if(enemyGrid[xCoord][yCoord-1]=='o'){ 
            grid[xCoord][yCoord-1]='@';
            yCoord-=1; 
            cout <<"dir2 if fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
            return;
        }
        //If shot is a miss, changes direction (clockwise)
        else{
            grid[xCoord][yCoord-1] = 'X';
            //If directions were switched (end of ship was reached) and encounters 
            //  the other end, it will change values to call randHit() again. 
            if(grid[xCoord][yCoord-1] == 'X' && grid[xCoord][yCoord]=='@' && grid[xCoord][yCoord+1] == '@'){ 
                x= -1;          //Changes values to call randHit()
                y= -1; 
                direction = 0;  //resets direction 
                return; 
            }
            direction++; 
            cout <<"dir2 else fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
        }
    }
    else if(direction == 3){ 
        //Checks if coordinate is an enemy target and changes player grid if it is
        //Keeps going in same direction if it keeps hitting targets
        if(enemyGrid[xCoord-1][yCoord]=='o'){ 
            grid[xCoord-1][yCoord]='@';
            xCoord-=1;
            //cout <<"dir3 if fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
            return;
        }
        //If shot is a miss, changes direction (clockwise) or go in opposite direction 
        //      if it encounters end of ship. 
        else{
            grid[xCoord-1][yCoord] = 'X';
            //If directions were switched (end of ship was reached) and encounters 
            //  the other end, it will change values to call randHit() again. 
            //cout <<"dir3 else fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
            if(grid[xCoord-1][yCoord] == 'X' && grid[xCoord][yCoord]=='@' && grid[xCoord+1][yCoord] == '@'){ 
                x= -1;          //Changes values to call randHit()
                y= -1; 
                direction = 0;  //Resets direction
                return; 
            }
        }
    }
    
    //cout <<"endSH fhx: " <<firstHitX <<" fhy: " << firstHitY <<" x: " <<x <<" y: " <<y <<" xCoord: " <<xCoord <<" yCoord: " <<yCoord << " direction: " <<direction <<endl;
     
}
void randHit(char grid [][SIZE],char enemyGrid[][SIZE],int &x,int &y){ 
    do{ 
        x = rand()%10; 
        y = rand()%10; 
    }while(grid[x][y] == 'X'|| grid [x][y]=='@'); 
     
    if(enemyGrid[x][y]=='o'){ 
        grid[x][y]='@';
    }
    else{
        grid[x][y] = 'X';
    }
}

void printGrid(char grid[][SIZE]){ 
    for(int i=0; i<SIZE; i++){ 
        for(int j=0; j<SIZE; j++){ 
            cout<<grid[i][j] <<" "; 
        }
        cout<<endl; 
    }
    
}