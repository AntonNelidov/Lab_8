#include <iostream>

using namespace std;

class Matrix
{
	// Абстракция
	// Инкапсуляция
	// Использование вне класса
public:
	// Конструктор
	Matrix(int n, int m)
	{
		cout << "Constructor" << endl;
		m_n = n;
		m_m = m;
		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];
	}

	// Конструктор копирования
	Matrix(const Matrix& mat)
	{
		cout << "Copy constructor" << endl;

		m_n = mat.m_n;
		m_m = mat.m_m;

		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];
	}

	// Присваивание
	Matrix& operator=(const Matrix& mat)
	{
		cout << "Operator =" << endl;

		m_n = mat.m_n;
		m_m = mat.m_m;

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];

		return *this;
	}

	// Оператор сложения
	Matrix operator+(const Matrix& mat)
	{
		cout << "operator+" << endl;
		Matrix tmp(2, 3);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	// Оператор сложения  C += A <=> C = C + A
	Matrix operator+=(const Matrix& mat)
	{
		cout << "operator+=" << endl;
		Matrix tmp(2, 3);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	// Оператор вычитания
	Matrix operator-(const Matrix& mat)
	{
		cout << "operator-" << endl;
		Matrix tmp(2, 3);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		return tmp;
	}

	// Оператор умножения
	Matrix operator*(const Matrix& mat)
	{
		cout << "operator*" << endl;
		Matrix tmp(m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = 0;
				for (int k = 0; k < m_m; k++)
				{
					tmp.m_mat[i][j] += m_mat[i][k] * mat.m_mat[k][j];
				}
			}
		}
		return tmp;
	}
	
	// Деструктор
	~Matrix()
	{
		cout << "Destructor" << endl;
		for (int i = 0; i < m_n; i++)
			delete[] m_mat[i];
		delete m_mat;
	}

	// friend - позволяет функции иметь доступ к private полям/методам класса
	friend istream& operator>>(istream& os, Matrix& mat);
	friend ostream& operator<<(ostream& os, const Matrix& mat);

	int Determin()
	{
		cout << endl << "Matrix determinant: " << endl;

		if ((m_n == 2) && (m_m == 2))
		{
			return (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]);
		}
		else if ((m_n == 3) && (m_m == 3))
		{
			return (m_mat[0][0] * (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) - (m_mat[0][1] * (m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2])) + (m_mat[0][2] * (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0])));
		}
		else
			cout <<endl<< "This operation doesn't work for this size!"<<endl;
	}

	Matrix Transposit()
	{
		cout << endl << "Matrix transposition: " << endl;

		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = m_mat[j][i];
			}
		}
		return tmp;
	}

	Matrix Inverse()
	{
		cout << endl << "Inverse matrix: " << endl;

		Matrix tmp(m_n, m_m);
		for (int i = 0; i < m_n; i++)
		{
			for (int j = 0; j < m_m; j++)
			{
				tmp.m_mat[i][j] = 0;
			}
		}
		if ((m_n == 2 && m_m == 2) || (m_n == 3 && m_m == 3))
		{
			int det = Determin(); // проверка на обратимость матрицы
			if (det == 0) {
				cout << endl << "Inverse matrix doesn't exist because of Det = 0" << endl;
				return tmp;
			}

			if (m_n == 2) {
				tmp.m_mat[0][0] = m_mat[1][1] / det;
				tmp.m_mat[0][1] = -m_mat[0][1] / det;
				tmp.m_mat[1][0] = -m_mat[1][0] / det;
				tmp.m_mat[1][1] = m_mat[0][0] / det;
				return tmp;
			}
			if (m_n == 3) {
				tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det;
				tmp.m_mat[0][1] = -(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / det;
				tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det;
				tmp.m_mat[1][0] = -(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / det;
				tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det;
				tmp.m_mat[1][2] = -(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / det;
				tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det;
				tmp.m_mat[2][1] = -(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / det;
				tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det;
				return tmp;
			}
		}
		else
			cout << endl << "This operation doesn't work for this size!" << endl;
	}

	// Использование внутри класса
private:
	int m_n, m_m;		// Поле
	int n;
	int** m_mat; // Matrix
};


int main()
{
	const int n_2 = 2; const int m_2 = 2;
	const int n_3 = 3; const int m_3 = 3;

	// // // // // // // // // // // // // // //

	Matrix A(n_2, m_2);

	cin >> A;

	cout << A << endl;

	cout << A.Determin() << endl;

	cout << A.Transposit() << endl;

	cout << A.Inverse() << endl;

	// // // // // // // // // // // // // // //

	Matrix B(n_3, m_3);

	cin >> B;

	cout << B << endl;

	cout << B.Determin() << endl;

	cout << B.Transposit() << endl;

	cout << B.Inverse() << endl;

	// // // // // // // // // // // // // // //

	return 0;
}