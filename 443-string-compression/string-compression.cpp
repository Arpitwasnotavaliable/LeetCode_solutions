class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int write = 0;  // position to write the compressed result
        int read = 0;   // position to read the next group start

        while (read < n) {
            char currentChar = chars[read];
            int count = 0;

            // count consecutive occurrences of currentChar
            while (read < n && chars[read] == currentChar) {
                read++;
                count++;
            }

            // write the character
            chars[write++] = currentChar;

            // write the count (if more than 1), digit by digit
            if (count > 1) {
                string countStr = to_string(count);
                for (char c : countStr) {
                    chars[write++] = c;
                }
            }
        }

        return write;
    }
};