#include <iostream>	
//99�˷���
void printmt() {
	for (int ii = 1; ii <= 9; ii++)
	{
		for (int jj = 1; jj <= ii; jj++)
			std::cout << ii << "*" << jj << "=" << ii * jj << " ";
		std::cout << "\n";
	}
}

