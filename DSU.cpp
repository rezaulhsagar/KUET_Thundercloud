//DSU
const int N 100000;
int parent[N + 5];

void build (){
	for (int i = 1; i <= N; i++){
		parent[i] = i;
	}
}

int findparent (int a){
	if (parent[a] == a) return a;
	return parent[a] = findparent (parent[a]);
}

void makeset (int a, int b){
	int pa = findparent (a);
	int pb = findparent (b);
	pa = parent[pb];
}
