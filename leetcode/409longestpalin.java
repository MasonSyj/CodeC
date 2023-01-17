class Solution {
public int longestPalindrome(String s) {
    if (s == null || s.length() < 1) return 0;
    Set<Character> set = new HashSet<>();
    for (int i = 0; i < s.length(); i++) {
        if (set.contains(s.charAt(i))) set.remove(s.charAt(i));
        else set.add(s.charAt(i));
    }
    if (set.size() <= 1) return s.length();
    return s.length() - set.size() + 1;
    
}
    
class Solution {
    public int longestPalindrome(String s) {
        int[] count = new int[128];
        for (char c: s.toCharArray())
            count[c]++;

        int ans = 0;
        for (int v: count) {
            ans += v / 2 * 2;
            if (ans % 2 == 0 && v % 2 == 1)
                ans++;
        }
        return ans;
    }
}