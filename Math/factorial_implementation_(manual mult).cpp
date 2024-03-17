#include <bits/stdc++.h>
using namespace std;
int arr[1000];
int most_digit;
void fact(int n){

    int carry=0;
    for(int i=2;i<=n;i++){

        for(int j=0;j<=most_digit || carry;j++){
            int num = arr[j] * i + carry;
            arr[j] = num%10;
            carry=num/10;
            most_digit=max(j,most_digit);
        }

    }
}
int main(){
    int n;
    scanf("%d",&n);
    arr[0]=1;
    fact(n);


    for(int i=most_digit;i>=0;i--)
        printf("%d",arr[i]);
    printf("\n");
}
