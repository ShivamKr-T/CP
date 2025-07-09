auto nge=[&](vector<int> &arr){
    int n=arr.size();
    stack<int> st;
    vector<int> res(n);
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top()<=arr[i]) st.pop();
        res[i]=(st.empty()?-1:st.top());
        st.push(arr[i]);
    }
    return res;
};

auto nse=[&](vector<int> &arr){
    int n=arr.size();
    stack<int> st;
    vector<int> res(n);
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top()>=arr[i]) st.pop();
        res[i]=(st.empty()?-1:st.top());
        st.push(arr[i]);
    }
    return res;
};

auto pge=[&](vector<int> &arr){
    int n=arr.size();
    stack<int> st;
    vector<int> res(n);
    for(int i=0;i<n;i++){
        while(!st.empty() && st.top()<=arr[i]) st.pop();
        res[i]=(st.empty()?-1:st.top());
        st.push(arr[i]);
    }
    return res;
};

auto pse=[&](vector<int> &arr){
    int n=arr.size();
    stack<int> st;
    vector<int> res(n);
    for(int i=0;i<n;i++){
        while(!st.empty() && st.top()>=arr[i]) st.pop();
        res[i]=(st.empty()?-1:st.top());
        st.push(arr[i]);
    }
    return res;
};
