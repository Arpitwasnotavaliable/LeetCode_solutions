
class Solution {
public:
    using Set = set<string>;

    string s;
    int pos = 0;

    Set parseExpr() {
        Set result = parseTerm();

        while (pos < s.size() && s[pos] == ',') {
            pos++;

            Set next = parseTerm();

            result.insert(next.begin(), next.end());
        }

        return result;
    }

    Set parseTerm() {
        Set result = {""};

        while (pos < s.size() &&
               s[pos] != ',' &&
               s[pos] != '}') {

            Set next;

            if (s[pos] == '{') {
                pos++;

                next = parseExpr();

                pos++;
            }
            else {
                next.insert(string(1, s[pos]));
                pos++;
            }

            Set temp;

            for (const string& a : result) {
                for (const string& b : next) {
                    temp.insert(a + b);
                }
            }

            result = temp;
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        Set ans = parseExpr();

        return vector<string>(ans.begin(), ans.end());
    }
};

