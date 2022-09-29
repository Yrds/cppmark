#ifndef CPPMARK_INCLUDED
#define CPPMARK_INCLUDED

#include <string>
#include <vector>
#include <string_view>

namespace cppmark {
  struct Block {
    std::string symbol;
    std::string content;
  };

  std::string
    md2html(std::string md);

  std::vector<Block>
    getBlocks(std::string md);

  std::string
    blocksToHtml(std::vector<Block> blocks);

  long unsigned int
    tabBlock(std::string_view mdView, std::vector<Block>& blocks);
}

#endif //MD_INCLUDED
