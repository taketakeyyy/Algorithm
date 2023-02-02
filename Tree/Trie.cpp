#include <bits/stdc++.h>
using namespace std;


// Trie木
template <typename T>
class Trie {
    private:
        // Trie木用のノード
        struct Node {
            map<char, Node*> next;
            Node *prev;
            char moji;
            bool is_endnode;  // ある文字列の終端ノード（受理状態）か？
            Node() {
                is_endnode = false;
            }
        };
        Node root;

    public:
        Trie() {
            root = Node();
        }

        // 文字列Sを追加
        // O(|S|)
        void add(string const &S) {
            Node *now_ptr = &root;
            for(T i=0; i<(T)S.size(); i++) {
                if (now_ptr->next.count(S[i])) {
                    // すでに文字が存在する場合、その子をたどる
                    now_ptr = now_ptr->next[S[i]];
                    if (i == (T)S.size()-1) now_ptr->is_endnode = true;
                    continue;
                }
                else {
                    // 文字が存在しない場合、新しく分岐木を作る
                    Node *child_ptr = new Node();
                    child_ptr->moji = S[i];
                    child_ptr->prev = now_ptr;
                    now_ptr->next[S[i]] = child_ptr;
                    if (i == (T)S.size()-1) child_ptr->is_endnode = true;
                    now_ptr = child_ptr;
                }
            }
        }

        // 文字列SがTrie木に存在するかを返す
        // O(|S|)
        bool search(string const &S) {
            Node *now_ptr = &root;
            for(T i=0; i<(T)S.size(); i++) {
                if (!now_ptr->next.count(S[i])) return false;
                now_ptr = now_ptr->next[S[i]];
            }
            if (now_ptr->is_endnode) return true;
            return false;
        }

        // 文字列Sと、Trie木に存在する文字列との最長共通接頭辞（LCP）の長さを返す
        // 文字列S自体がTrie木に存在する場合、それ以外とのLCPを返す
        // O(|S|)
        T lcp_len_exclude(string const &S) {
            T res = 0;
            T depth = 0;
            Node *now_ptr = &root;
            for(T i=0; i<(T)S.size(); i++) {
                if (!now_ptr->next.count(S[i])) break;

                now_ptr = now_ptr->next[S[i]];
                depth++;
                if ((T)now_ptr->next.size() >= 2) res = depth;
                else if (i==(T)S.size()-1 && now_ptr->next.size()>=1) res = depth;
                else if (i!=(T)S.size()-1 && now_ptr->is_endnode) res = depth;
            }
            return res;
        }

        // 文字列Sと、Trie木に存在する文字列との最長共通接頭辞（LCP）の長さを返す
        // 文字列S自体がTrie木に存在する場合、S.size()を返す
        // O(|S|)
        T lcp_len(string const &S) {
            T depth = 0;
            Node *now_ptr = &root;
            for(T i=0; i<(T)S.size(); i++) {
                if (!now_ptr->next.count(S[i])) break;
                now_ptr = now_ptr->next[S[i]];
                depth++;
            }
            return depth;
        }
};

void test1() {
    cout << "===test1===" << endl;
    Trie<int> trie;

    // Trie木に "FIREMAN" の文字列を追加
    trie.add("FIREMAN");

    // Trie木に "FIRE" の文字列は存在するか？
    string s = "FIRE";
    cout << (trie.search(s) ? "Yes" : "No") << endl;
    // No

    // LCP（最長共通接頭辞）になら "FIRE" は存在する
    int len = trie.lcp_len(s);
    cout << s.substr(0,len) << endl;
    // FIRE

    // "FIRE" 追加後は、"FIRE" は見つかる（それはそう）
    trie.add("FIRE");
    cout << (trie.search("FIRE") ? "Yes" : "No") << endl;
    // Yes
}

void test2() {
    cout << "===test2===" << endl;
    Trie<int> trie;

    // 文字列を追加する
    trie.add("FIREMAN");
    trie.add("FIREARM");
    trie.add("FIREWORK");

    {// Trie木に存在する文字列と、 "FIREWOMAN" とのLCPは？
        string s = "FIREWOMAN";
        int len = trie.lcp_len(s);
        cout << len << endl;
        cout << s.substr(0,len) << endl;
        // 6
        // FIREWO
    }
    {// Trie木に "FIREMAN" は存在するので、LCPは "FIREMAN" そのもの。
        string s = "FIREMAN";
        int len = trie.lcp_len(s);
        cout << len << endl;
        cout << s.substr(0,len) << endl;
        // 7
        // FIREMAN
    }
    {// Trie木の "FIREMAN" を除外したい場合はこっちを使う。するとLCPは "FIRE" になる。
        string s = "FIREMAN";
        int len = trie.lcp_len_exclude(s);
        cout << len << endl;
        cout << s.substr(0,len) << endl;
        // 4
        // FIRE
    }
}


int main() {
    test1();
    test2();
    return 0;
}