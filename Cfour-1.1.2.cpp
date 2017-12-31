#include <iostream>

#define INF 1000000000

using namespace std;

int score1[5]={0, 1, 5, 9999, 99999999};
int score2[5]={0, 1, 5, 9999, 9999999};

int graph[7][6], po[7];

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
    for(i=3;i<=5;i++)
        for(j=3;j<=6;j++){
            int move[3]={0, 0, 0};
            for(k=0;k<=3;k++)
                move[graph[j-k][i-k]]++;
            if(move[1]==4 || move[2]==4)
                return 1;
        }
    for(i=3;i<=5;i++)
        for(j=0;j<=3;j++){
            int move[3]={0, 0, 0};
            for(k=0;k<=3;k++)
                move[graph[j+k][i-k]]++;
            if(move[1]==4 || move[2]==4)
                return 1;
        }
    
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
    for(i=3;i<=5;i++)
        for(j=3;j<=6;j++){
            int move[3]={0, 0, 0};
            for(k=0;k<=3;k++)
                move[graph[j-k][i-k]]++;
            if(move[2]==0)
                a+=score1[move[1]];
            if(move[1]==0)
                b+=score2[move[2]];
        }
    for(i=3;i<=5;i++)
        for(j=0;j<=3;j++){
            int move[3]={0, 0, 0};
            for(k=0;k<=3;k++)
                move[graph[j+k][i-k]]++;
            if(move[2]==0)
                a+=score1[move[1]];
            if(move[1]==0)
                b+=score2[move[2]];
        }
    
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
    int input, empty=41;
    
    //welcome!
    cout << "Welcome to Connect Four!" << endl;
    print();
    
    //player move first
    cout << "Please make your move!" << endl;
    while(true){
        cin >> input, input--;
        if(input>=0 && input<=6 && po[input]<=5){
            graph[input][po[input]++]=2;
            break;
        }
        cout << "Invalid input!" << endl;
    }
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
        empty--;
        
        
        //al play
        cout << p+1 << endl;
        graph[p][po[p]++]=1;
        print();
        if(win()){
            cout << "Al win!" << endl;
            return 0;
        }
        
        //check for tie
        if(!empty)
            break;
        
        //player play
        cout << "Please make your move!" << endl;
        while(true){
            cin >> input, input--;
            if(input>=0 && input<=6 && po[input]<=5){
                graph[input][po[input]++]=2;
                break;
            }
            cout << "Invalid input!" << endl;
        }
        print();
        if(win()){
            cout << "You win!" << endl;
            return 0;
        }
        empty--;
    }
    
    cout << "It's a tie!" << endl;
    
    return 0;
}
