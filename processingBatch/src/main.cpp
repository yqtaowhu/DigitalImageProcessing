#include<opencv2\opencv.hpp>
//#include "ReadDeal.h"
#include "Transfomation.h"
using namespace std;
using namespace cv;

void PrintHelp() {
	cout << "Usage: imgPro [option] filename(input) filename(output)" << endl;
	cout << "Avaible options are:" << endl; cout << endl;
	cout << "\t-c\tcliping picture" << endl;
	cout << "\t-s\tadd salt noise" << endl;
}
int main(int argc,char *argv[]) {
	if (argc == 1||argc==2||argc==3) {
		PrintHelp();
		return 0;
	}
	if (argc > 4) {
		cout << "too many parametrs" << endl;
	}
	cout << "please input how many example you want to process : " << endl;
	int num; cin >> num;
	Transfomation imgPro(num, argv[2], argv[3]);
	if (argc == 4) {
		switch (tolower(argv[1][1])) {
			case 'c': {
				imgPro.Clip();
				cout << "Complete Process" << endl;
				break;
			}
			case 's': {
				int n;
				cout << "please enter how many noise do you want to add" << endl;
				cin >> n;
				imgPro.Salt(n);
				cout << "Complete Process" << endl;
				break;
			}
			case 'r': {
				cout << "please enter which size do you want to output" << endl;
				cout << "input example: 24 24" << endl;
				int m, n;
				cin>> m >> n;
				imgPro.Resize(m, n);
				cout << "Complete Process" << endl;
				break;
			}
		}
	}
	waitKey();
}

