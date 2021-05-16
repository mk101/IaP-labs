#pragma once
#include <vector>
#include <string>

struct Product {
	std::string Code;
	std::wstring Name;
	size_t Cost = 0;
	uint8_t Sale = 0;
};

class Warehouse {
private:
	std::vector<Product> Products;
public:
	Warehouse();
	const Product& GetProductByCode(const std::string& code) const;
	std::vector<Product> GetProducts() const;
};
