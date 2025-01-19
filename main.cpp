#include <algorithm>
#include <asm-generic/errno.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

struct Node {
  char chr; // Dato almacenado en el nodo
  int frecuency;
  Node *left;  // Puntero al hijo izquierdo
  Node *right; // Puntero al hijo derecho

  Node(char ch, int frec, Node *l = nullptr, Node *r = nullptr)
      : chr(ch), frecuency(frec), left(l), right(r) {}
};

// Funcion para comparar nodos por su frecuencia :
bool compareNodes(Node *a, Node *b) { return (a->frecuency < b->frecuency); }

// Función para buscar un valor en el árbol
bool searchValue(Node *root, char value, std::string &actual_road) {

  // Si el nodo es null, significa que no encontramos el valor
  if (root == nullptr) {
    return (false);
  }

  // Si el nodo no tiene hijos y el char es el mismo que el valor, significa que
  // lo encontramos
  if (!root->left && !root->right && root->chr == value) {
    return (true);
  }

  // Agregamos un '0' al camino y buscamos en el hijo izquierdo
  actual_road.push_back('0');
  if (searchValue(root->left, value, actual_road)) {
    return (true);
  }
  // Si el valor no se encuentra acá, eliminamos el '0' que pusimos
  // anteriormente
  actual_road.pop_back();

  // Repetimos el proceso anterior pero del lado derecho
  actual_road.push_back('1');
  if (searchValue(root->right, value, actual_road)) {
    return (true);
  }
  actual_road.pop_back();

  return (false);
}

// Funcion para crear el árbol de Huffman
Node *HuffmanTree() {
  std::vector<Node *> nodes;

  for (int chr = 32; chr <= 127; chr++) {
    nodes.push_back(new Node(chr, 1));
  }

  while (nodes.size() > 1) {
    std::sort(nodes.begin(), nodes.end(), compareNodes);

    Node *left = nodes[0];
    Node *right = nodes[1];

    Node *combined =
        new Node('\0', left->frecuency + right->frecuency, left, right);

    nodes.erase(nodes.begin());
    nodes.erase(nodes.begin());

    nodes.push_back(combined);
  }

  return (nodes[0]);
}

void deleteTree(Node *root) {
  if (root == nullptr)
    return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

void followPath(Node *root, std::string path, int &actual_index, char &result) {

  if (root == nullptr) {
    result = (char)0;
    return;
  }

  if (!root->left && !root->right) {
    result = root->chr;
    return;
  }

  if (path[actual_index] == '0') {
    actual_index++;
    followPath(root->left, path, actual_index, result);
  } else {
    actual_index++;
    followPath(root->right, path, actual_index, result);
  }
}

void encodeFile(std::string file_path, Node *root) {
  std::ifstream original(file_path);
  std::ofstream encoded("encoded.txt");

  if (!original.is_open() || !encoded.is_open()) {
    std::cerr << "Error al Abrir el archivo\n";
    deleteTree(root);
    return;
  }

  if (original.peek() == std::ifstream::traits_type::eof()) {
    std::cerr << "El archivo esta vacio\n";
    deleteTree(root);
    return;
  }

  std::string line;
  std::string road;

  while (std::getline(original, line)) {
    for (char chr : line) {
      if (searchValue(root, chr, road)) {
        encoded << road;
      }
      road.clear();
    }
    encoded << '\n';
  }

  original.close();
  encoded.close();
}

void decodeFile(std::string file_path, Node *root) {
  std::ifstream encoded(file_path);
  std::ofstream decoded("decodeFile.txt");

  if (!encoded.is_open() || !decoded.is_open()) {
    std::cerr << "Error al abrir el archivo\n";
    return;
  }

  if (encoded.peek() == std::ifstream::traits_type::eof()) {
    std::cerr << "EL archivo está vacío";
    return;
  }

  std::string line;
  int actual_index = 0;
  char result;
  while (std::getline(encoded, line)) {
    actual_index = 0;
    while (actual_index < line.length()) {
      followPath(root, line, actual_index, result);

      if (result != (char)0) {
        decoded << result;
      }
    }

    decoded << '\n';
  }
}

int main() {
  Node *root = HuffmanTree();
  decodeFile("encoded.txt", root);
  deleteTree(root);
  return (0);
}
