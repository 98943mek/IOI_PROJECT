#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAXN = 100500;
int ans;

struct node{
	int max_height,min_height;
	int left,right,lazy;
}node[MAXN*4];

struct node tmp(int left,int right,int maxh,int minh){
	struct node tmp;
	tmp.left = left, tmp.right = right, tmp.max_height = maxh, tmp.min_height = minh, tmp.lazy = -1;
	return tmp;
}

void init(int idx,int left,int right){
	node[idx] = tmp(left,right,0,0);
	if(left != right){
		init(2*idx,left,(left+right)/2);
		init(2*idx+1,(left+right)/2+1,right);
	}
}

void update(int idx,int L,int R,int H){
	if(node[idx].lazy != -1){
		node[idx].max_height = max(node[idx].max_height,node[idx].lazy);
		node[idx].min_height = max(node[idx].min_height,node[idx].lazy);
		
		node[2*idx].lazy = node[idx].lazy;
		node[2*idx+1].lazy = node[idx].lazy;
		node[idx].lazy = -1;
	}
	
	if(L > node[idx].right || R < node[idx].left) return ;
	
	if(L <= node[idx].left && node[idx].right <= R){
		if(H > node[idx].min_height) node[idx].lazy = H;
		return ;
	}	
	
	update(2*idx,L,R,H);
	update(2*idx+1,L,R,H);
	
	node[idx].min_height = min(node[2*idx].min_height,node[2*idx+1].min_height);
	node[idx].max_height = max(node[2*idx].max_height,node[2*idx+1].max_height);
}

int query(int idx,int L,int R,int H){
	if(node[idx].lazy != -1){
		node[idx].max_height = max(node[idx].max_height,node[idx].lazy);
		node[idx].min_height = max(node[idx].min_height,node[idx].lazy);
		
		node[2*idx].lazy = node[idx].lazy;
		node[2*idx+1].lazy = node[idx].lazy;
		node[idx].lazy = -1;
	}
	
	int result = 0;
	
	if(L > node[idx].right || R < node[idx].left) result = 0;
	else if(L <= node[idx].left && node[idx].right <= R && node[idx].max_height <= H) result = node[idx].right-node[idx].left+1;
	else if(L <= node[idx].left && node[idx].right <= R && node[idx].min_height > H) result = 0;
	else{
		result = query(2*idx,L,R,H) + query(2*idx+1,L,R,H);
		node[idx].max_height = max(node[2*idx].max_height,node[2*idx+1].max_height);
		node[idx].min_height = min(node[2*idx].min_height,node[2*idx+1].min_height);
	}
	return result;
}

int main(){
	int C,N,A,B,H;
	scanf("%d",&C);
	while(C--){
		scanf("%d",&N); ans = 0;  init(1,0,MAXN);
		for(int i=1;i<=N;i++){
			scanf("%d %d %d",&A,&B,&H);
			ans += query(1,A,B,H);
			update(1,A,B,H);
			printf("%d\n",ans);
		}
		printf("%d\n",ans);
	}
	
	return 0;
}