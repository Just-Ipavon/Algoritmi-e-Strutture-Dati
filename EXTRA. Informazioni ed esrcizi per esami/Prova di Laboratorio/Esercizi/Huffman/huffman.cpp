#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr)
        : ch(ch), freq(freq), left(left), right(right) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

class Huffman {
private:
    Node* root = nullptr;
    unordered_map<char, string> codes;

    void generate_codes(Node* node, const string& current_code) {
        if (!node) return;

        if (!node->left && !node->right) {
            codes[node->ch] = current_code;
        }

        generate_codes(node->left, current_code + "0");
        generate_codes(node->right, current_code + "1");
    }

public:
    ~Huffman() {
        destroy_tree(root);
    }

    void destroy_tree(Node* node) {
        if (!node) return;
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }

    void build(const vector<pair<char, int>>& data) {
        priority_queue<Node*, vector<Node*>, Compare> pq;
        for (auto& [ch, freq] : data) {
            pq.push(new Node(ch, freq));
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            Node* merged = new Node('\0', left->freq + right->freq, left, right);
            pq.push(merged);
        }

        root = pq.top();
        generate_codes(root, "");
    }

    void print_codes(ostream& out) const {
        out << "Codici di Huffman:\n";
        for (const auto& [ch, code] : codes) {
            out << ch << ": " << code << "\n";
        }
    }

    const unordered_map<char, string>& get_codes() const {
        return codes;
    }

    Node* get_root() const {
        return root;
    }

    // Metodo di decodifica
    string decode(const string& encoded_str) const {
        string decoded = "";
        Node* current = root;
        for (char bit : encoded_str) {
            if (!current) break;
            if (bit == '0') {
                current = current->left;
            } else if (bit == '1') {
                current = current->right;
            } else {
                // Ignora caratteri non binari
                continue;
            }

            // Se siamo in una foglia, aggiungiamo il carattere decodificato
            if (current && !current->left && !current->right) {
                decoded += current->ch;
                current = root;
            }
        }
        return decoded;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in || !out) {
        cerr << "Errore apertura file.\n";
        return 1;
    }

    vector<pair<char, int>> data;
    char ch;
    int freq;

    while (in >> ch >> freq) {
        data.emplace_back(ch, freq);
    }

    Huffman h;
    h.build(data);
    h.print_codes(out);

    // Esempio: decodifica di una stringa codificata (da inserire o leggere)
    // Qui come esempio stringa codificata codici concatenati, ad esempio "010011..."
    string encoded_string;
    cout << "Inserisci la stringa codificata da decodificare (es. 010011...): ";
    cin >> encoded_string;

    string decoded = h.decode(encoded_string);
    out << "\nDecodifica della stringa '" << encoded_string << "': " << decoded << "\n";

    cout << "Codici Huffman generati e salvati in output.txt\n";
    cout << "Decodifica della stringa codificata: " << decoded << endl;

    return 0;
}
