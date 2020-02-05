#include <iostream>

using namespace std;

void insertSort(int a[], int n);

int main(void){
	int list[20];
	int num, n, i, j;
	
	cout<< "input n:" <<endl;
	cin >> n;
	cout<<"input "<< n << " numbers:"<< endl;
	for(i=0; i<n; i++)
	 cin >> list[i];
	 
	insertSort(list, n);
	cout << "after sorting:" <<endl; 
	for(i=0; i<n; i++)
		cout<<list[i] <<endl;
		
	return 0;
}

void insertSort(int a[], int n){ //插入排序 
	int i, j, temp;
	for(i=1; i<n; i++){
		temp = a[i];
		j = i-1;
		while(j>=0 && a[j]<temp){ //从后往前挪 
			a[j+1] = a[j];
			j = j-1;
		}
		a[j+1] = temp;	//挪到位置后，插入进去	
	}
}
