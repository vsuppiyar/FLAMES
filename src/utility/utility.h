#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <algorithm>

#include "../classes/GeneAnnoParser/GFFRecord.h"
#include "../classes/Pos.h"


namespace ranges
{
    template<typename Range, typename Function>
    Function for_each(Range& range, Function f)
    {
        return std::for_each(std::begin(range), std::end(range), f);
    }

	template<typename Range, typename Function>
	Function transform(Range& range, Range& out, Function f) {
		return std::transform(std::begin(range), std::end(range), std::begin(out), f);
	}

	template<typename T, typename U>
	std::vector<U> map(const std::vector<T> &range, std::function<U(const T &)> f) {
		std::vector<U> out;
		for (const T &t : range) {
			out.push_back(f(t));
		}
		return out;
	}

	template <typename T>
	int sumMap(const std::vector<T> &vec, std::function<int(T)> f) {
		int sum = 0;
		for (auto it : vec) {
			sum += f(it);
		}
		return sum;
	}

	// template <typename T, typename U>
	// U reduce(const std::vector<T> &range, std::function<U(const T &, const U &) f) {
	// 	U res = range[0];
	// 	for (int i = 1; i < range.size(); i++) {
	// 		res = f(range[i], res);
	// 	}
	// 	return res;
	// }
	// template <typename T, typename U>
	// U reduce(const std::vector<T> &range, U init, std::function<U(const T &, const U &) f) {
	// 	U res = init;
	// 	for (int i = 0; i < range.size(); i++) {
	// 		res = f(range[i], res);
	// 	}
	// 	return res;
	// }
}


template <typename T>
void printMap(std::unordered_map<std::string, T> &, std::function<std::string (T)>);

std::string PosToStr(Pos);

std::string VecToStr(std::vector<std::string>);

/*
 * At vector position, determine the most value across all vectors
 * @return a vector of the most common elements at each position
*/
template <typename T>
static inline std::vector<T> 
mostCommonEachCell(const std::vector<std::vector<T>> &values, int maxSize) {
	std::vector<T> newValue;
	for (int i = 0; i < maxSize; i++) {
		std::unordered_map<T, int> thisPosValueCounts;
		for (int j = 0; j < values.size(); j++) {
			thisPosValueCounts[values[j][i]]++;
		}
		// get the the most common value of junction
		// at each i position 
		T bestValue;
		int maxCount = 0;
		for (auto &[value, count] : thisPosValueCounts) {
			if (count > maxCount) {
				bestValue = value;
				maxCount = count;
			}
		}
		newValue.push_back(bestValue);
	}

	return newValue;
}

template <typename T>
static inline T mostCommon(const std::vector<T> &values) {
	std::unordered_map<T, int> counts;
	for (auto it : values) {
		counts[it]++;
	}

	T max = (*std::max_element(
				counts.cbegin(), counts.cend(),
				[](const std::pair<T, int> &a, const std::pair<T, int> &b) { 
					return a.second < b.second; 
				}
	)).first;

	return max;
}

/*
 * Taking a vector of values (which contains duplicates)
 * count the number of occurances for each unique value
 * and sort from most number to least
*/
template <typename T>
std::vector<std::pair<T, int>> 
static inline sortNumberOccurances(const std::vector<T> &values) {
	std::unordered_map<T, int> counts;
	for (const auto &i : values) {
		counts[i]++;
	}

	return sortNumberOccurances(counts);
}

template <typename T>
std::vector<std::pair<T, int>>
static inline sortNumberOccurances(const std::unordered_map<T, int> &counts) {
	std::vector<std::pair<T, int>> out;
	for (const auto &i : counts) {
		out.push_back(i);
	}

	std::sort(out.begin(), out.end(),
		[](const auto &p1, const auto p2) {
			return (p1.second > p2.second);
		}
	);

	return out;	
}

