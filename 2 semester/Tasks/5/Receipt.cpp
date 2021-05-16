#include "Receipt.h"

Receipt::Receipt(const std::vector<Record>& records, size_t cost, size_t sale) 
	: Records(records), Cost(cost), Sale(sale) {
	ToPay = Cost - Sale;
}

std::wstring Receipt::ToString() const {
	std::wstring res;

	for (const auto &r : Records) {
		res += r.Name + L" [" + std::to_wstring(r.CostForOne) + L"] x" + std::to_wstring(r.Count) + L" : " + std::to_wstring(r.Cost) + L"\n";
	}

	res += L"�����: " + std::to_wstring(Cost) + L"\n";
	res += L"������: " + std::to_wstring(Sale) + L"\n";
	res += L"� ������: " + std::to_wstring(ToPay) + L"\n";

	return res;
}
