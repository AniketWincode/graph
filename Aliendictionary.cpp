class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> indegree;
        for (auto& word : words) {
            for (char c : word) {
                graph[c] = unordered_set<char>();
                indegree[c] = 0;
            }
        }
        for (int i = 1; i < words.size(); ++i) {
            string& first = words[i - 1];
            string& second = words[i];
            int len = min(first.size(), second.size());
            for (int j = 0; j < len; ++j) {
                if (first[j] != second[j]) {
                    if (graph[first[j]].insert(second[j]).second) {
                        indegree[second[j]]++;
                    }
                    break;
                }
            }
            if (first.size() > second.size() && first.substr(0, len) == second.substr(0, len)) {
                return "";
            }
        }

        // indegree
        queue<char> q;
        for (auto& [c, deg] : indegree) {
            if (deg == 0) q.push(c);
        }
        string result;
        while (!q.empty()) {
            char c = q.front();
            q.pop();
            result += c;
            for (char neighbor : graph[c]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) q.push(neighbor);
            }
        }
        return result.size() == indegree.size() ? result : "";
    }
};
