//
// Created by 20106 on 12/8/2024.
//

#ifndef WORDX_O_H
#define WORDX_O_H




#include "BoardGame_Classes.h"

template <typename T>
class WordX_O:
public Board<T> {
public:
    WordX_O ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};


template <typename T>
class word_Player : public Player<T> {
public:
    word_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};


template <typename T>
class word_Random_Player : public RandomPlayer<T>{
public:
    word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <fstream>

using namespace std;

// Constructor for X_O_Board
template <typename T>
WordX_O<T>::WordX_O() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';
        }
    }
    this->n_moves = 0;
}




template<typename T>
bool WordX_O<T>::update_board(int x, int y, T mark)
{
    char letter;
    vector<char> characters = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    if (mark == 'W') {

            cout << "Enter your symbol: ";
            cin >> letter;


        while (find(characters.begin(),characters.end(),letter)==characters.end());

    }
    else if (mark == 'R')
    {
       srand(time(0));
        int index = rand() % 26;
        letter = characters[index];
    }


    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == '-' || mark == 0))
    {
        if (mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = '-';
        }
        else
        {
            this->n_moves++;
            cout<<this->board[x][y] ;
            this->board[x][y] = letter;
        }
        return true;
    }

    return false;
}




template<typename T>
void WordX_O<T>::display_board()
{
    for(int i=0;i<this->rows;i++)
    {

        cout<<" \n|  ";
        for(int j=0;j<this->columns;j++) {
            cout<<"("<<i<<","<<j<<")";
            cout<<setw(2)<<this->board[i][j]<<"  |";
        }
        cout<<"\n------------------------\n";
    }
    cout<<endl;
}




template<typename T>
bool WordX_O<T>::is_win() {
    string word;
    vector<string> words;
    ifstream input;
    input.open("dic.txt");



    while(input >> word) {
        words.push_back(word);
    }
    input.close();



    for (int i = 0; i < this->rows; i++)
    {

        string rowst = "";
        string columnst = "";
        rowst.push_back(this->board[i][0]);rowst.push_back(this->board[i][1]);rowst.push_back(this->board[i][2]);
        columnst.push_back(this->board[i][0]);columnst.push_back(this->board[i][1]);columnst.push_back(this->board[i][2]);

        if(find(words.begin(),words.end(),rowst) == words.end() && this->board[i][0] !='-'  && ( this->board[i][1] !='-')&& (this->board[i][2] !='-'))
        {return true;}
        if(find(words.begin(),words.end(),columnst) == words.end() &&( this->board[i][0] !='-')&& ( this->board[i][1] !='-')&& (this->board[i][2] !='-'))
        {return true;}



    }
    string diag1 = "", diag2 = "";

    diag1.push_back(this->board[0][0]);diag1.push_back(this->board[1][1]);diag1.push_back(this->board[2][2]);
    diag2.push_back(this->board[0][2]);diag2.push_back(this->board[1][1]);diag2.push_back(this->board[2][0]);
    if(find(words.begin(),words.end(),diag1)==words.end()&&(this->board[0][0]!='-')&&(this->board[1][1]!='-')&& (this->board[2][2]!='-'))
    {return true;}
    if(find(words.begin(),words.end(),diag2)==words.end()&&(this->board[0][2]!='-')&&(this->board[1][1]!='-')&&( this->board[2][0]!='-'))
    {return true;}

    return false;


}



template <typename T>
bool WordX_O<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WordX_O<T>::game_is_over() {
    return is_win() || is_draw();
}



template <typename T>
word_Player<T>::word_Player(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void word_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}


template <typename T>
word_Random_Player<T>::word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}


template <typename T>
void word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //WORDX_O_H
