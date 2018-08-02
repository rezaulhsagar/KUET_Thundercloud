//BIT
const int N = 100000;
int tree[N + 5];

void update (int idx, int val){
	while (idx <= n){
		tree[idx] += val;
		idx += idx & (-idx);
	}
}

int query (int idx){
	int sum = 0;
	while (idx > 0){
		sum += tree[idx];
		idx -= idx & (-idx);
	}
	return sum;
}
