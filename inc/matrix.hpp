#pragma once
#include <iostream>

using namespace std;

namespace mt::math
{
//#define LIGHT

	template<typename T, int N, int M>
	class Matrix
	{
	public:
		// Конструктор
		Matrix()
		{
#ifdef LIGHT
			cout << "Constructor" << endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		// Конструктор копирования
		Matrix(const Matrix<T, N, M>& mat)
		{
#ifdef LIGHT
			cout << "Copying Constructor" << endl;
#endif
			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		int get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		// Присваивание
		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
#ifdef LIGHT
			cout << "Operator =" << endl;
#endif
			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];

			return *this;
		}

		// Оператор сложения
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
			cout << "operator+" << endl;
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			return tmp;
		}

		// Оператор сложения  C += A <=> C = C + A
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+=(const Matrix<T, N, M>& mat)
		{
			cout << "operator+=" << endl;
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
			return tmp;
		}

		// Оператор вычитания
		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
			cout << "operator-" << endl;
			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
			return tmp;
		}

		// Оператор умножения
		template<typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{
			Matrix<T, N, M> tmp;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < mat.getM(); j++) {
					int sum = 0;
					for (int k = 0; k < m_m; k++)
						sum += m_mat[i][k] * mat.get(i, j);
					tmp.set(i, j, sum);
				}

			return tmp;
		}

		// Деструктор
		~Matrix()
		{
#ifdef LIGHT
			cout << "Destructor" << endl;
#endif	
		}

		int Determin()
		{

			if ((m_n == 2) && (m_m == 2))
			{
				return (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]);
			}
			else if ((m_n == 3) && (m_m == 3))
			{
				return (m_mat[0][0] * (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) - (m_mat[0][1] * (m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2])) + (m_mat[0][2] * (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0])));
			}
			else
				cout << endl << "This operation doesn't work for this size!" << endl;
		}

		Matrix Transposit()
		{
			Matrix<T, N, M> tmp;
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
			Matrix<T, N, M> tmp;
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

		// friend - позволяет функции иметь доступ к private полям/методам класса
		template<typename T, int N, int M>
		friend istream& operator>>(istream& os, Matrix<T, N, M>& mat);

		template<typename T, int N, int M>
		friend ostream& operator<<(ostream& os, const Matrix<T, N, M>& mat);


	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

	// Перегрузка оператора ввода
	template<typename T, int N, int M>
	istream& operator>>(istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	// Перегрузка оператора вывода
	template<typename T, int N, int M>
	ostream& operator<<(ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << endl;
		for (int i = 0; i < mat.m_n; i++) {
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << endl;
		}
		return out;
	}

	using Matrix2x2 = Matrix<float, 2, 2>;
	using Matrix3x3 = Matrix<float, 3, 3>;
}