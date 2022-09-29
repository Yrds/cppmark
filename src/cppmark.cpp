#include "cppmark.hpp"
#include <string_view>

namespace cppmark {
  std::string
    md2html(std::string md){
      auto blocks = getBlocks(md);

      return blocksToHtml(blocks);
    }

  std::vector<Block>
    getBlocks(std::string md) {
      std::vector<Block> blocks;

      std::string_view mdView{md.c_str()};

      int nextFind = 0;

      while(mdView.at(nextFind) != md.back()) {
        //If 4 spaces create a <pre><code> block
        if(mdView.substr(nextFind, 4) == "    "){

          auto blockStart = nextFind + 4;

          nextFind = tabBlock(mdView.substr(nextFind + blockStart), blocks) + nextFind;

          continue;
        } else {
          //Skip whitespaces
          while(mdView.at(nextFind) == ' ') {
            nextFind++;
          }

          if(mdView.at(nextFind) == '\t') {

            nextFind = tabBlock(mdView.substr(nextFind), blocks) + nextFind;

            continue;

          }

        }

        blocks.push_back({
            "",
            std::string(mdView.substr(nextFind).data())
            });
      }

      return blocks;
    }

  long unsigned int
    tabBlock(std::string_view mdView, std::vector<Block>& blocks) {

      //auto blockStart = nextFind + 1;

      auto blockStart = 1;

      auto nextFind = mdView.find("\n");

      auto content = std::string(mdView.substr(blockStart, nextFind).data());

      blocks.push_back({
          "\t",
          content
          });

      return nextFind;

    }

  std::string
    blocksToHtml(std::vector<Block> blocks) {
      std::string html;

      for(auto block: blocks) {
        if(block.symbol == "\t"){
          html.append("<pre><code>" + block.content + "</code></pre>\n");
          continue;
        }

        html.append(block.content);
      }

      return html;
    }
};
