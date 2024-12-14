

#ifndef PIRAMIDX_O_H
#define PIRAMIDX_O_H

#include <iomanip>

#include"BoardGame_Classes.h"
template <typename T>
class PIRAMIDX_O:
public Board<T>
{
public:
    PIRAMIDX_O();
    bool update_board(int x,int y , T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();



};

template <typename T>
class game_player:
public Player<T>
{
 public:
    game_player(string name,T symbol);
    void getmove (int &x,int &y);

};

template <typename T>
class game_ranom: public RandomPlayer<T> {

public:

    game_ranom(T symbol);
    void getmove (int &x,int &y);


};






#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;




template<typename T>
PIRAMIDX_O<T>::PIRAMIDX_O() {
    this->rows = 3;
    this->columns = 5;


    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }

    this->n_moves = 0;
}



template<typename T>
bool PIRAMIDX_O<T>::update_board(int x ,int y, T mark)
{
    if(!(x<0||x>=this-> rows||y<0||y>=this-> columns)&&(this->board[x][y]==0||mark==0))
    {
        if(mark==0)
        {
            this->n_moves--;
            this->board[x][y]=0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y]=toupper(mark);

        }

        return true;
    }
 return false;
}




template<typename T>
void PIRAMIDX_O<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {

        for (int space = 0; space < (this->rows - i - 1); space++) {
            cout << "   ";
        }

        cout << "| ";
        for (int j = 0; j < this->columns; j++) {

            if (j >= (this->columns / 2 - i) && j <= (this->columns / 2 + i)) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
        }
        cout<<endl;
    }
    cout << "\n-----------------------------";
    cout << endl;

}




template<typename T>
bool PIRAMIDX_O<T>::is_win()
{

        if (
              (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != 0) ||
              (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != 0) ||
              (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != 0) ||
              (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != 0)||
              (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != 0)
              )

            {
            return true;
            }


    // Check diagonals
    if ((this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0))
        {
        return true;
        }

    return false;

}


template <typename T>
bool PIRAMIDX_O<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}


template<typename T>
bool PIRAMIDX_O<T>::game_is_over()
{
    return is_win() || is_draw();


}

template<typename T>
game_player<T>::game_player(string name ,T symbol):Player<T>(name,symbol) {
}

template<typename T>
void game_player<T>::getmove(int &x, int &y)

{
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}




template <typename T>
game_ranom<T>::game_ranom(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void game_ranom<T>::getmove(int& x, int& y)
{
    x =rand() % 3;//valid row range
    int start_index=(5/2)-x;
    y =start_index+(rand()%(2*x+1)); //valid coloumn range




}















#endif //PIRAMIDX_O_H
