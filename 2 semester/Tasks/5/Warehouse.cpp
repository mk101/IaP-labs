#include "Warehouse.h"

Warehouse::Warehouse() {
	Products.push_back({ std::string("0000"), std::wstring(L"Хлеб"), 30, 0 });
	Products.push_back({ std::string("0001"), std::wstring(L"Печенье"), 200, 10 });
	Products.push_back({ std::string("0002"), std::wstring(L"Вода"), 20, 10 });
}

const Product& Warehouse::GetProductByCode(const std::string& code) const {
	for (const auto &p : Products) {
		if (code == p.Code) {
			return p;
		}
	}

	return {std::string("0000"), std::wstring(L""), 0, 0};
}

std::vector<Product> Warehouse::GetProducts() const {
	return Products;
}
