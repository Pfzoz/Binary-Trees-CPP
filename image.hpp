#ifndef IMAGE
#define IMAGE

#include <string>
#include <vector>
#include <iostream>

class Image
{
private:
    

public:
std::vector<std::vector<char>> mat;
    Image(int m, int n, char fill = ' ')
    {
        std::vector<char> row(n, fill);
        this->mat = std::vector<std::vector<char>>(m, row);
    }

    int rows() { return this->mat.size(); };
    int cols() { return this->mat[0].size(); };

    void set(int row, int col, char value) { this->mat[row][col] = value; };
    void set_row(int row, std::vector<char> line) { this->mat[row] = line; };
    char get(int row, int col) { return this->mat[row][col]; };

    void expand_right(int n, char fill = ' ');
    void expand_left(int n, char fill = ' ');
    void expand_up(int n, char fill = ' ');
    void expand_down(int n, char fill = ' ');

    void shrink_right(int n);
    void shrink_left(int n);
    void shrink_up(int n);
    void shrink_down(int n);

    void trim(char trimmer = ' ')
    {
        for (int i = 0; i < this->mat.size(); i++)
        {
            int delete_row = 1;
            for (int j = 0; j < this->mat[0].size(); j++)
            {
                if (this->mat[i][j] != trimmer) delete_row = 0;
            }
            if (delete_row) 
            {
                this->mat.erase(this->mat.begin()+i);
                i--;
            }
        }
        for (int i = 0; i < this->mat[0].size(); i++)
        {
            int delete_column = 1;
            for (int j = 0; j < this->mat.size(); j++)
            {
                if (this->mat[j][i] != trimmer) delete_column = 0;
            }
            if (delete_column)
            {
                for (int j = 0; j < this->mat.size(); j++) this->mat[j].erase(this->mat[j].begin()+i);
                i--;
            }
        }
    }

    void show(int spacing = 0)
    {
        for (std::vector<char> row : this->mat)
        {
            for (char point : row)
            {
                std::cout << point;
                for (int i = 0; i < spacing; i++)
                    std::cout << ' ';
            }
            std::cout << '\n';
        }
    }
};

void Image::shrink_up(int n)
{
    std::cout << "Shrinking up " << n << " times\n";
    for (int i = 0; i < n; i++) this->mat.erase(this->mat.begin());
}

void Image::shrink_down(int n)
{
    std::cout << "Shrinking down " << n << " times\n";
    for (int i = 0; i < n; i++) this->mat.pop_back();
}

void Image::shrink_right(int n)
{
    std::cout << "Shrinking right " << n << " times\n";
    for (int i = 0; i < this->mat.size(); i++)
    {
        for (int j = 0; j < n; j++) this->mat[0].pop_back();
    }
}

void Image::shrink_left(int n)
{
    std::cout << "Shrinking left " << n << " times\n";
    for (int i = 0; i < this->mat.size(); i++)
    {
        for (int j = 0; j < n; j++) this->mat[0].erase(this->mat[0].begin());
    }
}

void Image::expand_right(int n, char fill)
{
    for (int i = 0; i < this->mat.size(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->mat[i].push_back(fill);
        }
    }
}

void Image::expand_left(int n, char fill)
{
    for (int i = 0; i < this->mat.size(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->mat[i].insert(this->mat[i].begin(), fill);
        }
    }
}

void Image::expand_down(int n, char fill)
{
    std::vector<char> row(this->cols(), fill);
    for (int i = 0; i < n; i++)
    {
        this->mat.push_back(row);
    }
}

void Image::expand_up(int n, char fill)
{
    std::vector<char> row(n, fill);
    for (int i = 0; i < n; i++)
    {
        this->mat.insert(this->mat.begin(), row);
    }
}

#endif