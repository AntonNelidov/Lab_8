#include <iostream>
#include <matrix.hpp>

using namespace std;
using namespace mt::math;

int main()
{
	// // // // // // // // // // // // // // //

	Matrix2x2 A;
	Matrix3x3 B;
	Matrix2x2 C;

	cout << "Enter the A (2x2) matrix: " << endl;
	cin >> A;

	cout << A << endl;

	cout << endl << "Matrix determinant: " << endl;
	cout << A.Determin() << endl;

	cout << endl << "Transposition Matrix: " << endl;
	cout << A.Transposit() << endl;

	cout << endl << "Inversion Matrix: " << endl;
	cout << A.Inverse() << endl;

	// // // // // // // // // // // // // // //

	cout << "Enter the B (3x3) matrix: " << endl;
	cin >> B;

	cout << B << endl;

	cout << endl << "Matrix determinant: " << endl;
	cout << B.Determin() << endl;

	cout << endl << "Transposition Matrix: " << endl;
	cout << B.Transposit() << endl;

	cout << endl << "Inversion Matrix: " << endl;
	cout << B.Inverse() << endl;

	// // // // // // // // // // // // // // //
	cout << "Tests:" << endl;

	cout << "A*A = ";
	C = A * A;
	cout << C << std::endl;
	
	cout << "A-A = ";
	C = A - A;
	cout << C << std::endl;

	cout << "A+A = ";
	C = A + A;
	cout << C << std::endl;

	// // // // // // // // // // // // // // //

	return 0;
}