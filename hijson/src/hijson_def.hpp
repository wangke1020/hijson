#ifndef __HIJISON_DEF_H__
#define __HIJISON_DEF_H__
/*
this is a file for defining the macro "HIJSON_DEFINE(...)". the max count of param is 8.
*/
#include "adaptor.hpp"
#include <string>
using namespace std;
using namespace json;
namespace json
{ 
	namespace adaptor
	{

		string trim(string& str)
		{
			size_t first = str.find_first_not_of(' ');
			size_t last = str.find_last_not_of(' ');
			return str.substr(first, (last - first + 1));
		}

		vector<string> &split(const string &s, char delim, vector<string> &elems)
		{
			stringstream ss(s);
			string item;
			while (getline(ss, item, delim))
			{
				elems.push_back(trim(item));
			}
			return elems;
		}

		using StrVec = vector<string>;

#define HIJSON_DEFINE(...)\
	Value toJsonValue() const\
	{\
		vector<string> vec; \
		string args_str = #__VA_ARGS__; \
		split(args_str, ',', vec); \
		return json::adaptor::toJsonValue(vec, __VA_ARGS__); \
	}\
	void fromJsonValue(const Value& value) \
	{\
		vector<string> vec; \
		string args_str = #__VA_ARGS__; \
		split(args_str, ',', vec); \
		json::adaptor::fromJsonValue(value, vec, __VA_ARGS__);\
	}

		//1 items
		template <typename A0>
		Value toJsonValue(const StrVec& vec, const A0& a0)
		{
			Object o;
			o[vec[0]] = Convert(a0);
			return Value(o);
		}
		template <typename A0>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0)
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
		}

		//2 params
		template <typename A0, typename A1>
		Value toJsonValue(const StrVec& vec, const A0& a0, const A1& a1) 
		{
			Object o;
			o[vec[0]] = Convert(a0);
			o[vec[1]] = Convert(a1);
			return Value(o);
		}
		template <typename A0, typename A1>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0, A1& a1) 
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
			As<A1>(o[vec[1]], a1);
		}


		//3 params
		template <typename A0, typename A1, typename A2>
		Value toJsonValue(const StrVec& vec, const A0& a0, const A1& a1, const A2& a2) 
		{
			Object o;
			o[vec[0]] = Convert<A0>(a0);
			o[vec[1]] = Convert<A1>(a1);
			o[vec[2]] = Convert<A2>(a2);
			return Value(o);
		}
		template <typename A0, typename A1, typename A2>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0, A1& a1, A2& a2)
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
			As<A1>(o[vec[1]], a1);
			As<A2>(o[vec[2]], a2);
		}


		//4 params
		template <typename A0, typename A1, typename A2, typename A3>
		Value toJsonValue(const StrVec& vec, const A0& a0, const A1& a1, const A2& a2, const A3& a3) 
		{
			Object o;
			o[vec[0]] = Convert<A0>(a0);
			o[vec[1]] = Convert<A1>(a1);
			o[vec[2]] = Convert<A2>(a2);
			o[vec[3]] = Convert<A3>(a3);
			return Value(o);
		}
		template <typename A0, typename A1, typename A2, typename A3>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0, A1& a1, A2& a2, A3& a3)
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
			As<A1>(o[vec[1]], a1);
			As<A2>(o[vec[2]], a2);
			As<A3>(o[vec[3]], a3);
		}



		//5 params
		template <typename A0, typename A1, typename A2, typename A3, typename A4>
		Value toJsonValue(const StrVec& vec, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		{
			Object o;
			o[vec[0]] = Convert<A0>(a0);
			o[vec[1]] = Convert<A1>(a1);
			o[vec[2]] = Convert<A2>(a2);
			o[vec[3]] = Convert<A3>(a3);
			o[vec[4]] = Convert<A4>(a4);
			return Value(o);
		}
		template <typename A0, typename A1, typename A2, typename A3, typename A4>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0, A1& a1, A2& a2, A3& a3, A4& a4)
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
			As<A1>(o[vec[1]], a1);
			As<A2>(o[vec[2]], a2);
			As<A3>(o[vec[3]], a3);
			As<A4>(o[vec[4]], a4);
		}


		//6 params
		template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
		Value toJsonValue(const StrVec& vec, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
		{
			Object o;
			o[vec[0]] = Convert<A0>(a0);
			o[vec[1]] = Convert<A1>(a1);
			o[vec[2]] = Convert<A2>(a2);
			o[vec[3]] = Convert<A3>(a3);
			o[vec[4]] = Convert<A4>(a4);
			o[vec[5]] = Convert<A5>(a5);
			return Value(o);
		}
		template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5)
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
			As<A1>(o[vec[1]], a1);
			As<A2>(o[vec[2]], a2);
			As<A3>(o[vec[3]], a3);
			As<A4>(o[vec[4]], a4);
			As<A5>(o[vec[5]], a5);
		}


		//7 params
		template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
		Value toJsonValue(const StrVec& vec, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
		{
			Object o;
			o[vec[0]] = Convert<A0>(a0);
			o[vec[1]] = Convert<A1>(a1);
			o[vec[2]] = Convert<A2>(a2);
			o[vec[3]] = Convert<A3>(a3);
			o[vec[4]] = Convert<A4>(a4);
			o[vec[5]] = Convert<A5>(a5);
			o[vec[6]] = Convert<A6>(a6);
			return Value(o);
		}
		template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6)
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
			As<A1>(o[vec[1]], a1);
			As<A2>(o[vec[2]], a2);
			As<A3>(o[vec[3]], a3);
			As<A4>(o[vec[4]], a4);
			As<A5>(o[vec[5]], a5);
			As<A6>(o[vec[6]], a6);
		}

		//8 params
		template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
		Value toJsonValue(const StrVec& vec, const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
		{
			Object o;
			o[vec[0]] = Convert<A0>(a0);
			o[vec[1]] = Convert<A1>(a1);
			o[vec[2]] = Convert<A2>(a2);
			o[vec[3]] = Convert<A3>(a3);
			o[vec[4]] = Convert<A4>(a4);
			o[vec[5]] = Convert<A5>(a5);
			o[vec[6]] = Convert<A6>(a6);
			o[vec[7]] = Convert<A7>(a7);
			return Value(o);
		}
		template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
		void fromJsonValue(const Value& value, const StrVec& vec, A0& a0, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7)
		{
			Object o = value.ToObject();
			As<A0>(o[vec[0]], a0);
			As<A1>(o[vec[1]], a1);
			As<A2>(o[vec[2]], a2);
			As<A3>(o[vec[3]], a3);
			As<A4>(o[vec[4]], a4);
			As<A5>(o[vec[5]], a5);
			As<A6>(o[vec[6]], a6);
			As<A7>(o[vec[7]], a7);
		}
	}
}
#endif