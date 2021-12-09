// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"

void checkDimension(int a, int b) {
	if (a != b) {
		throw comp6771::euclidean_vector_error("Dimensions of LHS(" + std::to_string(a) + ") and RHS("
		                                       + std::to_string(b) + ") do not match\n");
	}
}

void checkDivision(double a) {
	if (a == 0.0) {
		throw comp6771::euclidean_vector_error("Invalid vector division by 0\n");
	}
}

void checkIndex(int a, int dim) {
	if (a < 0 or a >= dim) {
		throw comp6771::euclidean_vector_error("Index " + std::to_string(a)
		                                       + " is not valid for this euclidean_vector object\n");
	}
}

namespace comp6771 {
	euclidean_vector& euclidean_vector::operator=(euclidean_vector const& ev) {
		euclidean_vector temp = ev;
		std::swap(temp.dimension_, this->dimension_);
		std::swap(temp.magnitude_, this->magnitude_);
		return *this;
	}

	euclidean_vector& euclidean_vector::operator=(euclidean_vector&& ev) {
		euclidean_vector temp = ev;
		std::swap(temp.dimension_, this->dimension_);
		std::swap(temp.magnitude_, this->magnitude_);

		ev.magnitude_ = nullptr;
		ev.dimension_ = 0;
		ev.norm_ = -1;
		return *this;
	}

	euclidean_vector::operator std::vector<double>() {
		std::vector<double> vec;
		for (int i = 0; i < this->dimension_; i++) {
			vec.push_back(this->at(i));
		}
		return vec;
	}

	euclidean_vector::operator std::list<double>() {
		std::list<double> lst;
		for (int i = 0; i < this->dimension_; i++) {
			lst.push_back(this->at(i));
		}
		return lst;
	}

	double& euclidean_vector::operator[](int i) {
		assert(i < dimension_ and i >= 0);
		norm_ = -1;
		return magnitude_[static_cast<size_t>(i)];
	}

	double euclidean_vector::operator[](int i) const {
		assert(i < dimension_ and i >= 0);
		return magnitude_[static_cast<size_t>(i)];
	}

	euclidean_vector operator+(euclidean_vector lhs) {
		return lhs;
	}

	euclidean_vector operator-(euclidean_vector lhs) {
		for (int i = 0; i < lhs.dimension_; i++) {
			lhs.magnitude_[static_cast<size_t>(i)] = lhs.at(i) * (-1);
		}
		return lhs;
	}

	euclidean_vector& euclidean_vector::operator+=(euclidean_vector const& rhs) {
		checkDimension(this->dimension_, rhs.dimension_);
		std::unique_ptr<double[]> temp =
		   std::make_unique<double[]>(static_cast<size_t>(rhs.dimension_));
		for (int i = 0; i < rhs.dimension_; i++) {
			this->at(i) += rhs.at(i);
		}
		this->norm_ = -1;
		return *this;
	}

	euclidean_vector& euclidean_vector::operator-=(euclidean_vector const& rhs) {
		checkDimension(this->dimension_, rhs.dimension_);
		std::unique_ptr<double[]> temp =
		   std::make_unique<double[]>(static_cast<size_t>(rhs.dimension_));
		for (int i = 0; i < rhs.dimension_; i++) {
			this->at(i) -= rhs.at(i);
		}
		this->norm_ = -1;
		return *this;
	}

	euclidean_vector& euclidean_vector::operator*=(double rhs) {
		for (int i = 0; i < this->dimension_; i++) {
			this->at(i) *= rhs;
		}
		this->norm_ = -1;
		return *this;
	}

	euclidean_vector& euclidean_vector::operator/=(double rhs) {
		checkDivision(rhs);
		for (int i = 0; i < this->dimension_; i++) {
			this->at(i) /= rhs;
		}
		this->norm_ = -1;
		return *this;
	}

	double euclidean_vector::at(int i) const {
		checkIndex(i, this->dimension_);
		return this->magnitude_[static_cast<size_t>(i)];
	}

