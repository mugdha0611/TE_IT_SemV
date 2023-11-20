#include <iostream>
#include <vector>
using namespace std;

void findSoS(vector <int> &arr, int index, int target, vector <int> &currentSubset, vector <vector<int>> &result){
    //when target becomes zero subset is found 
    if(target == 0){
        result.push_back(currentSubset);
    }

    if(index >= arr.size() || target<0){
        return;
    }

    //updating current state
    currentSubset.push_back(arr[index]);
    findSoS(arr,index+1, target - arr[index], currentSubset, result);

    //exclude current element 
    currentSubset.pop_back();
    findSoS(arr, index+1, target, currentSubset, result);
}

int main(){
    int n;
    cout<<"\nEnter the no of integers:"<<endl;
    cin>>n;
    vector <int> arr(n);
    cout<<"\nenter the integers:"<<endl;
    for(int i = 0; i<n; i++){
        cin>>arr[i];
    }

    int target;
    cout<<"\nEnter target sum:"<<endl;
    cin>>target;

    vector <int> currentSubset;
    vector<vector<int>> result;
    findSoS(arr,0,target,currentSubset,result);
    if(result.empty()){
        cout<<"\n no found:"<<endl;
    }else{
        cout<<"\nSubset with sum"<<target<<"are :"<<endl;
        for(const vector <int> &subset : result){
            for(int num : subset){
                cout<<num<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}