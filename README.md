# hijson
It is based on [SuperEasyJSON](http://sourceforge.net/projects/supereasyjson/) inspired by [msgpack](https://github.com/msgpack/msgpack).

So far, it just can simply convert a vecotor or a map to Json Value. 
```
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
```
*custom adaptors* will be come soon.
