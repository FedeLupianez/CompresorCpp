#include <iostream>

struct Node {
    int data;          // Dato almacenado en el nodo
    Node* left;        // Puntero al hijo izquierdo
    Node* right;       // Puntero al hijo derecho

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return (root);
}

// Mostrar el árbol en orden
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

// Función para buscar un valor en el árbol
void searchValue(Node* root, int value){
    if (root->data == value){
        std::cout << "valor encontrado\n\n";
        return;
    }

    if (root == nullptr){
        std::cout << "valor no encontrado\n\n";
        return;
    }

    if (root->data > value){
        searchValue(root->left, value);
        std::cout << "0";
    }else{
        searchValue(root->right, value);
        std::cout << "1";
    }

}

// Funcion para insertar los nodos en el árbol
Node* createTree(){
    Node* root = nullptr;
    root = insert(root, 100);
    root = insert(root, 25);
    root = insert(root, 75);
    root = insert(root, 10);
    root = insert(root, 39);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 33);
    root = insert(root, 45);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 12);
    root = insert(root, 17);
    root = insert(root, 11);
    root = insert(root, 13);
    root = insert(root, 16);
    root = insert(root, 18);
    root = insert(root, 31);
    root = insert(root, 35);
    root = insert(root, 30);
    root = insert(root, 32);
    root = insert(root, 34);
    root = insert(root, 36);
    root = insert(root, 43);
    root = insert(root, 47);
    root = insert(root, 42);
    root = insert(root, 44);
    root = insert(root, 46);
    root = insert(root, 48);
    root = insert(root, 61);
    root = insert(root, 55);
    root = insert(root, 67);
    root = insert(root, 53);
    root = insert(root, 57);
    root = insert(root, 51);
    root = insert(root, 54);
    root = insert(root, 56);
    root = insert(root, 58);
    root = insert(root, 65);
    root = insert(root, 64);
    root = insert(root, 66);
    root = insert(root, 69);
    root = insert(root, 68);
    root = insert(root, 70);
    root = insert(root, 86);
    root = insert(root, 79);
    root = insert(root, 93);
    root = insert(root, 77);
    root = insert(root, 81);
    root = insert(root, 76);
    root = insert(root, 78);
    root = insert(root, 80);
    root = insert(root, 82);
    root = insert(root, 91);
    root = insert(root, 95);
    root = insert(root, 90);
    root = insert(root, 92);
    root = insert(root, 94);
    root = insert(root, 96);
    return(root);
}


int main() {
    Node* root = createTree();
    std::cout << "arbol armado\n";

    searchValue(root, 1);
    
    delete root;

    return (0);
}