#include "cppmark.hpp"

namespace cppmark {
  std::string
    md2html(std::string md){
      auto blocks = getBlocks(md);

      return blocksToHtml(blocks);
    }

  std::vector<Block>
    getBlocks(std::string md) {
      std::vector<Block> blocks;


      int nextFind = 0;

      while(md.at(nextFind) != md.back()) {
        //If 4 spaces create a <pre><code> block
        if(md.substr(nextFind, 4) == "    "){

        auto blockStart = nextFind + 4;

        nextFind = md.find('\n', nextFind);

          blocks.push_back({
              "\t",
              md.substr(blockStart, nextFind)
              });

          continue;
        } else {
          //Skip whitespaces
          while(md.at(nextFind) == ' ') {
            nextFind++;
          }

          if(md.at(nextFind) == '\t') {
            auto blockStart = nextFind + 1;

            nextFind = md.find('\n', nextFind);

            while(md.at(blockStart) == ' ') {
              blockStart++;
            }



            blocks.push_back({
                "\t",
                md.substr(blockStart, nextFind)
                });
            continue;
          }

        }

        blocks.push_back({
            "",
            md.substr(nextFind)
            });
      }

      return blocks;
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
