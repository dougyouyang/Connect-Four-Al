#include <iostream>

#define INF 1000000000

using namespace std;

int score1[5]={0, 1, 5, 9999, 99999999};
int score2[5]={0, 1, 5, 9999, 9999999};

int graph[7][6], po[7];

void play2(int x, int y, int &a, int &b)
{
    int move[3]={0, 0, 0};
    move[graph[x][y]]++, move[graph[x-1][y-1]]++, move[graph[x-2][y-2]]++, move[graph[x-3][y-3]]++;
    if(move[2]==0)
        a+=score1[move[1]];
    if(move[1]==0)
        b+=score2[move[2]];
}

void play22(int x, int y, int &a, int &b)
{
    int move[3]={0, 0, 0};
    move[graph[x][y]]++, move[graph[x+1][y-1]]++, move[graph[x+2][y-2]]++, move[graph[x+3][y-3]]++;
    if(move[2]==0)
        a+=score1[move[1]];
    if(move[1]==0)
        b+=score2[move[2]];
}

int play3(int x, int y)
{
    int move[3]={0, 0, 0};
    move[graph[x][y]]++, move[graph[x-1][y-1]]++, move[graph[x-2][y-2]]++, move[graph[x-3][y-3]]++;
    if(move[1]==4 || move[2]==4)
        return 1;
    
    return 0;
}

int play33(int x, int y)
{
    int move[3]={0, 0, 0};
    move[graph[x][y]]++, move[graph[x+1][y-1]]++, move[graph[x+2][y-2]]++, move[graph[x+3][y-3]]++;
    if(move[1]==4 || move[2]==4)
        return 1;
    
    return 0;
}

int win()
{
    int i, j, k;
    
    //horizontal
    for(i=5;i>=0;i--)
        for(j=0;j<=3;j++){
            int move[3]={0, 0, 0};
            for(k=j;k<j+4;k++)
                move[graph[k][i]]++;
            if(move[1]==4 || move[2]==4)
                return 1;
        }
    //vertical
    for(i=0;i<=6;i++)
        for(j=0;j<=2;j++){
            int move[3]={0, 0, 0};
            for(k=j;k<j+4;k++)
                move[graph[i][k]]++;
            if(move[1]==4 || move[2]==4)
                return 1;
        }
    //diagonal
    if(play3(3, 5)) return 1;
    if(play3(4, 5)) return 1;
    if(play3(5, 5)) return 1;
    if(play3(6, 5)) return 1;
    if(play3(3, 4)) return 1;
    if(play3(4, 4)) return 1;
    if(play3(5, 4)) return 1;
    if(play3(6, 4)) return 1;
    if(play3(3, 3)) return 1;
    if(play3(4, 3)) return 1;
    if(play3(5, 3)) return 1;
    if(play3(6, 3)) return 1;
    
    if(play33(0, 3)) return 1;
    if(play33(1, 3)) return 1;
    if(play33(2, 3)) return 1;
    if(play33(3, 3)) return 1;
    if(play33(0, 4)) return 1;
    if(play33(1, 4)) return 1;
    if(play33(2, 4)) return 1;
    if(play33(3, 4)) return 1;
    if(play33(0, 5)) return 1;
    if(play33(1, 5)) return 1;
    if(play33(2, 5)) return 1;
    if(play33(3, 5)) return 1;
    
    return 0;
}

int play(int al, int player)
{
    int a=0, b=0;
    int i, j, k;
    
    //make the move
    graph[al][po[al]-1]=1, graph[player][po[player]]=2;
    
    //score
    //horizontal
    for(i=5;i>=0;i--)
        for(j=0;j<=3;j++){
            int move[3]={0, 0, 0};
            for(k=j;k<j+4;k++)
                move[graph[k][i]]++;
            if(move[2]==0)
                a+=score1[move[1]];
            if(move[1]==0)
                b+=score2[move[2]];
        }
    //vertical
    for(i=0;i<=6;i++)
        for(j=0;j<=2;j++){
            int move[3]={0, 0, 0};
            for(k=j;k<j+4;k++)
                move[graph[i][k]]++;
            if(move[2]==0)
                a+=score1[move[1]];
            if(move[1]==0)
                b+=score2[move[2]];
        }
    //diagonal
    play2(3, 5, a, b);
    play2(4, 5, a, b);
    play2(5, 5, a, b);
    play2(6, 5, a, b);
    play2(3, 4, a, b);
    play2(4, 4, a, b);
    play2(5, 4, a, b);
    play2(6, 4, a, b);
    play2(3, 3, a, b);
    play2(4, 3, a, b);
    play2(5, 3, a, b);
    play2(6, 3, a, b);
    
    play22(0, 3, a, b);
    play22(1, 3, a, b);
    play22(2, 3, a, b);
    play22(3, 3, a, b);
    play22(0, 4, a, b);
    play22(1, 4, a, b);
    play22(2, 4, a, b);
    play22(3, 4, a, b);
    play22(0, 5, a, b);
    play22(1, 5, a, b);
    play22(2, 5, a, b);
    play22(3, 5, a, b);
    
    //undo the move
    graph[al][po[al]-1]=0, graph[player][po[player]]=0;
    
    return a-b;
}

void print()
{
    int i, j;
    for(i=5;i>=0;i--){
        for(j=0;j<=6;j++)
            cout << graph[j][i] << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int input;
    
    //welcome!
    cout << "Welcome to Connect Four!" << endl, cout << endl;
    print();
    
    //player move first
    cout << "Please make your move!" << endl;
    cin >> input, input--;
    graph[input][po[input]++]=2;
    print();
    
    
    while(true){
        int Max=-INF, p=-1;
        int i, j;
        
        //search for the best move
        for(i=0;i<=6;i++){
            int Min=INF;
            if(po[i]>5)
                continue;
            po[i]++;
            for(j=0;j<=6;j++){
                if(po[j]>=6)
                    continue;
                int cnt=play(i, j);
                if(cnt<Min)
                    Min=cnt;
            }
            po[i]--;
            if(Min>Max && Min!=INF)
                Max=Min, p=i;
        }
        
        //al play
        graph[p][po[p]++]=1;
        cout << p+1 << endl;
        print();
        
        //check for win
        if(win()){
            cout << "Al win!" << endl;
            return 0;
        }
        
        //check for tie
        bool tie=true;
        for(i=0;i<7;i++)
            for(j=0;j<6;j++)
                if(!graph[i][j])
                    tie=false;
        if(tie)
            break;
        
        //player play
        cout << "Please make your move!" << endl;
        while(true){
            cin >> input, input--;
            if(po[input]<=5){
                graph[input][po[input]++]=2;
                break;
            }
            cout << "Invalid Input!" << endl;
        }
        print();
        
        //check for win
        if(win()){
            cout << "You win!" << endl;
            return 0;
        }
    }
    
    cout << "It's a tie!" << endl;
    
    return 0;
}
