// 三角形，旋转卡壳
ll getMost(Point* ploy, int n) {
	if(n == 2) return (ploy[1] - ploy[0]).dis2();
	ploy[n] = ploy[0];
	int opa = 1;
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		while(((ploy[opa] - ploy[i]) ^ (ploy[i+1] - ploy[i])) 
			< ((ploy[(opa+1)%n] - ploy[i]) ^ (ploy[i+1] - ploy[i]))) 
			opa = (opa + 1) % n;
		ans = max(ans, (ploy[opa] - ploy[i]).dis2());
		// i与opa是对重点
		// printf("%d  %d\n", i, opa);
	}
	return ans;
}