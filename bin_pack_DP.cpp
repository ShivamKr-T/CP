auto bin_pack_DP = [&](vector<int> & v)->int{
    int n = v.size();
    double W = log(k);
    vector<double> wt(n);
    for (int i = 0; i < n; i++)
        wt[i] = log(v[i]);
    sort(w.begin(), w.end(), greater<double>());

    vector<double> bins;
    for (double wti : wt) {
        bool placed = false;
        for (double &load : bins) {
            if (load + wti < W) {
                load += wti;
                placed = true;
                break;
            }
        }
        if (!placed) {
            bins.push_back(wti);
        }
    }
    return bins.size();
};
