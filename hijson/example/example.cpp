#include <iostream>
#include <sstream>
#include "../src/hijson_def.hpp"
using namespace std;
using namespace json;
using namespace json::adaptor;

void simple_example()
{
	cout << "\n++++++++++++++++   simple example   ++++++++++++++++\n\n";
	//vector example
	using test_vector_t = vector<vector<string>>;
	test_vector_t v;
	auto v1 = vector<string>{ "a","b" };
	auto v2 = vector<string>{ "d", "d" };
	auto v3 = vector<string>{ "e" };
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	Value vecVaule = Convert(v);
	cout << Serialize(vecVaule) << endl;
	test_vector_t new_v;
	As(vecVaule, new_v);
	if (new_v == v)	cout << "new_v is equal to v" << endl;
	else			cout << "new_v is not euqal to v, error" << endl;


	//unordered_map example
	using test_map_t = unordered_map<string, vector<string>>;
	test_map_t map;
	map["v1"] = v1;
	map["v2"] = v2;
	map["v3"] = v3;
	Value mapValue = Convert(map);
	cout << Serialize(mapValue) << endl;
	test_map_t new_map;
	As<test_map_t>(mapValue, new_map);

	if (new_v == v)	cout << "new_map is equal to map" << endl;
	else			cout << "new_map is not euqal to map, error" << endl;
}


class A
{
public:
	A() {};
	string s;
	int i;
	bool b;
	double d;
public:
	explicit A(const string& _s, int _i, bool _b, double _d)
		:s(_s), i(_i), b(_b), d(_d) {};

	string to_string()
	{
		stringstream ss;
		ss << s << "|" << i << "|" << b << "|" << d;
		return ss.str();
	}
};


//custom adaptor function.
namespace json
{
	namespace adaptor
	{
		template<>                                   
		struct convert<A> 
		{
			Value operator()(const A& a) const
			{
				Object obj;
				obj["s"] = a.s;
				obj["i"] = a.i;
				obj["b"] = a.b;
				obj["d"] = a.d;
				return Value(obj);
			}
		};
		template<>
		struct as<A>
		{
			A& operator()(const Value& v, A& a) const
			{
				if (v.GetType() != ObjectVal) throw type_error();
				Object o = v.ToObject();
				a.s = o["s"];
				a.i = o["i"];
				a.b = o["b"];
				a.d = o["d"];
				return a;
			}
		};
	}
}

void custom_example()
{
	
	cout << "\n++++++++++++++++   custom exmaple   ++++++++++++++++\n\n";
	A a("a", 1, true, 3.14);
	cout << a.to_string() << endl;
	Value value = Convert(a);
	cout << Serialize(value) << endl;

	A new_a;
	As(value, new_a);
	cout << new_a.to_string() << endl;
}




class B
{
public:
	B() {};
	string s;
	int i;
	bool b;
	double d;
public:
	explicit B(const string& _s, int _i, bool _b, double _d)
		:s(_s), i(_i), b(_b), d(_d) {};

	string to_string()
	{
		stringstream ss;
		ss << s << "|" << i << "|" << b << "|" << d;
		return ss.str();
	}
	HIJSON_DEFINE(s, i, b, d)
};
void macro_example()
{
	cout << "\n++++++++++++++++   macro exmaple   ++++++++++++++++\n\n";
	B b("a", 1, true, 3.14);
	cout << b.to_string() << endl;
	Value value = Convert(b);
	cout << Serialize(value) << endl;

	B new_b;
	As(value, new_b);
	cout << new_b.to_string() << endl;

}
int main()
{
	simple_example();
	custom_example();
	macro_example();

#ifdef _MSC_VER
	getchar();
#endif
}