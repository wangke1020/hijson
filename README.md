# hijson
It is based on [SuperEasyJSON](http://sourceforge.net/projects/supereasyjson/) inspired by [msgpack](https://github.com/msgpack/msgpack).

It  can simply convert a vector or a map to Json Value. 
```cpp
	using test_map_t = unordered_map<string, vector<string>>;
	test_map_t map;
	map["v1"] = v1;
	map["v2"] = v2;
	map["v3"] = v3;
	Value mapValue = Convert(map);
	cout << Serialize(mapValue) << endl;
	test_map_t new_map;
	As<test_map_t>(mapValue, new_map);
```

```cpp
	//adator macro
	class B
	{
	public:
		B() {};
		string s;
		int i;
		bool b;
		double d;
	public:
		HIJSON_DEFINE(s, i, b, d)
	};
```