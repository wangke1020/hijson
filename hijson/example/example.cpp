#include <iostream>
#include "../src/json.h"
#include "../src/convert.hpp"
using namespace std;
using namespace json;
using namespace json::adapt;
int main()
{
	vector<vector<string>> v;
	auto v1 = vector<string>{"a","b"};
	auto v2 = vector<string>{"d", "d"};
	auto v3 = vector<string>{"e"};
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	cout << Serialize(convert<decltype(v)>()(v)) << endl;

	unordered_map<string, vector<string>> map;
	map["v1"] = v1;
	map["v2"] = v2;
	map["v3"] = v3;

	cout << Serialize(convert<decltype(map)>()(map)) << endl;
	//Value v(1);
	//Object o;
	//o["21"] = v;
	//cout << Serialize(o) << endl;
	getchar();


	
	//JObject obj;
	//obj.add("testKey", "test_value");
	//obj.add("intVal", 1);
	//cout << obj << endl;
	//return true;
}