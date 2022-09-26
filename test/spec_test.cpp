#include "cppmark.hpp"
#include <boost/ut.hpp> // import boost.ut;

constexpr auto sum(auto... args) { return (args + ...); }

int main() {
  using namespace boost::ut;

  "tab"_test = [] {
    {
      auto result = cppmark::md2html("\tfoo\tbaz\t\tbim\n");
      auto expected = "<pre><code>foo\tbaz\t\tbim\n</code></pre>\n";
      expect(result == expected);
    }
  };
}
