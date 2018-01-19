#ifndef EMOJIDEX_DATA_COMBINATION_H
#define EMOJIDEX_DATA_COMBINATION_H

#include <string>
#include <vector>
#include <unordered_map>

namespace Emojidex {
  namespace Data {
    class Combination
    {
    public:
      std::string base;
      std::vector<unsigned int> component_layer_order;
      std::vector< std::vector<std::string> > components;
      std::vector< std::unordered_map<std::string, Emojidex::Data::Checksums> > checksums;
    };
  }
}

#endif  /* EMOJIDEX_DATA_COMBINATION_H */
