#ifndef __ADAPTOR_HPP__
#define __ADAPTOR_HPP__
#include "json.h"
#include <vector>
#include <unordered_map>
using namespace std;

namespace json
{
	namespace adaptor
	{
		class type_error : public std::exception { };

		template<typename T>
		struct convert
		{
			Value operator()(const T& t)
			{
				return t.toJsonValue();
			}
		};

#define ADD_SPECIALIZATION_CONVERT_TYPE(T)       \
			template<>                                   \
			struct convert<T>{                           \
				Value operator()(const T& t) const{             \
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
			Value  operator()(const vector<T, Alloc>& v) const
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
			Value operator()(const unordered_map<string, V, Hash, Pred, Alloc>& map) const {
				Object o;
				for (auto iter : map)
				{
					o[iter.first] = convert<V>()(iter.second);
				}
				return Value(o);
			}
		};

		template<typename T>
		Value Convert(const T& t)
		{
			return convert<T>()(t);
		}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* 
		   struct as. convert a Json value to some struct.
		*/

		template<typename T>
		struct as
		{
			T& operator()(const Value& value, T& t)
			{
				t.fromJsonValue(value);
				return t;
			}
		};

#define ADD_SPECIALIZATION_AS_TYPE(T) \
		template<>                            \
		struct as<T>                          \
		{                                     \
			T& operator()(const Value& value, T& t)         \
			{                                 \
				t =  (T)value;              \
				return t;                    \
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
			vector<T, Alloc>& operator()(const Value& value, vector<T, Alloc>& vec) const
			{
				if (value.GetType() != ValueType::ArrayVal) throw type_error();
				Array arr = value.ToArray();
				for (auto i : arr)
				{
					T t;
					as<T>()(i, t);
					vec.push_back(t);
				}
				return vec;
			}
		};

		template <typename V, typename Hash, typename Pred, typename Alloc>
		struct as<unordered_map<string, V, Hash, Pred, Alloc>>
		{
			using map_t = unordered_map<string, V, Hash, Pred, Alloc>;
			map_t & operator()(const Value& value, map_t& map) const
			{
				if (value.GetType() != ValueType::ObjectVal) throw type_error();
				Object o = value.ToObject();
				for (auto iter : o)
				{
					V v;
					as<V>()(iter.second, v);
					map[iter.first] = v;
				}
				return map;
			}
		};

		template<typename T>
		T& As(const Value& v, T& t)
		{
			return as<T>()(v, t);
		}
	}
}
#endif
