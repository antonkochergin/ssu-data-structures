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

#define RED true
#define BLACK false

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;





struct tree
{
    int inf;
    tree *left;
    tree *right;
};

tree *node(int x)
{
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    return n;
}

//создание нового узла
tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}

//вставка элемента в дерево 
void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) tr = n; //если дерево пустое - корень
    else {
        tree* y = tr;
        while (y) { //ищем куда вставлять
            if (n->inf > y->inf) { //правая ветка
                if (y->right) y = y->right;
                else {
                    n->parent = y; //узел становится правым ребенком
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { //левая ветка
                if (y->left) y = y->left;
                else {
                    n->parent = y; //узел становится левым ребенком
                    y->left = n;
                    break;
                }
            }
            else { //если элемент уже существует
                delete n;
                break;
            }
        }
    }
}

//поиск элемента в дереве бинарного поиска
tree* find(tree* tr, int x) {
    if (!tr || tr->inf == x) return tr; //нашли или дошли до конца ветки
    if (x < tr->inf)
        return find(tr->left, x); //ищем по левой ветке
    else
        return find(tr->right, x); //ищем по правой ветке
}

//удаление узла из дерева бинарного поиска
void Delete(tree*& tr, tree* v) {
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
        Delete(tr, succ);
    }
}

//прямой обход 
template <typename T>
void preOrder(node<T>* root) {
    if (root == nullptr) return;
    
    cout << root->key << " ";  
    preOrder(root->left);      
    preOrder(root->right);     
}

//симметричный обход
template <typename T>
void inOrder(node<T>* root) {
    if (root == nullptr) return;
    
    inOrder(root->left);        
    cout << root->key << " ";
    inOrder(root->right);       
}

//обратный обход
template <typename T>
void postOrder(node<T>* root) {
    if (root == nullptr) return;
    
    postOrder(root->left);       
    postOrder(root->right);      
    cout << root->key << " ";
}




template <typename T>
struct node
{
    T key;
    bool color;
    node<T> *parent, *left, *right;
};

template <typename T>
class RBT
{
private:
    node<T> *root;

    void max_height(node<T> *x, short &max, short deepness = 1)
    {
        if (deepness > max)
            max = deepness;
        if (x->left)
            max_height(x->left, max, deepness + 1);
        if (x->right)
            max_height(x->right, max, deepness + 1);
    }

    void print_helper(node<T> *x, const COORD pos, const short offset)
    {
        SetConsoleTextAttribute(output, x->color == RED ? 12 : 8);
        SetConsoleCursorPosition(output, pos);
        cout << setw(offset + 1) << x->key;
        if (x->left)
            print_helper(x->left, {pos.X, short(pos.Y + 1)}, offset >> 1);
        if (x->right)
            print_helper(x->right, {short(pos.X + offset), short(pos.Y + 1)}, offset >> 1);
    }

    bool isSizeOfConsoleCorrect(const short &width, const short &height)
    {
        GetConsoleScreenBufferInfo(output, &csbInfo);
        COORD szOfConsole = csbInfo.dwSize;
        if (szOfConsole.X < width && szOfConsole.Y < height)
            cout << "Please increase the height and width of the terminal. ";
        else if (szOfConsole.X < width)
            cout << "Please increase the width of the terminal. ";
        else if (szOfConsole.Y < height)
            cout << "Please increase the height of the terminal. ";
        if (szOfConsole.X < width || szOfConsole.Y < height)
        {
            cout << "Size of your terminal now: " << szOfConsole.X << ' ' << szOfConsole.Y
                 << ". Minimum required: " << width << ' ' << height << ".\n";
            return false;
        }
        return true;
    }
public:
    void print(node<T> *head = nullptr)
    {
        if (!head)
            head = root;
        if (head)
        {
            short max = 1;
            max_height(head, max);
            short width = 1 << max + 1;
            short max_w = 128;
            if (width > max_w)
                width = max_w;
            while (!isSizeOfConsoleCorrect(width, max))
                system("pause");
            for (short i = 0; i < max; ++i)
                cout << '\n';
            GetConsoleScreenBufferInfo(output, &csbInfo);
            COORD endPos = csbInfo.dwCursorPosition;
            print_helper(head, {0, short(endPos.Y - max)}, width >> 1);
            SetConsoleCursorPosition(output, endPos);
            SetConsoleTextAttribute(output, 7);
        }
    }

int main()
{
    setlocale(LC_ALL, "RUS");
    tree *root = NULL;

    // Элементы заданы в векторе
    vector<int> numbers = {5, 7, 2, 1, 3, 4, 8, 0, 9, 6};

    // Вставляем элементы из вектора в дерево
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        int current_number = numbers[i];
        root = insert(root, current_number);
    }

    cout << "Дерево бинарного поиска:\n";
    print(root);
    cout << "\n\n";

    cout << "Прямой обход (preorder): ";
    preorder(root);
    cout << "\n";

    return 0;
}