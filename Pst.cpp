// Author : Pandit Deepesh Kumar Sharma (The-Pace)
// dk30390
// Mkthnum , spoj , Persistent Segment Tree.
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define M 100005

struct pst
{
    int val;
    pst *left;
    pst *right;
    pst (int _val,pst *_left,pst *_right)
    {
        val=_val;
        left=_left;
        right=_right;
    }
};

pst *self=new pst(0,NULL,NULL);

pst *update(pst *prev,pst *curr,int l,int r,int idx)
{
    if(idx>=l && idx<=r)
    {
        curr=new pst(0,self,self);
        if(l==r){
            curr->val=1;
            return curr;
        }
        int mid=(l+r)>>1;

         curr->left=update(prev->left,curr->left,l,mid,idx);
         curr->right=update(prev->right,curr->right,mid+1,r,idx);

        curr->val=curr->left->val+curr->right->val;
        return curr;
    }
    else
        return prev;
}

int query(pst *L,pst *R,int k,int l,int r)
{
    if(l==r)
        return l;
    int mid=(l+r)>>1;
    int found=R->left->val-L->left->val;
    if(found>=k)
        query(L->left,R->left,k,l,mid);
    else
        query(L->right,R->right,k-found,mid+1,r);
}

pst *sgt[M];
int a[M],sorted[M];

int main()
{
    int i,j,k,n,m,q,l,r;
    cin>>n>>q;
    map <int,int> mp;
    for(i=0;i<n;i++)
    {
       cin>>a[i];
       mp.insert({a[i],i});
    }
    i=0;
    for(auto it:mp)
    {
        mp[it.first]=i;
        sorted[i]=it.first;
        i++;
    }

   self->left=self->right=self;
   sgt[0]=self;
   for(i=0;i<n;i++)
   {  if(i==0)
      sgt[i]=update(sgt[0],sgt[i],0,n-1,mp[a[i]]);
      else
      sgt[i]=update(sgt[i-1],sgt[i],0,n-1,mp[a[i]]);
   }
   while(q--)
   {
       cin>>l>>r>>k;
       if(l>1)
       cout<<sorted[query(sgt[l-2],sgt[r-1],k,0,n-1)]<<endl;
       else
       cout<<sorted[query(self,sgt[r-1],k,0,n-1)]<<endl;
   }
}
