#include <iostream>
#include <vector>
using namespace std;
class Player
{
    public:
    string name;
    int pos;
    Player(string &s)
    {
        name=s;
        pos=0;
    }
    int move(int r)
    {
        pos = pos +r;
        return pos;
    }
};
class Board
{
    public:
    int size;
    vector<int> snakes;
    vector<int> ladders;
};
class Game
{
    public:
    Board board;
    vector<Player> playernames;
    vector<vector<int>> spos;
    vector<vector<int>> lpos;
    Game(int s, vector<string> &p, vector<int> &sp, vector<int> &lp)
    {
        board.size = s;
        for (int i=0;i<p.size();i++)
        {
            playernames.push_back(Player(p[i]));
        }
        board.snakes = sp;
        board.ladders = lp;
        
    }
    void play()
    {
        bool winnernotfound=true;
        while(winnernotfound)
        {
            for (int i=0;i<playernames.size();i++)
            {
                int dice = 1+rand()%6;
                int newpos=playernames[i].move(dice );
                if (newpos > board.size)
                {
                    playernames[i].pos=newpos-dice;
                }
                for (int j=0;j< board.snakes.size();j=j+2)
                {
                    if (playernames[i].pos == board.snakes[j])
                    {
                        playernames[i].pos= board.snakes[j+1];
                        std::cout<<""<<playernames[i].name<<" Got Snake!!"<<endl;
                        
                    }
                }
                for (int j=0;j< board.ladders.size();j=j+2)
                {
                    if (playernames[i].pos == board.ladders[j])
                    {
                        playernames[i].pos= board.ladders[j+1];
                        std::cout<<""<<playernames[i].name<<" Got Ladder!!"<<endl;
                        
                    }
                }
                cout<<"Player "<<playernames[i].name<<"is at position"<<playernames[i].pos<<endl;
                if (playernames[i].pos == board.size)
                {
                    cout<<"Player "<<playernames[i].name<<" is Winner"<<endl;
                    winnernotfound=false;
                }
            }
        }
    }
};

int main()
{
    //Game game;
    vector<string> name= {"yesh","pari"};
    vector<int> snake={90, 10,50,20};
    vector<int> ladder ={4,45,34,78};
    Game game(100,name,snake ,ladder);
    game.play();
    return 0;
}

