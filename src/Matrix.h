#pragma once
#include <iostream>

/// Matrix, rows*cols
class Matrix {
protected:
	float** self;
	int rows, cols;
	void Init(int rows, int cols);
    /// @deprecated Matrix can now be initialized directly from float[][]
	void Copy(const Matrix& other);
public:
	Matrix& operator=(const Matrix& other);
    /// @param array An array of float to initialize from
	Matrix(int rows, int cols, float** array = nullptr);
	Matrix(const Matrix& other);
	~Matrix();

    int Rows();
    int Cols();
	/// @return Determinator
	float Det();

	/// Sets the main diag to 1
	void Fill1();

    /// @return Matrix with no row and no col
	Matrix Cropped(int row, int col);
    /// @return Transposed matrix
	Matrix Transposed();

    /// Prints matrix
    //// @param roundTo Number of digits after point
	void Print(int roundTo = 2);

	/// Adds toBeAdded'th row to addTo'th row of matrix m, multiplied by k
	static void Manipulate(Matrix& m, int toBeAdded, int addTo, float k);
	/// Adds toBeAdded'th row to addTo'th row of matrix m and pair, multiplied by k
	static void Manipulate(Matrix& m, Matrix& pair, int toBeAdded, int addTo, float k);
	/// Multiplies toChange'th row of m by k
	static void Manipulate(Matrix& m, int toChange, float k);
    /// Multiplies toChange'th row of m and pair by k
	static void Manipulate(Matrix& m, Matrix& pair, int toChange, float k);

	Matrix operator*(const float& a);
	Matrix operator/(const float& a);
	Matrix operator*(const Matrix& other);
	Matrix operator-();
    
    /// @return Row
    float* operator[](const int& index) const;
};