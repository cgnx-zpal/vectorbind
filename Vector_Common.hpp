#include <vector>
#include <array>
#include <cstring>

template <typename T>
void increase(std::vector<T> &v)
{
  for(auto &item : v)
  {
    ++item;
  }
}

template <typename T>
void append1(std::vector<T> &v)
{
  v.push_back(T());
}

long constexpr operator""_KB(unsigned long long const x) { return 1024L * x; }
long constexpr operator""_MB(unsigned long long const x) { return 1024_KB * x; }

class BigData
{
public:
  using ArrayType = std::array<uint8_t, 1_MB>;
  BigData() { std::memset(&data, 0, data.size()); }
  std::array<uint8_t, 1_MB> data;
  friend BigData &operator++(BigData &b) 
  { 
    for(auto &item : b.data)
      ++item; 
    return b;
  }
  friend bool operator == (const BigData &lh, const BigData &rh)
  {
    if(lh.data.size() != rh.data.size())
      return false;

    for (size_t i = 0; i < lh.data.size(); ++i)
      if (lh.data[i] != rh.data[i])
        return false;

    return true;
  }
  friend bool operator != (const BigData &lh, const BigData &rh)
  {
    return !(lh == rh);
  }
};

// extern int getBigData(std::vector<BigData> v, size_t idx1, size_t idx2);
inline int getBigData(std::vector<BigData> v, size_t idx1, size_t idx2)
{
  return v[idx1].data[idx2];
}

template <typename T>
class foo
{
public:
  foo(){}
  foo(foo<T> const &other) = default;
  foo(std::string name, std::vector<T> items)
      : name_(std::move(name)), items_(std::move(items)) {}

  std::string name_;
  std::vector<T> items_;

  std::string const& getName() const { return name_; }
  void setName(std::string name) { name = std::move(name); }
  std::vector<T> & getItems() { return items_; }
};
