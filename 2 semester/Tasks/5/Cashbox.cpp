#include "Cashbox.h"

Cashbox::Cashbox() : wh() {}

void Cashbox::Scan(const std::string& code) {
	Scans.push_back(wh.GetProductByCode(code));
}

const Product& Cashbox::GetProduct(const std::string& code) const {
	return wh.GetProductByCode(code);
}

Receipt Cashbox::GetReceipt() const {
	std::vector<Record> records;
	bool f = true;
	size_t cost = 0;
	size_t sale = 0;

	for (const auto& p : Scans) {
		f = true;

		cost += p.Cost;
		sale += p.Cost * p.Sale / 100;

		for (auto& r : records) {
			if (r.Name == p.Name) {
				r.Count++;
				r.Cost += r.CostForOne;
				f = false;
				break;
			}
		}

		if (f) {
			records.push_back({ p.Name, p.Cost - (size_t)(p.Cost * p.Sale / 100), 1, p.Cost - (size_t)(p.Cost * p.Sale / 100) });
		}
	}

	return Receipt(records, cost, sale);
}

size_t Cashbox::GetCost() const {
	size_t cost = 0;
	for (const auto& p : Scans) {
		cost += p.Cost - (size_t)(p.Cost * p.Sale / 100);
	}

	return cost;
}

void Cashbox::Remove(const std::string& code) {
	auto iter = Scans.begin();
	
	while (iter != Scans.end()) {
		if (iter->Code == code) {
			Scans.erase(iter);
			return;
		}
		iter++;
	}
}

