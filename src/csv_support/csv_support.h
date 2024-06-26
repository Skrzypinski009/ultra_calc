#pragma once
#include <string>
#include <vector>
#include "../workspace/table.h"
#include "../workspace/workspace.h"

namespace uc {
  namespace csv {
    std::vector<std::string>* getLines(std::string csv_path);
    Table* createTable(std::vector<std::string>* lines, Workspace* workspace);

    std::vector<std::string>* getLines(Table* table, const bool raw);
    void saveTable(const std::string& path, std::vector<std::string>* lines);
  }
}
