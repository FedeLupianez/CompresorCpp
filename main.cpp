#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

struct Node {
  char data;   // Dato almacenado en el nodo
  Node *left;  // Puntero al hijo izquierdo
  Node *right; // Puntero al hijo derecho

  Node(int value) {
    data = value;
    left = nullptr;
    right = nullptr;
  }
};

Node *insert(Node *root, char value) {
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
void searchValue(Node *root, char value, std::string &actualRoad) {

  if (root == nullptr) {
    std::cout << "valor no encontrado\n\n";
    return;
  }

  if (root->data == value) {
    std::cout << "valor encontrado\n\n";
    return;
  }

  if (root->data > value) {
    actualRoad += "0";
    searchValue(root->left, value, actualRoad);
  } else {
    actualRoad += "1";
    searchValue(root->right, value, actualRoad);
  }
}

// Funcion para insertar los nodos en el árbol
Node *createTree() {
  Node *root = nullptr;
  std::array<int, 95> values = {
      73,  67,  126, 36,  97,  108, 86,  110, 114, 112, 49, 81,  59,  105,
      43,  51,  70,  92,  71,  44,  94,  89,  77,  124, 55, 103, 62,  115,
      50,  72,  123, 75,  38,  127, 35,  58,  125, 41,  88, 101, 63,  61,
      84,  54,  53,  42,  60,  91,  46,  32,  90,  48,  96, 120, 118, 82,
      79,  116, 68,  64,  102, 80,  119, 66,  98,  113, 65, 122, 74,  34,
      121, 76,  78,  87,  33,  47,  109, 104, 83,  52,  95, 57,  85,  111,
      45,  93,  37,  107, 39,  100, 69,  117, 56,  106, 40};

  for (int &letter : values) {
    root = insert(root, letter);
  }
  return (root);
}

void followPath(Node *root, std::string path, int index_direction,
                char &value) {

  if (root == nullptr)
    return;

  if (index_direction >= path.length()) {
    value = root->data;
    return;
  }
  std::cout << "hola";
  if (path[index_direction] == '0') {
    index_direction++;
    followPath(root->left, path, index_direction, value);
  } else {
    index_direction++;
    followPath(root->right, path, index_direction, value);
  }
}

void deleteTree(Node *root) {
  if (root == nullptr)
    return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

int main() {
  Node *root = createTree();
  /*std::string road_to_value;

  searchValue(root, 'j', road_to_value);
  std::cout << road_to_value << std::endl;
  char result = ' ';
  followPath(root, road_to_value, 0, result);
  std::cout << "valor encontrado : " << result << '\n';*/

  std::ifstream file("archivo.txt");
  std::ofstream write_file("archivo2.txt");

  if (file.peek() == std::ifstream::traits_type::eof()) {
    std::cerr << "El archivo de entrada esta vacio\n";
    deleteTree(root);
    return (1);
  }

  if (!file.is_open() || !write_file.is_open()) {
    std::cerr << "Hubo un problema al abrir el archivo\n";
    deleteTree(root);
    return (1);
  }

  std::string line;

  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string token;

    while (std::getline(stream, token, '.')) {
      for (char chr : token) {
        std::cout << chr << std::endl;
        std::string road_to_value;
        searchValue(root, chr, road_to_value);
        write_file << road_to_value << " ";
        road_to_value.clear();
      }
      write_file << '\n';
    }
  }
  file.close();
  write_file.close();
  deleteTree(root);
  return (0);
}
