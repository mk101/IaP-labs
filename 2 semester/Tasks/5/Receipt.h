#pragma once
#include <string>
#include <vector>


struct Record {
	std::wstring Name;
	size_t CostForOne;
	size_t Count;
	size_t Cost;
};

class Receipt {
private:
	std::vector<Record> Records;
	size_t Cost;
	size_t Sale;
	size_t ToPay;
public:
	Receipt(const std::vector<Record>& records, size_t cost, size_t sale);
	std::wstring ToString() const;
};
