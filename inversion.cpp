int merging(vi &vec, int low, int mid, int high) {
	int cnt = 0; vi temp; int left = low; int right =  mid + 1;
	while (left <= mid && right <= high) {
		if (vec[left] <= vec[right]) {temp.pb(vec[left]); left++;}
		else {temp.pb(vec[right]); cnt += (mid - left + 1); right++;}
	}
	while (left <= mid) {temp.pb(vec[left]); left++;}
	while (right <= high) {temp.pb(vec[right]); right++;}
	for (int i = low; i <= high; i++) vec[i] = temp[i - low];
	return cnt;
}
int merge_sort(vi &vec, int low, int high) {
	int cnt = 0;
	if (low >= high) return cnt;
	int mid = (low + high) / 2;
	cnt += merge_sort(vec, low, mid);
	cnt += merge_sort(vec, mid + 1, high);
	cnt += merging(vec, low, mid, high);
	return cnt;
}