	double& euclidean_vector::at(int i) {
		checkIndex(i, this->dimension_);
		return this->magnitude_[static_cast<size_t>(i)];
	}

	int euclidean_vector::dimensions() const {
		return this->dimension_;
	}

	int euclidean_vector::dimensions() {
		return this->dimension_;
	}

	double euclidean_vector::getNorm() const {
		return this->norm_;
	}

	void euclidean_vector::setNorm(double n) const {
		this->norm_ = n;
	}

	bool operator==(euclidean_vector const& lhs, euclidean_vector const& rhs) {
		if (lhs.dimension_ != rhs.dimension_) {
			return false;
		}
		for (int i = 0; i < lhs.dimension_; i++) {
			if (lhs.at(i) != rhs.at(i)) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(euclidean_vector const& lhs, euclidean_vector const& rhs) {
		return !(lhs == rhs);
	}

	euclidean_vector operator+(euclidean_vector const& lhs, euclidean_vector const& rhs) {
		checkDimension(lhs.dimension_, rhs.dimension_);
		auto res = comp6771::euclidean_vector(lhs.dimension_);

		for (int i = 0; i < lhs.dimension_; i++) {
			res.magnitude_[static_cast<size_t>(i)] = lhs.at(i) + rhs.at(i);
		}

		return res;
	}

	euclidean_vector operator-(euclidean_vector const& lhs, euclidean_vector const& rhs) {
		checkDimension(lhs.dimension_, rhs.dimension_);
		auto res = comp6771::euclidean_vector(lhs.dimension_);

		for (int i = 0; i < lhs.dimension_; i++) {
			res.magnitude_[static_cast<size_t>(i)] = lhs.at(i) - rhs.at(i);
		}

		return res;
	}

	euclidean_vector operator*(euclidean_vector const& lhs, double rhs) {
		auto res = comp6771::euclidean_vector(lhs.dimension_);

		for (int i = 0; i < lhs.dimension_; i++) {
			res.magnitude_[static_cast<size_t>(i)] = lhs.at(i) * rhs;
		}
		return res;
	}

	euclidean_vector operator*(double lhs, euclidean_vector const& rhs) {
		return rhs * lhs;
	}

	euclidean_vector operator/(euclidean_vector const& lhs, double rhs) {
		checkDivision(rhs);
		auto res = comp6771::euclidean_vector(lhs.dimension_);

		for (int i = 0; i < lhs.dimension_; i++) {
			res.magnitude_[static_cast<size_t>(i)] = lhs.at(i) / rhs;
		}
		return res;
	}

	std::ostream& operator<<(std::ostream& os, euclidean_vector const& ev) {
		os << "[";
		for (int i = 0; i < ev.dimension_; i++) {
			if (i == ev.dimension_ - 1) {
				os << ev.magnitude_[static_cast<size_t>(i)];
			}
			else {
				os << ev.magnitude_[static_cast<size_t>(i)] << " ";
			}
		}
		os << "]";
		return os;
	}

	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.dimensions() == 0) {
			return 0.0;
		}
		if (v.getNorm() == -1) {
			double total = 0;
			for (int i = 0; i < v.dimensions(); i++) {
				total += v.at(i) * v.at(i);
			}
			v.setNorm(sqrt(total));
			return sqrt(total);
		}
		else {
			return v.getNorm();
		}
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw comp6771::euclidean_vector_error("euclidean_vector with no dimensions does not have "
			                                       "a unit vector");
		}
		auto norm = euclidean_norm(v);
		if (norm == 0) {
			throw comp6771::euclidean_vector_error("euclidean_vector with zero euclidean normal does "
			                                       "not have a unit vector");
		}

		auto res = comp6771::euclidean_vector(v.dimensions());

		for (int i = 0; i < v.dimensions(); i++) {
			res.at(i) = v.at(i) / norm;
		}
		return res;
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		checkDimension(x.dimensions(), y.dimensions());
		double res = 0;
		for (int i = 0; i < x.dimensions(); i++) {
			res += x.at(i) * y.at(i);
		}

		return res;
	}

} // namespace comp6771
