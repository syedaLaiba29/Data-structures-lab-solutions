#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    int a;
    cout<<"Enter the no of players ";
    cin>>a;
    
    int *score;
    score=(int*)malloc(a* sizeof(int));
    for (int i=0; i<a; i++)
    {
        cout<<"Enter the score of player "<<i+1<<" : ";
        cin>>score[i];
    }
    for (int i=0; i<a; i++)
    {
        cout<<"Player "<<i+1<<" : "<<score[i]<<endl;
    }
    score=nullptr;

    return 0;
}