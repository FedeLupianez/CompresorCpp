#include <iostream>
#include <array>
#include <vector>
#include <fstream>

struct Node {
    char data;          // Dato almacenado en el nodo
    Node* left;        // Puntero al hijo izquierdo
    Node* right;       // Puntero al hijo derecho

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, char value) {
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


// Función para buscar un valor en el árbol
void searchValue(Node* root, char value, std::string &actualRoad){
    if (root->data == value){
        std::cout << "valor encontrado\n\n";
        return;
    }

    if (root == nullptr){
        std::cout << "valor no encontrado\n\n";
        return;
    }

    if (root->data > value){
        actualRoad += "0";
        searchValue(root->left, value, actualRoad);
    }else{
        actualRoad += "1";
        searchValue(root->right, value, actualRoad);
    }

}

// Funcion para insertar los nodos en el árbol
Node* createTree(){
    Node* root = nullptr;
    std::array< int, 95 > values = {
        73, 67, 126, 36, 97, 108, 86, 110, 114, 112, 49, 81, 59, 105, 43, 51, 70, 92, 
        71, 44, 94, 89, 77, 124, 55, 103, 62, 115, 50, 72, 123, 75, 38, 127, 35, 58, 125,
        41, 88, 101, 63, 61, 84, 54, 53, 42, 60, 91, 46, 32, 90, 48, 96, 120, 118, 82, 
        79, 116, 68, 64, 102, 80, 119, 66, 98, 113, 65, 122, 74, 34, 121, 76, 78, 87, 33, 47, 109, 
        104, 83, 52, 95, 57, 85, 111, 45, 93, 37, 107, 39, 100, 69, 117, 56, 106, 40,
    };

    for (int &letter : values){
        root = insert(root, letter);
    }
    return(root);
}


int main() {
    Node* root = createTree();
    std::string road_to_value;

    searchValue(root, 'f', road_to_value);
    std::cout << road_to_value << std::endl;
    
    delete root;

    return (0);
}