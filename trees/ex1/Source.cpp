/*
Необходимо реализовать:
Двоичное дерево поиска с основными операциями: +
добавление узла +
удаление узла +
поиск узла по ключу +
три варианта обхода. +++
 */

#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;


struct tree {
    int inf;
    tree* left;
    tree* right;
    tree* parent;
};


tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}


tree* insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) {
        tr = n;
        return tr;
    }

    tree* y = tr;
    while (y) {
        if (n->inf > y->inf) {
            if (y->right) {
                y = y->right;
            }
            else {
                n->parent = y;
                y->right = n;
                break;
            }
        }
        else if (n->inf < y->inf) {
            if (y->left) {
                y = y->left;
            }
            else {
                n->parent = y;
                y->left = n;
                break;
            }
        }
        else {
            delete n;
            break;
        }
    }
    return tr;
}


tree* find(tree* tr, int x) {
    if (!tr || tr->inf == x) return tr;
    if (x < tr->inf)
        return find(tr->left, x);
    else
        return find(tr->right, x);
}


tree* findMin(tree* v) {
    if (!v) return NULL;
    while (v->left) {
        v = v->left;
    }
    return v;
}

tree* Min(tree* tr) {
    if (!tr->left) return tr; //нет левого ребенка
    else return Min(tr->left); //идем по левой ветке до конца
}


void deleteNode(tree*& tr, tree* v) {
    if (!v) return;

    tree* p = v->parent;

    //1.удаление листа
    if (!v->left && !v->right) {
        if (!p) tr = NULL;
        else {
            if (p->left == v) p->left = NULL;
            else p->right = NULL;
        }
        delete v;
    }
    //2.удаление узла с одним ребенком
    else if (!v->left || !v->right) {
        tree* child = v->left ? v->left : v->right;
        if (p) {
            if (p->left == v) p->left = child;
            else p->right = child;
            child->parent = p;
        }
        else {
            tr = child;
            child->parent = NULL;
        }
        delete v;
    }
    //3.удаление узла с двумя детьми
    else {
        tree* succ = Min(v->right); //следующий за удаляемым узлом
        v->inf = succ->inf; //присваиваем значение
        deleteNode(tr, succ);
    }
}

// Удаление узла по ключу
void deleteByKey(tree*& tr, int key) {
    tree* nodeToDelete = find(tr, key);
    if (nodeToDelete) {
        deleteNode(tr, nodeToDelete);
        cout << "Элемент " << key << " успешно удален.\n";
    }
    else {
        cout << "Элемент " << key << " не найден в дереве.\n";
    }
}

// Прямой обход
void preorder(tree* root) {
    if (root == NULL) return;
    cout << root->inf << " ";
    preorder(root->left);
    preorder(root->right);
}

// Симметричный обход
void inorder(tree* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->inf << " ";
    inorder(root->right);
}

// Обратный обход
void postorder(tree* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->inf << " ";
}

// Функция для вычисления максимальной высоты дерева
void max_height(tree* x, short& max, short deepness = 1) {
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}

// Функция проверки размера консоли
bool isSizeOfConsoleCorrect(const short& width, const short& height) {
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if (szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Please increase the size of the terminal. Size now: "
            << szOfConsole.X << "x" << szOfConsole.Y
            << ". Minimum required: " << width << "x" << height << ".\n";
        return false;
    }
    return true;
}

// Вспомогательная функция для печати дерева
void print_helper(tree* x, const COORD pos, const short offset) {
    SetConsoleCursorPosition(outp, pos);
    cout << right << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

// Основная функция печати дерева
void printTree(tree* tr) {
    if (tr) {
        short max = 1;
        max_height(tr, max); //вычисляем высоту дерева
        short width = 1 << (max + 1); //вычисляем ширину для печати
        short max_w = 128;
        if (width > max_w) width = max_w;


        //резервируем место для вывода
        for (short i = 0; i < max; ++i) cout << '\n';

        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;

        //выводим дерево
        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
        SetConsoleCursorPosition(outp, endPos);
    }
    else {
        cout << "Дерево пустое." << endl;
    }
}

// Функция для демонстрации всех обходов
void demonstrateTraversals(tree* root, const string& message) {
    cout << "\n" << message << "\n";
    cout << "Прямой обход (preorder):    ";
    preorder(root);
    cout << "\nСимметричный обход (inorder): ";
    inorder(root);
    cout << "\nОбратный обход (postorder):  ";
    postorder(root);
    cout << "\n";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "RUS");

    tree* root = NULL;


    vector<int> numbers = { 40, 20,80,10,15,60,70,63,68,5,8,3,90,85 };

    for (size_t i = 0; i < numbers.size(); ++i) {
        int current_number = numbers[i];
        cout << "\nДобавляем элемент " << current_number << ":\n";
        root = insert(root, current_number);
        printTree(root);
        demonstrateTraversals(root, "Обходы после добавления :");
    }

    cout << "\n\n";
    
    cout << endl;

    cout << "ПОСЛЕДОВАТЕЛЬНОЕ УДАЛЕНИЕ ЭЛЕМЕНТОВ\n";

    vector<int> deleteKeys = { 40, 60  };
    for (int key : deleteKeys) {
        cout << "\nПытаемся удалить элемент " << key << ":\n";
        deleteByKey(root, key);
        printTree(root);
        demonstrateTraversals(root, "Обходы после удаления :");
        cout << "-----------------------------------------------\n";
    }

    cout << "\n\n";
    cout << "ФИНАЛЬНОЕ СОСТОЯНИЕ ДЕРЕВА\n";
    cout << "-----------------------------------------------\n";
    printTree(root);
    demonstrateTraversals(root, "Все обходы финального дерева:");
    return 0;
}