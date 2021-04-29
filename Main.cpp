#include "MyInterface.hpp"
//#include "MyInterface.cpp"
#include <typeinfo>

void Init(Graphic::Line &points, float start, float finish)
{
	float dx = (finish - start) / (ARRAY_SIZE - 1);
	for (; start < finish; start += dx)
		points.AddPair(start, sin(start));
}


int main(int argc, char** argv)
{	
	try
	{
		Graphic g1;
		g1.Init(argc, argv);

		g1.AddLine();
		g1.at(0).AddPair(1000, 0.0341064);
		g1.at(0).AddPair(2000, 0.120386);
		g1.at(0).AddPair(3000, 0.314297);
		g1.at(0).AddPair(4000, 0.51938);
		g1.at(0).AddPair(5000, 0.87913);
		g1.at(0).AddPair(6000, 1.15108);
		g1.at(0).AddPair(7000, 1.61167);
		g1.at(0).AddPair(8000, 1.97069);
		g1.at(0).AddPair(9000, 2.57895);
		g1.at(0).AddPair(10000, 3.38455);
		g1.at(0).setColor(1.0, 0.0, 0.0);
		
		g1.AddLine();
		g1.at(1).AddPair(1000, 0.000517);
		g1.at(1).AddPair(2000, 0.0009874);
		g1.at(1).AddPair(3000, 0.0015735);
		g1.at(1).AddPair(4000, 0.0022775);
		g1.at(1).AddPair(5000, 0.0028312);
		g1.at(1).AddPair(6000, 0.0034145);
		g1.at(1).AddPair(7000, 0.0045125);
		g1.at(1).AddPair(8000, 0.0053821);
		g1.at(1).AddPair(9000, 0.0053508);
		g1.at(1).AddPair(10000, 0.0062767);			
		g1.at(1).setColor(0.0, 1.0, 0.0);
		//Init(g1.at(0), 0, 100);
		//Init(g1.at(1), 10, 110);
		g1.Show();
		return 0;
	}

	
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}
	
//1000	0.0341064	0.000517	0.0316723	0.0018303	0.0064737
//2000	0.120386	0.0009874	0.149566	0.0074347	0.0199115
//3000	0.314297	0.0015735	0.251128	0.0152149	0.0394173
//4000	0.51938	0.0022775	0.537759	0.0278328	0.0903038
//5000	0.87913	0.0028312	0.793699	0.0418264	0.102405
//6000	1.15108	0.0034145	1.12645	0.0933315	0.117722
//7000	1.61167	0.0045125	1.45267	0.13115	0.136876
//8000	1.97069	0.0053821	1.91234	0.147451	0.151384
//9000	2.57895	0.0053508	2.46386	0.130519	0.194446
//10000	3.38455	0.0062767	2.93144	0.187727	0.301849



