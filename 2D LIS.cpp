
//2D LIS O(nlogn)
typedef pair<int,int> pii;
pii p[100005];
set<pii> s[100005];
set<pii>::iterator it,it1;
int main(){
	int n,i,lo,hi,mid,lb,k,t,cs = 1;
	scanf("%d",&n);
	for(i = 0;i<n;i++) scanf("%d %d",&p[i].first,&p[i].second);
	s[0].insert(p[0]);
	k = 0;
	for(i = 1;i<n;i++){
		lo = 0; hi = k,lb = -1;
		while(lo<=hi){
			mid = (lo + hi) / 2;
			it = s[mid].lower_bound(p[i]);
			if(it!=s[mid].begin() ){
				it1 = it,it1--;
				if((*it1).first==p[i].first) it --;
			}
			if(it!=s[mid].begin() && (*(--it)).second<p[i].second)
lo = mid + 1,lb = max(lb,mid);	
			else hi = mid - 1;
		}
		lb++;
		k = max(k,lb);
		it = s[lb].lower_bound(pii(p[i].first,-inf));
		if(it==s[lb].end() || ((*it).first>p[i].first || (*it).second>p[i].second))
			s[lb].insert(p[i]);
		it = s[lb].upper_bound(p[i]);
		while(it!=s[lb].end()){
			if((*it).first>=p[i].first && (*it).second >= p[i].second){
				it1 = it, it1++;
				s[lb].erase(it);
				it = it1;
			}
			else break;
		}
	}
	printf("%d\n",k+1);
	return 0;
}
