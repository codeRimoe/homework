#include <iostream>
using namespace std;

int fun(int _nCount = 1000)
{
	cout<<"array size = "<<_nCount<<endl;

	cout<<"create new data set"<<endl;
	double* pdata = new double [_nCount];
	
	memset(pdata, 0, _nCount*sizeof(double));
	
	delete []pdata;
	cout<<"destroy data set"<<endl;

	return 0;
}



int main(int argc, char** argv)
{
	if (argc<=1)
	{
		cout<<"plz input params of array size."<<endl;
		return -1;
	}
	
 	cout<<"hello world!"<<endl;	
	//cout<<"nCount = "<<nCount<<endl;
	
	fun(atoi(argv[1]));
	
	cout<<"exit now."<<endl;
	return 1;
}