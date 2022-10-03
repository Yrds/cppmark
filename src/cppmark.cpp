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

      std::string_view mdView{md.c_str()};

      unsigned long int nextFind = 0;

      while(mdView.at(nextFind) != md.back()) {
        //If 4 spaces create a <pre><code> block
        if(mdView.substr(nextFind, 4) == "    "){

          nextFind += 4;

          nextFind = tabBlock(mdView.substr(nextFind), blocks) + nextFind;

          continue;
        } else {
          //Skip whitespaces
          while(mdView.at(nextFind) == ' ') {
            nextFind++;
          }

          if(mdView.at(nextFind) == '\t') {

            nextFind++;
            nextFind = tabBlock(mdView.substr(nextFind), blocks) + nextFind;

            continue;

          }

        }

        if(nextFind < mdView.size()) {
          blocks.push_back({
              "",
              std::string(mdView.substr(nextFind).data())
              });
        }

        return blocks;
      }

      return blocks;
    }

  long unsigned int
    tabBlock(std::string_view mdView, std::vector<Block>& blocks) {

      constexpr auto blockStart = 0;

      auto nextFind = mdView.find("\n\n");

      if(nextFind == std::string_view::npos) {
        nextFind = mdView.size() - 1;
      }

      //TODO fix blockStart position
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
          std::string content = block.content;

          //NOTE This causing tests to failling
        
          for(unsigned long int tabPosition = content.find("    ", 0); tabPosition != std::string::npos; tabPosition = content.find("    ", tabPosition)) {
            content.replace(tabPosition, 4, "");
          }

          html.append("<pre><code>" + content + "</code></pre>\n");
          continue;
        }

        html.append("<p>" + block.content + "</p>");
      }

      return html;
    }
};
