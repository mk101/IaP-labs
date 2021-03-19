//template<class E, typename D>
//ArrController<E, D>::ArrController() {
//	this->Length = 0;
//	this->Elements = nullptr;
//	this->Degrees = nullptr;
//}
//
//template<class E, typename D>
//ArrController<E, D>::ArrController(E* elems, D* degrees, uint len) {
//	assert(len > 0);
//	this->Length = len;
//	
//	this->Elements = new E[len];
//	this->Degrees = new D[len];
//	
//	for (uint i = 0; i < len; i++) {
//		this->Elements[i] = elems[i];
//		this->Degrees[i] = elems[i];
//	}
//}
//
//template<class E, typename D>
//ArrController<E, D>::ArrController(const ArrController& ac) {
//	this->Length = ac.Length;
//	
//	this->Elements = new E[this->Length];
//	this->Degrees = new D[this->Length];
//
//	for (uint i = 0; i < this->Length; i++) {
//		this->Elements[i] = ac.Elements[i];
//		this->Degrees[i] = ac.Degrees[i];
//	}
//}
//
//template<class E, typename D>
//ArrController<E, D>::~ArrController() {
//	this->Length = 0;
//	delete[] this->Elements;
//	delete[] this->Degrees;
//
//	this->Elements = nullptr;
//	this->Degrees = nullptr;
//}
//
//template<class E, typename D>
//void ArrController<E, D>::Add(const E& elem, const D& deg) {
//	E* newElems = new E[this->Length + 1];
//	D* newDegrees = new D[this->Length + 1];
//
//	for (uint i = 0; i < this->Length; i++) {
//		newElems[i] = this->Elements[i];
//		newDegrees[i] = this->Degrees[i];
//	}
//
//	newElems[this->Length] = elem;
//	newDegrees[this->Length] = deg;
//	this->Length++;
//	
//	delete[] this->Elements;
//	delete[] this->Degrees;
//
//	this->Elements = newElems;
//	this->Degrees = newDegrees;
//}
//
//template<class E, typename D>
//void ArrController<E, D>::Remove(int index) {
//	E* newElems = new E[this->Length - 1];
//	D* newDegs = new D[this->Length - 1];
//
//	uint k = 0;
//	for (uint i = 0; i < this->Length; i++) {
//		if (i != index) {
//			newElems[k] = this->Elements[i];
//			newDegs[k] = this->Degrees[i];
//		}
//	}
//
//	delete[] this->Elements;
//	delete[] this->Degrees;
//
//	this->Elements = newElems;
//	this->Degrees = newDegs;
//}
//
//template<class E, typename D>
//ArrController<E, D>& ArrController<E, D>::operator=(const ArrController& ac) {
//	this->Length = ac.Length;
//	
//	delete[] this->Elements;
//	delete[] this->Degrees;
//
//	this->Elements = new E[this->Length];
//	this->Degrees = new D[this->Length];
//
//	for (uint i = 0; i < this->Length; i++) {
//		this->Elements[i] = ac.Elements[i];
//		this->Degrees[i] = ac.Degrees[i];
//	}
//
//	return *this;
//}
//
//template<class E, typename D>
//E ArrController<E, D>::operator[](const int& index) {
//	E& elem = this->Elements[index];
//	D& deg = this->Degrees[index];
//	E newElem = E(elem);
//
//	for (D i = 0; i < deg; i++) {
//		newElem *= elem;
//	}
//
//	return newElem;
//}
//
//template<class E, typename D>
//std::ostream& operator<<(std::ostream& out, const ArrController<E, D>& ac) {
//	out << "(" << ac.Elements[0] << ")^" << ac.Degrees[0];
//	for (uint i = 1; i < ac.Length; i++) {
//		out << " + (" << ac.Elements[i] << ")^" << ac.Degrees[i];
//	}
//}
//
//template<class E, typename D>
//std::istream& operator>>(std::istream& in, ArrController<E, D>& ac){
//	uint len = 0;
//	in >> len;
//
//	E e;
//	D d;
//
//	for (uint i = 0; i < len; i++) {
//		in >> e;
//		in >> d;
//
//		ac.Add(e, d);
//	}
//}
