#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int* arr;
int main()
{
    int num;
    cin>>num;
    int sum;
    cin>>sum;
    int count=0;
    arr=new int[num];
    for(int i=0;i<num;i++)
        cin>>arr[i];
    sort(arr,arr+num);
    for(int i=0;i<num&&arr[i]<=sum/3;i++)
    {
        for(int j=i+1,k=num-1;j<k&&arr[k]>=sum/3;)
        {
            
            
            int sum1=arr[i]+arr[j]+arr[k];
            if(sum1>sum)
            {
                k--;
                continue;
            }
            else if(sum1==sum)
            {
               // cout<<arr[i]<<' '<<arr[j]<<' '<<arr[k]<<endl;
                count++;
                k--;
                j++;
                //break;
            }
            else if(sum1<sum)

            {
                j++;
                continue;
            }
        }
    }
    cout<<"wo yi yue du guan yu chao xi de shuo ming"<<endl;
    cout<<count<<endl;
  
    return 1;
}