#pragma once
#include "Warehouse.h"
#include "Receipt.h"

class Cashbox {
private:
	std::vector<Product> Scans;
	Warehouse wh;
public:
	Cashbox();
	void Scan(const std::string& code);
	const Product& GetProduct(const std::string& code) const;
	Receipt GetReceipt() const;
	size_t GetCost() const;
	void Remove(const std::string& code);
};
