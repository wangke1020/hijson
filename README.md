# hijson
It is based on [SuperEasyJSON](http://sourceforge.net/projects/supereasyjson/) inspired by [msgpack](https://github.com/msgpack/msgpack).

So far, it just can simply convert  bettween a vector or a map  and Json Value.
```
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
	auto new_v = As<test_vector_t>(vecVaule);

	using test_map_t = unordered_map<string, vector<string>>;
	test_map_t map;
	map["v1"] = v1;
	map["v2"] = v2;
	map["v3"] = v3;
	Value mapValue = Convert(map);
	cout << Serialize(mapValue) << endl;

	auto new_map = As<test_map_t>(mapValue);
```

