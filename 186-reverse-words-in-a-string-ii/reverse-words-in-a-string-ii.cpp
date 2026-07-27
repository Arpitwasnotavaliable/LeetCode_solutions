void BigRev(vector<char>& s){
    int start=0;
    int end=s.size()-1;
    while(start<end){
        swap(s[start],s[end]);
        start++;
        end--;
    }
}


class Solution {
public:
    void reverseWords(vector<char>& s) {
        
        BigRev(s);

        int ss=0,se=0,te=0;
        while(ss<s.size()){
            while(se<s.size()&&s[se]!=' '){
                se++;
            }
            te=se;
            se--;
            while(ss<se){
                swap(s[ss],s[se]);
                ss++;
                se--;
            }

            ss=te+1;
            se=ss;
        }


    }
};