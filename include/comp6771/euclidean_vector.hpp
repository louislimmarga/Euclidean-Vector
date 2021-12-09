#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		euclidean_vector()
		: dimension_{1} {
			std::unique_ptr<double[]> temp =
			   std::make_unique<double[]>(static_cast<size_t>(this->dimension_));
			temp[0] = 0.0;
			this->magnitude_ = std::move(temp);
		}
		explicit euclidean_vector(int dim)
		: dimension_{dim} {
			std::unique_ptr<double[]> temp =
			   std::make_unique<double[]>(static_cast<size_t>(this->dimension_));
			for (int i = 0; i < this->dimension_; i++) {
				temp[static_cast<size_t>(i)] = 0.0;
			}
			this->magnitude_ = std::move(temp);
		}
		euclidean_vector(int dim, double val)
		: dimension_{dim} {
			std::unique_ptr<double[]> temp =
			   std::make_unique<double[]>(static_cast<size_t>(this->dimension_));
			for (int i = 0; i < this->dimension_; i++) {
				temp[static_cast<size_t>(i)] = val;
			}
			this->magnitude_ = std::move(temp);
		}
		euclidean_vector(std::vector<double>::const_iterator begin,
		                 std::vector<double>::const_iterator end)
		: dimension_{0} {
			auto temp = begin;
			while (temp != end) {
				dimension_ = dimension_ + 1;
				temp++;
			}
			size_t i = 0;
			std::unique_ptr<double[]> temp1 =
			   std::make_unique<double[]>(static_cast<size_t>(this->dimension_));
			while (begin != end) {
				temp1[i] = *begin;
				i++;
				begin++;
			}
			this->magnitude_ = std::move(temp1);
		}
		euclidean_vector(std::initializer_list<double> lst)
		: dimension_{static_cast<int>(lst.size())} {
			std::unique_ptr<double[]> temp =
			   std::make_unique<double[]>(static_cast<size_t>(this->dimension_));
			size_t i = 0;
			for (auto val : lst) {
				temp[static_cast<size_t>(i)] = val;
				i++;
			}
			this->magnitude_ = std::move(temp);
		}
		euclidean_vector(euclidean_vector const& ev)
		: dimension_{ev.dimension_} {
			std::unique_ptr<double[]> temp =
			   std::make_unique<double[]>(static_cast<size_t>(this->dimension_));
			for (int i = 0; i < this->dimension_; i++) {
				temp[static_cast<size_t>(i)] = ev.magnitude_[static_cast<size_t>(i)];
			}
			this->magnitude_ = std::move(temp);
		}
		euclidean_vector(euclidean_vector&& ev)
		: magnitude_(std::exchange(ev.magnitude_, nullptr))
		, dimension_{std::exchange(ev.dimension_, 0)} {}
		~euclidean_vector() noexcept = default;

		euclidean_vector& operator=(euclidean_vector const&);
		euclidean_vector& operator=(euclidean_vector&&);

		double& operator[](int i);
		double operator[](int i) const;

		friend euclidean_vector operator+(euclidean_vector);
		friend euclidean_vector operator-(euclidean_vector);

		euclidean_vector& operator+=(euclidean_vector const&);
		euclidean_vector& operator-=(euclidean_vector const&);
		euclidean_vector& operator*=(double);
		euclidean_vector& operator/=(double);

		explicit operator std::vector<double>();
		explicit operator std::list<double>();

		double at(int) const;
		double& at(int);
		int dimensions();
		int dimensions() const;

		friend bool operator==(euclidean_vector const&, euclidean_vector const&);
		friend bool operator!=(euclidean_vector const&, euclidean_vector const&);
		friend euclidean_vector operator+(euclidean_vector const&, euclidean_vector const&);
		friend euclidean_vector operator-(euclidean_vector const&, euclidean_vector const&);
		friend euclidean_vector operator*(euclidean_vector const&, double);
		friend euclidean_vector operator*(double, euclidean_vector const&);
		friend euclidean_vector operator/(euclidean_vector const&, double);
		friend std::ostream& operator<<(std::ostream&, euclidean_vector const&);

		double getNorm() const;
		void setNorm(double) const;

	private:
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		int dimension_;
		mutable double norm_ = -1;
	};

	auto euclidean_norm(euclidean_vector const& v) -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
