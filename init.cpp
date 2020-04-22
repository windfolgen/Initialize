#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <time.h>
#include <map>

using namespace std;

typedef map<string, double> paramap;
paramap maptest;

void op(paramap & mp)
{
	cout << "map as function variables:" << endl;
	double t;
	t = mp["test3"];
	cout << "test3:" << t << endl;
}

void run_tot(string param) {

	//cuba.CubaSet(3, 1); // set ndim and ncomp and result[],error[],prob[]
	//cuba.CubaInt(pp2.tot_integrand); //carray out the integral. results in intcuba.result[]

	string a, b, c;
	a = "ppzj";
	b = "LO";
	c = to_string(1.0);
	ofstream out;
	out.open(a + "_" + "tot_cs" + "_" + b + "_" + c + "_" + "testset" + ".txt");
	if (out) {
		out << "The input parameter file is: " << param << endl;
		out << "total cross section: " << 7200 << "+-" << 10 << endl;
	}
	else { cerr << "file cannot be written!" << endl; }
	out.close();
	out.open("histroy.txt", ios::app);
	if (out) {
		time_t nt = time(NULL);
		struct tm lt_nt;
		localtime_s(&lt_nt, &nt);
		char stTemp[32];
		asctime_s(stTemp, &lt_nt);
		out << stTemp << " " << param << " " << "tot_cross_section: " << 7200 << "+-" << 10 << endl;
	}
	else { cerr << "write in histroy.txt failed!" << endl; }
	out.close();
}

void run_pt(string param) {

	int l = 29 + 1;
	//cuba.CubaSet(2, l); // set ndim and ncomp and result[],error[],prob[]
	//cuba.CubaInt(pp2.pt_integrand);

	string a, b, c;
	a = "ppzj";
	b = "LO";
	c = to_string(1.0);

	ofstream out;
	out.open(a + "_" + "pt_dist" + "_" + b + "_" + c + "_" + "testset" + ".txt", ios::app);


	if (out) {
		time_t nt = time(NULL);
		struct tm lt_nt;
		localtime_s(&lt_nt, &nt);
		char stTemp[32];
		asctime_s(stTemp, &lt_nt);
		out << stTemp << endl;
		out << "The input parameter file is: " << param << endl;
		out << "pt distribution: " << endl;
		double pT = 30;
		for (int i = 0; i < l; i++) {
			out << i + 1 << " " << pT << " " << 0.1 << "+-" << 0.01 << endl;
			pT += 10;
		}
	}
	else { cerr << "file cannot be written!" << endl; }
	out.close();
}

int main(int agrc, char* argv[]) {
	ifstream loadparam;
	string paramname;
	cin >> paramname;
	loadparam.open(paramname+".txt");
	if (!loadparam) { cerr << "file open error!" << endl; return 0; }
	
	string line,a;
	char c[3];
	double b;
	while (getline(loadparam,line)) {
		if(line.find("//")!=string::npos) line.erase(line.find("//")); //delete the comments

		if (line.find_first_not_of(" ") != string::npos)
		{
			if (line.find_first_not_of(" ") != 0)
			line = line.substr(line.find_first_not_of(" "));
		}
		else line = "";// delete the beginning empty space

		//if(!line.empty()) cout << line << endl;
		if (!line.empty()) {
			stringstream s;
			s << line;
			while (s >> a >> c >> b) {
				maptest.insert(paramap::value_type(a,b));
			}
		}
	}
	for (paramap::iterator i = maptest.begin(); i != maptest.end(); i++) cout << i->first << " = " << i->second << endl;
	cout << "test1:" << maptest["test1"] << endl;

	op(maptest);
	loadparam.close();

	run_tot(paramname);
	run_pt(paramname);

	return 0;
}