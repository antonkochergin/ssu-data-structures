#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

#define RED true
#define BLACK false

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

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
        RBT<int> tree;

        // Вставка элементов для демонстрации
        cout << "Inserting elements: ";
        int values[] = {50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45, 55, 65, 75, 85};
        for (int val : values)
        {
            cout << val << " ";
            tree.insert(val);
        }
        cout << "\n\n";

        // Вывод дерева
        tree.print();

        cout << "\n\nPress Enter to exit...";
        cin.get();

        return 0;
    };