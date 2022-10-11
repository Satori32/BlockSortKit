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

Data BlockSort_EncII(DType In) {//consume memory
	std::vector<Data> D;
	for (std::size_t i = 0; i < In.size(); i++) {
		D.push_back({ In,i });
		std::rotate(In.begin(), In.begin() + 1, In.end());
	}

	std::stable_sort(D.begin(), D.end(), [&](auto& A, auto& B) { return std::get<0>(A) < std::get<0>(B); });

	std::size_t X = 0;
	DType R;
	for (std::size_t i = 0; i < In.size(); i++) {
		if (std::get<1>(D[i]) == 0) {
			X = i;
			break;
		}
	}
	for (std::size_t i = 0; i < In.size(); i++) {
		//R.push_back(std::get<0>(D[(X + i) % D.size()])[0]);
		R.push_back(std::get<0>(D[i]).back());
	}
	
	return { R,X };
}

Data BlockSort_Enc(const DType& In) {//consume CPU Time
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
				return std::isless(AR, BR);
			}
		}
		A = B = DD;
		return false;
		});

	DType R;
	std::size_t L=0;

	for (std::size_t i = 0; i < D.size(); i++) {
		//R.push_back(std::get<0>(D[i]));
		R.push_back(In[(std::get<1>(D[i]) + In.size() - 1) % In.size()]);
		if (std::get<1>(D[i]) == 0) { L = i; }
	}

	return { R,L};

}


DType BlockSort_Dec( DType D, std::size_t N){///,const DType& O,const Data& A) {
	std::vector<std::tuple<Word, std::size_t>> V;
	DType R;

	//std::rotate(D.begin(), D.begin() + (D.size()-(N)), D.end());
	//std::rotate(D.begin(), D.begin() + N, D.end());

	for (std::size_t i = 0; i < D.size(); i++) {
		V.push_back({D[i], i });
	}

	std::stable_sort(V.begin(), V.end(), [](auto& A, auto& B) {return std::get<0>(A)<std::get<0>(B); });

	for (std::size_t i = 0; i <V.size(); i++) {
		N = std::get<1>(V[N]);
		R.push_back(D[N]);	

	}
	//std::rotate(R.begin(), R.begin()+1, R.end());
	//std::rotate(R.begin(), R.end()-N, R.end());
	//std::reverse(R.begin(), R.end());

	return R;
}

DType MakeCacao() {
	DType R = { 'c','a','c','a','o'};

	return R;
}

DType Make_cdebaaaa() {
	DType R = { 'c','d','e','b','a','a','a','a'};

	return R;
}
DType MakePapaya() {
	DType R = { 'p','a','p','a','y','a',};

	return R;
}
DType MakeBanana() {
	DType R = { 'b','a','n','a','n','a',};

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
	//auto D = Make_cdebaaaa();
	//auto D = MakePapaya();
	//auto D = MakeBanana(); 
	//auto D = MakeVecor2(8);
	//auto D = MakeVecor2(128);

	auto D = MakeVecor2(1280);	
	
	Show(D);
	std::cout << std::endl;

	auto A = BlockSort_EncII(D);

	Show(std::get<0>(A));
	std::cout << std::endl;

	auto B = BlockSort_Dec(std::get<0>(A), std::get<1>(A));// , D, A);

	Show(B);
	std::cout << std::endl;
	if (D == B) {
		std::cout<< std::endl << "good" << std::endl;
	}else{
		std::cout<< std::endl << "Bad" << std::endl;
	}

	return 0;
	


}