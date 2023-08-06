#include <iostream>
#include "cctree.hpp"
#include "image.hpp"

void construct_image(TreeNode *node, Image &image, int row, int col, int spacing = 2)
{
    if (node != NULL)
    {
        std::string number = std::to_string(node->value);
        for (int i = 0; i < number.size(); i++)
        {
            image.set(row, col-i, number[number.size()-1-i]);
        }
        if (node->left != NULL && node->left->is_leaf() == 1)
            construct_image(node->left, image, row+1, col-spacing);
        else
            construct_image(node->left, image, row+1, col-spacing*2);
        if (node->right != NULL && node->right->is_leaf() == 1)
            construct_image(node->right, image, row+1, col+spacing);
        else
            construct_image(node->right, image, row+1, col+spacing*2);
    }
}

void show_tree(Tree &tree)
{
    if (tree.get_root() == NULL) return;
    Image tree_image(700, 700);
    construct_image(tree.get_root(), tree_image, 350, 350, 3);
    tree_image.trim();
    tree_image.show(0);
    std::cout << "\n";
}

std::string left_rotation_opt(Tree &tree)
{
    int number;
    std::cout << "Insira o número do nodo: ";
    std::cin >> number;
    std::string message = "[ SISTEMA ] >> Nodo " + std::to_string(number) + " rotacionado!";
    tree.left_rotation(tree.get_node(number));
    return message;
}

std::string right_rotation_opt(Tree &tree)
{
    int number;
    std::cout << "Insira o número do nodo: ";
    std::cin >> number;
    std::string message = "[ SISTEMA ] >> Nodo " + std::to_string(number) + " rotacionado!";
    tree.right_rotation(tree.get_node(number));
    return message;
}

std::string get_height_opt(Tree &tree)
{
    int number;
    std::cout << "Insira o número do nodo: ";
    std::cin >> number;
    std::string message = "[ SISTEMA ] >> A altura do nodo " + std::to_string(number) + " é: ";
    message.append(std::to_string(tree.get_node(number)->get_height()));
    std::system("clear");
    return message;
}

void in_order_opt(Tree &tree)
{
    std::system("clear");
    std::cout << "\n";
    std::cout << "[ RESULTADO ] >> [";
    tree.in_order_traversal();
    std::cout << "]\n\n";
}

void pre_order_opt(Tree &tree)
{
    std::system("clear");
    std::cout << "\n";
    std::cout << "[ RESULTADO ] >> [";
    tree.pre_order_traversal();
    std::cout << "]\n\n";
}

void post_order_opt(Tree &tree)
{
    std::system("clear");
    std::cout << "\n";
    std::cout << "[ RESULTADO ] >> [";
    tree.post_order_traversal();
    std::cout << "]\n\n";
}

std::string insertion_opt(Tree &tree)
{
    int value;
    std::cout << "\nInsira o valor a ser inserido na árvore: ";
    std::cin >> value;
    tree.insert(value);
    std::system("clear");
    std::string message = "[ SISTEMA ] >> Nó (";
    message.append(std::to_string(value));
    message.append(") inserido.");
    return message;
}

int main()
{
    Tree tree;           // Program Binary Tree
    std::string message; // Boot Message
    message.append("[ SISTEMA ] >> Árvore Vazia Inicializada.\n");
    // Program Cycle
    int option = -1;
    std::system("clear");
    while (option != 0)
    {
        // Program Header
        std::cout << "============================\n";
        std::cout << "=        Árvores C++       =\n";
        std::cout << "============================\n\n";
        // Árvore
        show_tree(tree);
        // Menu
        std::cout << "1. Inserir valor na árvore.\n";
        std::cout << "2. Busca Em-Ordem.\n";
        std::cout << "3. Busca Pré-Ordem.\n";
        std::cout << "4. Busca Pós-Ordem.\n";
        std::cout << "5. Altura de um elemento.\n";
        std::cout << "6. Rotacionar um elemento. [Esquerda]\n";
        std::cout << "7. Rotacionar um elemento. [Direita]\n";
        std::cout << "0. Sair.\n";
        // Status Messages
        std::cout << '\n';
        std::cout << message;
        std::cout << "\n\n";
        message.clear();
        // Input
        std::cout << ">> ";
        std::cin >> option;
        // Options Handling
        switch (option)
        {
        case (1):
            message.append(insertion_opt(tree));
            break;
        case (2):
            in_order_opt(tree);
            break;
        case (3):
            pre_order_opt(tree);
            break;
        case (4):
            post_order_opt(tree);
            break;
        case (5):
            std::system("clear");
            message.append(get_height_opt(tree));
            break;
        case (6):
            std::system("clear");
            message.append(left_rotation_opt(tree));
            break;
        case (7):
            std::system("clear");
            message.append(right_rotation_opt(tree));
            break;
        case (0):
            std::system("clear");
            message.append("[ SISTEMA ] >> Programa encerrado.\n");
            break;
        default:
            std::system("clear");
            message.append("[ SISTEMA ] >> Opção desconhecida.\n");
        }
    }
}