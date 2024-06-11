#include <iostream>
using namespace std;

void input_mat(int a[9][9]);
bool is_valid(int a[9][9]);
void find_next(int *r, int *c);
bool check_row(int r, int c, int a[9][9]);
bool check_col(int r, int c, int a[9][9]);
bool check_box(int r, int c, int a[9][9]);
bool is_safe(int r, int c, int a[9][9]);
bool assign(int a[9][9], int r, int c);
bool new_assign(int a[9][9], int r, int c);
bool unassigned(int a[9][9]);
void solve(int a[9][9], int r, int c);
int calc_box(int r, int c, int a[9][9]);
void output_mat(int a[9][9]);

int main()
{
    int a[9][9];
    input_mat(a);
    if (!is_valid(a))
    {
        cout << "Invalid sudoku" << endl;
        exit(0);
    }
    solve(a, 0, 0);
    if (unassigned(a))
    {
        cout << "Sudoku cannot be solved" << endl;
        exit(0);
    }

    output_mat(a);
    return 0;
}

void find_next(int *r, int *c)
{
    (*c)++;
    if (*c > 8)
    {
        *c = 0;
        (*r)++;
        if (*r > 8)
        {
            *r = 9;
            *c = 9;
        }
    }
}

bool assign(int a[9][9], int r, int c)
{
    int i;
    for (i = 1; i <= 9; i++)
    {
        a[r][c] = i;
        if (is_safe(r, c, a))
        {
            cout << r << ',' << c << "=" << a[r][c] << endl;
            return true;
        }
    }
    a[r][c] = 0;
    return false;
}

bool new_assign(int a[9][9], int r, int c)
{
    int i;
    for (i = a[r][c] + 1; i <= 9; i++)
    {
        a[r][c] = i;
        if (is_safe(r, c, a))
        {
            // cout << r << ',' << c << "=" << a[r][c] << endl;
            return true;
        }
    }
    a[r][c] = 0;
    return false;
}

void solve(int a[9][9], int r, int c)
{
    if (r < 9 && c < 9)
    {
        if (a[r][c] == 0)
        {
        x:
            if (new_assign(a, r, c))
            {
                int new_r = r, new_c = c;
                find_next(&new_r, &new_c);
                solve(a, new_r, new_c); // 1
                if (unassigned(a))
                {
                    goto x;
                }
            }
            else
            {
                a[r][c] = 0;
                return;
            }
        }

        else
        {
            int new_r = r, new_c = c;
            find_next(&new_r, &new_c);
            solve(a, new_r, new_c); // 2
        }
    }
}

bool check_row(int r, int c, int a[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if (a[r][c] == a[r][i] && i != c)
            return false;
    }
    return true;
}

bool check_col(int r, int c, int a[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if (a[r][c] == a[i][c] && i != r)
            return false;
    }
    return true;
}

int calc_box(int r, int c, int a[9][9])
{
    int box;
    if (r >= 0 && r <= 2 && c >= 0 && c <= 2)
        box = 1;
    if (r >= 0 && r <= 2 && c >= 3 && c <= 5)
        box = 2;
    if (r >= 0 && r <= 2 && c >= 6 && c <= 8)
        box = 3;
    if (r >= 3 && r <= 5 && c >= 0 && c <= 2)
        box = 4;
    if (r >= 3 && r <= 5 && c >= 3 && c <= 5)
        box = 5;
    if (r >= 3 && r <= 5 && c >= 6 && c <= 8)
        box = 6;
    if (r >= 6 && r <= 8 && c >= 0 && c <= 2)
        box = 7;
    if (r >= 6 && r <= 8 && c >= 3 && c <= 5)
        box = 8;
    if (r >= 6 && r <= 8 && c >= 6 && c <= 8)
        box = 9;

    return box;
}

bool check_box(int r, int c, int a[9][9])
{
    int box = calc_box(r, c, a);
    int i, j;
    switch (box)
    {
    case 1:
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 2:
        for (i = 0; i < 3; i++)
            for (j = 3; j < 6; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 3:
        for (i = 0; i < 3; i++)
            for (j = 6; j < 9; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 4:
        for (i = 3; i < 6; i++)
            for (j = 0; j < 3; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 5:
        for (i = 3; i < 6; i++)
            for (j = 3; j < 6; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 6:
        for (i = 3; i < 6; i++)
            for (j = 6; j < 9; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 7:
        for (i = 6; i < 9; i++)
            for (j = 0; j < 3; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 8:
        for (i = 6; i < 9; i++)
            for (j = 3; j < 6; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    case 9:
        for (i = 6; i < 9; i++)
            for (j = 6; j < 9; j++)
            {
                if (a[r][c] == a[i][j] && r != i && c != j)
                    return false;
            }
        break;
    }
    return true;
}

bool is_safe(int r, int c, int a[9][9])
{
    if (check_row(r, c, a) && check_col(r, c, a) && check_box(r, c, a))
        return true;
    return false;
}

void input_mat(int a[9][9])
{
    cout << "Enter the unsolved sudoku matrix (0 for empty places)" << endl;
    int i, j;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            cin >> a[i][j];
}

void output_mat(int a[9][9])
{
    cout << "Resultant sudoku is:" << endl
         << endl;
    int i, j, m = 0, n = 0;
    for (i = 0; i < 9; i++)
    {
        m++;
        n = 0;
        for (j = 0; j < 9; j++)
        {
            n++;
            cout << a[i][j] << " ";
            if (n % 3 == 0)
                cout << "| ";
        }

        cout << endl;
        if (m % 3 == 0)
        {
            for (j = 0; j < 8; j++)
                cout << "-  ";
            cout << endl;
        }
    }
}

bool unassigned(int a[9][9])
{
    int i, j;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            if (a[i][j] == 0)
                return true;
    return false;
}

bool is_valid(int a[9][9])
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        int c[10] = {0};
        for (j = 0; j < 9; j++)
            c[a[i][j]]++;
        for (j = 1; j <= 9; j++)
            if (c[j] > 1)
            {
                cout << "Same row" << endl;
                return false;
            }
    }
    for (i = 0; i < 9; i++)
    {
        int c[10] = {0};
        for (j = 0; j < 9; j++)
            c[a[j][i]]++;
        for (j = 1; j <= 9; j++)
            if (c[j] > 1)
            {
                cout << "Same column" << endl;
                return false;
            }
    }

    int c[10][10] = {0};
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
        {
            c[calc_box(i, j, a)][a[i][j]]++;
        }
    cout << endl;

    for (i = 1; i < 10; i++)
        for (j = 1; j < 10; j++)
            if (c[i][j] > 1)
            {
                cout << "Same box" << endl;
                return false;
            }

    return true;
}