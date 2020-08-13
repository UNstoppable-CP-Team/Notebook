//Manacher algorithm, complexity O(n)
int n; //length of the srtring
int d1[n], d2[n]; //d1 longest odd palindrome with center i, d2 longest even palindrome with center i
for (int i = 0, l = 0, r = -1; i < n; i++) { //odd
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1); //current lenght (half length)
    while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
        k++;
    }
    d1[i] = k--;
    if (i + k > r) { //updating (l, r)
        l = i - k;
        r = i + k;
    }
}
for (int i = 0, l = 0, r = -1; i < n; i++) { //even
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1); //current lenght (half length)
    while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
        k++;
    }
    d2[i] = k--;
    if (i + k > r) { //updating (l, r)
        l = i - k - 1;
        r = i + k ;
    }
}
//Taken from: https://cp-algorithms.com/string/manacher.html
