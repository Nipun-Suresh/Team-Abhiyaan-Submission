/*
Question: Find minimum number of swaps required to convert a random configuration of bits into one containing
contiguous blocks of 1s
Logic:
The number of swaps required depends on:
    1) Number of 1s that need to be moved
    2) Location of the block
To minimize 1), we choose the largest exisiting contiguous block of 1s, and swap all other 1s towards it
To minimize 2), we prefer blocks closer to the centre when many blocks are of same size

Once the appropriate block is chosen, number of swaps is calculated mathematically
*/


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//represents lower and upper index of a contiguous block of 1s
class Limits
{
    int lowLim,upLim;
    public:
    //since all functions are small, defined within class
    Limits()
    {lowLim=upLim=0;}
    void iniLow(int x) {lowLim=x;}
    void iniUp(int x) {upLim=x;}
    int getLow() {return lowLim;}
    int getUp() {return upLim;}
    void print()
    {cout<<endl<<lowLim<<" "<<upLim;}
    int width()
    {return (upLim-lowLim);}
};

//used to choose appropriate block
int maxIndex(int*,int);

int main()
{
    int size;
    cin>>size;
    int* arr=new int[size];

    for (int i=0,temp;i<size;i++)
    {
        cin>>temp;
        arr[i]=temp;
    }
    
    Limits* set=new Limits[size/2]; //max number of contiguous blocks is size/2
    int onPath=0; //whether pointer is in a block or not
    Limits temp;
    int count=0;
    for (int i=0;i<size;i++)
    {
        if ((arr[i]==1)&&(onPath==0))   //indicates beginning of block
        {
            temp.iniLow(i);
            onPath=1;
        }
        else if ((arr[i]==0)&&(onPath==1))  //indicates conclusion of block
        {
            temp.iniUp(i-1);
            set[count]=temp;
            count++;
            onPath=0;        
        }
        else if ((arr[i]==1)&&(i==size-1))  //handles exception when array ends with 1
        {
            temp.iniUp(i);
            set[count]=temp;
            count++;
            onPath=0;
        }
    }
    int* oneBlock=new int[count];
    for (int i=0;i<count;i++)
        oneBlock[i]=(set[i]).width();
        
        
    int index=maxIndex(oneBlock,count);
    int lower=(set[index]).getLow();    //lower limit of block
    int upper=(set[index]).getUp();     //upper limit of block
    
    int minSwaps=0;   //contains final output
    
    //goes leftward from lower limit, searches for 1s
    for (int i=lower-1,count=1;i>=0;i--)
    {
        if (arr[i]==1)
        {
            minSwaps+=(lower-count-i);
            count++;
        }
    }
    //goes rightward from upper limit, searches for 1s
    for (int i=upper+1,count=1;i<size;i++)
    {
        if (arr[i]==1)
        {
            minSwaps+=(i-upper-count);
            count++;
        }
    }
    cout<<minSwaps;
    return 0;
}

int maxIndex(int* vec,int size)
{
    int max=0;
    for (int i=1;i<size;i++)
        if (vec[max]<vec[i])
            max=i;
            
    //in case more than 1 block of same length exists, block closer to centre
    //and thus easier to swap to must be preferred
    vector <int> vec_temp,vec_rec;
    int temp;
    for (int i=0;i<size;i++)
        if (vec[max]==vec[i])
        {
            vec_rec.push_back(i);
            temp=abs(i-size/2);
            vec_temp.push_back(temp);
        }
    temp=vec_temp.size();
    int num=0;
    for (int i=1;i<temp;i++)
    {
        if (vec_temp.at(num)>vec_temp.at(i))
            num=i;
    }
    max=vec_rec.at(num);    
            
    return max;
}

