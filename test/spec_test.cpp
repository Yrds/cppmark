#include "cppmark.hpp"
#include <boost/ut.hpp> // import boost.ut;

constexpr auto sum(auto... args) { return (args + ...); }

int main() {
  using namespace boost::ut;

  "Tabs"_test = [] {
    {
      auto result = cppmark::md2html("\tfoo\tbaz\t\tbim\n");
      auto expected = "<pre><code>foo\tbaz\t\tbim\n</code></pre>\n";

      expect(eq(result, expected)) << "message failure";
    }
    {
      auto result = cppmark::md2html("  \tfoo\tbaz\t\tbim\n");
      auto expected = "<pre><code>foo\tbaz\t\tbim\n</code></pre>\n";

      expect(eq(result, expected)) << "message failure";
    }

    //{
    //  auto result = cppmark::md2html("    a\ta\n    ὐ\ta\n");
    //  auto expected = "<pre><code>a\ta\nὐ\ta\n</code></pre>\n";

    //  expect(eq(result, expected)) << "message failure";
    //}
  };
}
