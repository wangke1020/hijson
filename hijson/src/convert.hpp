#pragma once
#include "json.h"
#include <vector>
#include <unordered_map>
using namespace std;

namespace json
{
	namespace adapt
	{
		class type_error : public std::exception { };

		template<typename T>
		struct convert
		{
			Value operator()(T t) const
			{
				throw type_error();
			}
		};
		
		#define ADD_SPECIALIZATION_CONVERT_TYPE(T)       \
			template<>                                   \
			struct convert<T>{                           \
				Value operator()(T t) const{             \
					return Value(t);                     \
				}                                        \
			};

		ADD_SPECIALIZATION_CONVERT_TYPE(int);
		ADD_SPECIALIZATION_CONVERT_TYPE(float);
		ADD_SPECIALIZATION_CONVERT_TYPE(double);
		ADD_SPECIALIZATION_CONVERT_TYPE(string);
		ADD_SPECIALIZATION_CONVERT_TYPE(bool);


		// convert a convert vector to Json Value
		template <typename T, typename Alloc>
		struct convert<vector<T, Alloc> >
		{
			Value  operator()(vector<T, Alloc>& v) const
			{
				Array arr;
				for (auto it : v)
				{
					arr.push_back(convert<T>()(it));
				}
				return Value(arr);
			}
		};

		// convert a convert unordered_map<string, ...> to Json Value
		template <typename V, typename Hash, typename Pred, typename Alloc>
		struct convert<unordered_map<string, V, Hash, Pred, Alloc> > {
			Value operator()(unordered_map<string, V, Hash, Pred, Alloc>& map) const {
				Object o;
				for (auto iter : map)
				{
					o[iter.first] = convert<V>()(iter.second);
				}
				return Value(o);
			}
		};


		/* 
		   struct as. convert a Json value to some struct.
		*/

		template<typename T>
		struct as
		{
			T operator()(Value value) const
			{
				throw type_error();
			}
		};

#define ADD_SPECIALIZATION_AS_TYPE(T) \
		template<>                            \
		struct as<T>                          \
		{                                     \
			T operator()(Value value)         \
			{                                 \
				return (T)value;              \
			}                                 \
		}; 

		ADD_SPECIALIZATION_AS_TYPE(int);
		ADD_SPECIALIZATION_AS_TYPE(float);
		ADD_SPECIALIZATION_AS_TYPE(double);
		ADD_SPECIALIZATION_AS_TYPE(string);
		ADD_SPECIALIZATION_AS_TYPE(bool);
		

		template <typename T, typename Alloc>
		struct as<vector<T, Alloc> >
		{
			vector<T, Alloc> operator()(Value value) const
			{
				if (value.GetType() != ValueType::ArrayVal) throw type_error();
				Array arr = value.ToArray();
				vector<T, Alloc> v;
				for (auto i : arr)
				{
					arr.push_back(as<T>()(i));
				}
			}
		};

		template <typename V, typename Hash, typename Pred, typename Alloc>
		struct as<unordered_map<string, V, Hash, Pred, Alloc>>
		{
			unordered_map<string, V, Hash, Pred, Alloc> operator()(Value value) const 
			{
				if (value.GetType() != ValueType::ObjectVal) throw type_error();
				unordered_map < string, V, Hash, Pred, Alloc >> map;
				Object o = value.ToObject();
				for (auto iter : o)
				{
					map[iter.first] = as<V>()(iter.second)£»
				}
				return map;
			}
		};
	}
}

