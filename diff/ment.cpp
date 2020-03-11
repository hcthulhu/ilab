void Stack::Aritmetics(node* root) {
    if (root->left != nullptr){
        Aritmetics(root->left);
        Aritmetics(root->right);
    }
    Op(root->val);
}

#include <string>

int main() {
    std::string str1 = "hello";
    std::string str2 = "_world";
    str1 += str2;

    std::string str1("hello");
    std::string str2(str1);
    std::string str3('h', 10);

    c_str();
    int sz = str2.size();
}

// stack 
// push
// pop
// Aritmetics
