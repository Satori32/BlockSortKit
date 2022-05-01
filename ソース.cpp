#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>

typedef std::uint8_t Word;
typedef std::vector<Word> DType;
typedef std::vector<DType> DTypes;
typedef std::tuple<DType, std::size_t> Data;

Data BlockSort_Enc(const DType& In) {
	std::vector<std::tuple<Word, std::size_t>> D;

	for (std::size_t i = 0; i < In.size(); i++) {
		D.push_back({ In[i],i });
	}

	auto DD = D;
	auto A = D;
	auto B = D;
	auto& X = D;

	std::stable_sort(D.begin(), D.end(), [&](auto& AA, auto& BB) {
		std::rotate(A.begin(), A.begin() + (std::get<1>(AA) % A.size()), A.end());
		std::rotate(B.begin(), B.begin() + (std::get<1>(BB) % B.size()), B.end());

		for (std::size_t i = 0; i < X.size(); i++) {
			if (std::get<0>(A[i]) != std::get<0>(B[i])) {
				auto AR = std::get<0>(A[i]);
				auto BR = std::get<0>(B[i]);
				A = B = DD;
				return std::isgreater(AR, BR);
			}
		}
		A = B = DD;
		return false;
		});

	DType R;
	std::size_t L=0;

	for (std::size_t i = 0; i < D.size(); i++) {
		R.push_back(std::get<0>(D[i]));
		if (std::get<1>(D[i]) == 0) { L = i+1; }
	}

	std::rotate(R.begin(), R.end() - (L % R.size()), R.end());

	return { R,L };

}

DType MakeCacao() {
	DType R = { 'c','a','c','a','o'};

	return R;
}

DType MakeVecor(std::size_t L, unsigned int S = 0) {
	DType R;
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> ui(0, 255);
	for (std::size_t i = 0; i < L; i++) {
		R.push_back(ui(mt));
	}

	return R;
}
DType MakeVecor2(std::size_t L, unsigned int S = 0) {
	DType R;
	std::mt19937 mt(S);
	std::uniform_int_distribution<int> ui('A', 'z');
	for (std::size_t i = 0; i < L; i++) {
		R.push_back(ui(mt));
	}

	return R;
}

bool Show(const DType& In) {
	for (auto& o : In) {
		std::cout << o << ',';
	}

	std::cout << std::endl;

	return true;
}
int main() {
	//auto D = MakeCacao();

	//auto D = MakeVecor2(16);
	auto D = MakeVecor2(128);
	Show(D);

	auto A = BlockSort_Enc(D);

	Show(std::get<0>(A));

	return 0;
	


}