#include<bits/stdc++.h>

using namespace std;
struct node
{
    node*nxt;
    int val;
};

void addnode(node* &l,int v)
{
    node* newnode=new node;
    newnode->nxt=l;
    newnode->val=v;
    l=newnode;
}

void print(node* l)
{
    while(l!=NULL)
    {
        cout<<l->val<<" \n"[l->nxt==NULL];
        l=l->nxt;
    }
}

void reverse(node*&l)
{
    node *temp1=l,*temp2=NULL;
    while(temp1!=NULL)
        addnode(temp2,temp1->val),temp1=temp1->nxt;
    l=temp2;
}

void merge(node*list1,int sz1,node*list2,int sz2)
{
    node* head=list1;
    int sz=sz1+sz2;
    node* temp=NULL;
    while(sz1>0 && sz2>0)
    {
        if(list1->val<=list2->val)
            addnode(temp,list1->val),list1=list1->nxt,sz1--;
        else
            addnode(temp,list2->val),list2=list2->nxt,sz2--;
    }
    while(sz1>0)
        addnode(temp,list1->val),list1=list1->nxt,sz1--;
    while(sz2>0)
        addnode(temp,list2->val),list2=list2->nxt,sz2--;
    reverse(temp);
    while(sz>0)
        head->val=temp->val,head=head->nxt,temp=temp->nxt,sz--;
}

void mergesort(int s,int e,node*l)
{
    if(s==e)
        return;
    int mid=(s+e)/2;
    node*temp=l;
    for(int i=0;i<mid+1-s;i++)
        temp=temp->nxt;
    mergesort(s,mid,l);
    mergesort(mid+1,e,temp);
    merge(l,mid-s+1,temp,e-(mid+1)+1);
}

int main()
{
    node* l=NULL;
    int arr[]={5,2,-1,1};
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=n-1;i>=0;i--)
        addnode(l,arr[i]);
    cout<<"Original one:\n";print(l);
    cout<<endl;
    mergesort(0,n-1,l);
    cout<<"After sorting:\n";print(l);
    return 0;
}
