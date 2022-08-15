#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
// #include <arijit.h>
using namespace std;
clock_t start;

class list
{
    vector<int> l;

public:
    void add(int a)
    {
        l.push_back(a);
    }
    int length()
    {
        return l.size();
    }
    bool is_present(int a)
    {
        for (size_t i = 0; i < length(); i++)
        {
            if (a == l[i])
            {
                return true;
            }
        }
        return false;
    }

    list complement()
    {
        list B;
        for (int i = 0; i < 9; i++)
        {
            if (!is_present(i + 1))
            {
                B.add(i + 1);
            }
        }
        return B;
    }
    int get(int i)
    {
        assert(i < length() && i >= 0);
        return l[i];
    }
    void show()
    {
        for (size_t i = 0; i < length(); i++)
        {
            cout << l[i] << " ";
        }
        cout << endl;
    }
};

list marge(list a, list b)
{
    list C = a;

    for (size_t i = 0; i < b.length(); i++)
    {
        if (!C.is_present(b.get(i)))
        {
            C.add(b.get(i));
        }
    }
    return C;
};

class sudoku
{
    int arr[9][9];
    list grr[9][9];
    bool is_valid_;

    friend bool sudoku_solver(sudoku);

public:
    sudoku()
    {
        is_valid_ = true;
    }
    void copy()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (arr[i][j] != 0)
                {
                    grr[i][j].add(arr[i][j]);
                }
            }
        }
    }

    void input()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cin >> arr[i][j];
                assert(arr[i][j] >= 0 || arr[i][j] <= 9);
            }
        }
    }

    void show()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    list row(int a)
    {
        assert(a < 9 && a >= 0);
        list B;
        for (int i = 0; i < 9; i++)
        {
            if (arr[a][i] != 0)
            {
                if (B.is_present(arr[a][i]))
                {
                    is_valid_ = false;
                }
                B.add(arr[a][i]);
            }
        }
        return B;
    }
    list col(int a)
    {
        assert(a < 9 && a >= 0);
        list B;
        for (int i = 0; i < 9; i++)
        {
            if (arr[i][a] != 0)
            {
                if (B.is_present(arr[i][a]))
                {
                    is_valid_ = false;
                }
                B.add(arr[i][a]);
            }
        }
        return B;
    }

    list cell(int a, int b)
    {
        int cr = a / 3;
        int cc = b / 3;
        list C;
        for (int i = cr * 3; i < 3 * cr + 3; i++)
        {
            for (int j = cc * 3; j < 3 * cc + 3; j++)
            {
                if (arr[i][j] != 0)
                {
                    if (C.is_present(arr[i][j]))
                    {
                        is_valid_ = false;
                    }
                    C.add(arr[i][j]);
                }
            }
        }
        return C;
    }
    void solved()
    {
        bool is_done_ = true;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (grr[i][j].length() == 1 && arr[i][j] == 0)
                {
                    is_done_ = false;
                    arr[i][j] = grr[i][j].get(0);
                }
            }
        }
        if (is_done_)
        {
            return;
        }
        update();
    }
    bool is_valid()
    {
        for (size_t i = 0; i < 9; i++)
        {
            row(i);
            col(i);
            cell(3 * (i / 3), 3 * (i % 3));
        }

        return is_valid_;
    }

    void update()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (arr[i][j] == 0)
                {
                    grr[i][j] = marge(marge(row(i), col(j)), cell(i, j)).complement();
                }
            }
        }
        solved();
    }

    bool is_done()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (arr[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

bool sudoku_solver(sudoku S)
{
    S.update();
    if (!S.is_valid())
    {
        return false;
    }
    if (S.is_done())
    {
        S.show();
        clock_t end = clock();
        cout << endl<<(end - start)/CLOCKS_PER_SEC<<endl;
        exit(0);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (S.arr[i][j] == 0)
            {
                for (int k = 0; k < S.grr[i][j].length(); k++)
                {
                    S.arr[i][j] = S.grr[i][j].get(k);
                    sudoku_solver(S);
                }
            }
        }
    }
    return false;
}

int main()
{
    start = clock();
    sudoku S;
    S.input();
    S.copy();
    sudoku_solver(S);
    cout << "impossible" << endl;
    return 0;
}