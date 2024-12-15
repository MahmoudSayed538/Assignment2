#include <iostream>
#include "BoardGame_Classes.h"
#include "C4.h"
#include "NumTic.h"
#include "game1.h"
#include "game4.h"
#include "game_3.h"
#include "game_8.h"
#include "game_6.h"
#include "sus.h"

using namespace std;

void C4()
{
    int choice;
    Player<char>* players[2];
    connectFourBoard<char>* B = new connectFourBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Four in Row Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new connectFourPlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new connectFourRPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
        }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new connectFourPlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new connectFourRPlayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    // Create the game manager and run the game
    GameManager<char> C4_game(B, players);
    C4_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void pyramid()
{
    int choice;
    Player<char>* players[2];
   PIRAMIDX_O<char> *B = new PIRAMIDX_O<char>();
    string playerXName, player2Name;

    cout << "Welcome to Piramid X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new game_player<char>(playerXName, 'X');
        break;
        case 2:
            players[0] = new game_ranom<char>('X');
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new game_player<char>(player2Name, 'O');
        break;
        case 2:
            players[1] = new game_ranom<char>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}

void XO_5x5 ()
{
    int choice;
    Player<char>* players[2];
    Five_XO<char>* B = new Five_XO<char>();
    string playerXName, player2Name;

    cout << "Welcome to 5 Tic Tac Toe. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Five_XO_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Five_XO_Random<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

  
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Five_XO_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Five_XO_Random<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    // Create and run the game manager
    GameManager<char> Five_XO_Game(B, players);
    Five_XO_Game.run();

    // Clean up memory
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}


void wordTicTacToe()
{
    int choice;
    Player<char>* players[2];
    WordX_O<char>*B=new WordX_O<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Word Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new   word_Player<char>(playerXName, 'W');
            break;
        case 2:
            players[0] = new word_Random_Player<char>('W');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new word_Player<char>(player2Name, 'R');
            break;
        case 2:
            players[1] = new word_Random_Player<char>('R');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return ;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}




void Numerical_Tic_Tac_Toe()
{
    int choice;
    Player<int>* players[2];
    NT_Board<int>* B = new NT_Board<int>();
    string player1Name, player2Name;

    cout << "Welcome to Numerical_Tic_Tac_Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new NT_Player<int>(player1Name, 1);
            break;
        case 2:
            players[0] = new NT_Random_Player<int>(1,1);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
        }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new NT_Player<int>(player2Name, 2);
            break;
        case 2:
            players[1] = new NT_Random_Player<int>(2,2);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    // Create the game manager and run the game
    GameManager<int> NT_game(B, players);
    NT_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Misere()
{
    int choice;
    Player<char>* players[2]; // Array to store two players
    Missere_Board<char>* B = new Missere_Board<char>(); // Create game board
    string playerXName, player2Name;

    cout << "Welcome to Missere Tic Tac Toe. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Missere_player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Missere_comp<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Missere_player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Missere_comp<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    // Start the game
    GameManager<char> Missere_game(B, players);
    Missere_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}

void Ultimate()
{
    int choice;
    Player<char>* players[2];
    Ultimate_board <char>* B = new Ultimate_board <char>();
    string playerXName, player2Name;

    cout << "Welcome to Ultimate X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up dynamically allocated memory
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}


void Sus()
{
    int choice;
    Player<char>* players[2];
    SUS_Board<char>* B = new SUS_Board<char>();
    string playerSName, playerUName;


    // Set up player 1
    cout << "Enter Player S name: ";
    cin >> playerSName;
    cout << "Choose Player S type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new SUS_Player<char>(playerSName, 'S');
            break;
        case 2:
            players[0] = new SUS_Random_Player<char>('S');
            break;
        default:
            cout << "Invalid choice for Player S. Exiting the game.\n";
            return;
    }

    // Set up player 2
    cout << "Enter Player U name: ";
    cin >> playerUName;
    cout << "Choose Player U type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new SUS_Player<char>(playerUName, 'U');
            break;
        case 2:
            players[1] = new SUS_Random_Player<char>('U');
            break;
        default:
            cout << "Invalid choice for Player U. Exiting the game.\n";
            return;
    }

    // Create the game manager and run the game
    GameManager<char> s_u_game(B, players);
    s_u_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }


}




int main()
{
    bool run = true;
    while(run) 
    {
        int game;
        cout<<"Welcome to FCAI game application\nPlease choose the game you wanna play\n1.Pyramid X/O\n2.Four in a Row\n3.5x5 X/O\n4.Word Tic Tac Toe\n5.Numerical Tic Tac Toe\n6.Misere X/O\n7.Ultimate X/O\n8.SUS\nother to exit\n";
        cin>>game;
        switch(game)
        {
            case 1:
                pyramid();
                break;
            case 2:
                C4();
                break;
            case 3:
                XO_5x5();
                break;
            case 4:
                wordTicTacToe();
                break;
            case 5:
                Numerical_Tic_Tac_Toe();
                break;
            case 6:
                Misere();
                break;
            case 7:
                Ultimate();
                break;
            case 8:
                Sus();
                break;
            default:
                run = false;
                break;
        }
    }

}


