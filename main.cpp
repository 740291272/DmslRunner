#include "Dmsl/Dmsl.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

static Dmsl::DmslVirtualMachine* pVM;
static std::stack<std::shared_ptr<const std::vector<double>>> varying;

static void printHelloWorld(double*, void*)
{
	cout << "HelloWorld" << endl;
}

static void call(double* args, void*)
{
	Dmsl::DmslUnit unit(*pVM, args[0], varying.top());
	varying.push(unit.GetVaryingOut());
	unit.Call();
	varying.pop();
}

static void print(double* args, void*)
{
	cout << args[0] << endl;
}

int main(int argc,char** argv)
{
	if (argc != 2)
	{
		cout << "DmslRunner dmslSrc" << endl;
	}
	else
	{
		std::ifstream in(argv[1]);
		if (in.fail())
		{
			cout << "Can not find file " << argv[1] << endl;
			return -1;
		}
		in.seekg(0, std::ios::end);
		auto size = in.tellg();
		in.seekg(0, std::ios::beg);
		
		std::vector<char> src;
		src.resize(size);
		in.read(src.data(), size);
		src.emplace_back('\0');
		std::string srcstr = src.data();

		srcstr = "cmethod printHelloWorld,0\n" + srcstr;
		srcstr = "cmethod call,1\n" + srcstr;
		srcstr = "cmethod print,1\n" + srcstr;

		Dmsl::DmslVirtualMachine vm{ srcstr,cout };
		pVM = &vm;
		vm.LinkCMet("printHelloWorld",&printHelloWorld);
		vm.LinkCMet("call", &call);
		vm.LinkCMet("print", &print);
		vm.Ready();

		double defaultUnit = 0;

		varying.push(nullptr);
		call(&defaultUnit, nullptr);
	}
}
