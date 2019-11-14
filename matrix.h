#ifndef AA_MATRIX_H
#define AA_MATRIX_H
#include "ErrorColor.h"
#include <iostream>
using namespace std;


template<typename T>
class Matrix{
private:
    int rows;
    int columns;
    static int objectCount;
    T **n;

public:
    Matrix(){
        this->rows = 4;
        this->columns = 4;
        n = new T *[this->rows];
        for (int i = 0; i <this->rows ; i++){
            n[i] = new T[this->columns];
            for (int j = 0; j < this->columns; j++){
                n[i][j] = 0;
            }
        }
    }

    Matrix(int rows,int columns)
    {
        objectCount++;
        this->rows = rows;
        this->columns = columns;
        n = new T *[this->rows];
        for (int i = 0; i <this->rows ; i++){
            n[i] = new T[this->columns];
            for (int j = 0; j < this->columns; j++){
                n[i][j] = 0;
            }
        }
    }

   ~Matrix() {
        //cout<<"matrix destructor"<<endl;
        delete [] n;
    }

    void PrintResult(const char* str = "__________________MATRIX:__________________" ){
        cout <<endl;
        cout<<str<<endl;
        for (int x = 0; x<this->rows; x++){
            for (int y = 0; y<this->columns; y++) {
                if (y == 0){
                    cout << " | " << n[x][y] << " ";
                }else{
                    cout << " " << n[x][y] << " ";}

            }
            cout <<" |" <<endl;
        }
    }

   Matrix& operator=(const Matrix &other ){
        if(this->columns<=other.columns && this->rows<=other.rows)
        {
            for(int i=0;i<this->rows;i++){
                for(int j=0;j<this->columns;j++){
                    this->n[i][j]=other.n[i][j];
                    }
                }
            return (*this);
        }else{
            cout <<endl<<RED<<"ERROR: "<< YELLOW<<"Matrix A = Matrix B. B has more dimensions than A"<<WHITE<<endl;
            exit (EXIT_FAILURE);
        }
    }

    Matrix& operator+(const Matrix &other){
        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                this->n[i][j]=other.n[i][j]+this->n[i][j];
            }
        }
        return (*this);
    }

    Matrix& operator*(const Matrix& other) {
        Matrix<T> result = Matrix<T>(rows, other.columns);
        if (this->rows == other.columns && this->columns == other.rows) {
            for (int i = 0; i < this->rows; i++) {
                for (int j = 0; j < this->columns; j++) {
                    for (int k = 0; k < this->columns; k++) {
                        result.n[i][j] += this->n[i][k]*other.n[k][j];
                    }
                }
            }
        }
        return (*this)=result;
    }


    T& operator()(int row, int col) {
        return n[row][col];
    }

};
template<typename T> int Matrix<T>::objectCount = 0;
#endif //AA_MATRIX_H
