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
                            {'~','~','~','~','~','~','~','~','o','~'}};
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
        if(enemyGrid[xCoord][yCoord+1]=='o'){ 
            grid[xCoord][yCoord+1]='@';
            yCoord+= 1; 
            return; 
        }
        else{
            grid[xCoord][yCoord+1] = 'X';
            direction++; 
        }
    }
    else if(direction == 1){ 
        if(enemyGrid[xCoord+1][yCoord]=='o'){ 
            grid[xCoord+1][yCoord]='@';
            xCoord+=1; 
            return; 
        }
        else{
            grid[firstHitX+1][firstHitY] = 'X';
            direction++; 
        }
    }
    else if(direction == 2){ 
        if(enemyGrid[xCoord][yCoord-1]=='o'){ 
            grid[xCoord][yCoord-1]='@';
            yCoord-=1; 
            return;
        }
        else{
            grid[firstHitX][firstHitY-1] = 'X';
            direction++; 
        }
    }
    else if(direction == 3){ 
        if(enemyGrid[xCoord-1][yCoord]=='o'){ 
            grid[xCoord-1][yCoord]='@';
            xCoord-=1;
            return;
        }
        else{
            grid[firstHitX-1][firstHitY] = 'X';
            direction++; 
        }
    }
    
    
     
}
void randHit(char grid [][SIZE],char enemyGrid[][SIZE],int &x,int &y){ 
    x = rand()%10; 
    y = rand()%10; 
    while(grid[x][y] == 'X'|| grid [x][y]=='@'){ 
        x = rand()%10; 
        y = rand()%10; 
    }
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