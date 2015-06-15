#ifndef EMOJIDEX_DATA_UNORDERED_MAP_H
#define EMOJIDEX_DATA_UNORDERED_MAP_H

#include <tr1/unordered_map>
#include <initializer_list>

namespace Emojidex {
  namespace Data {
    template<class K, class V>
    class UnorderedMap : public std::tr1::unordered_map<K, V>
    {
    public:
      typedef typename std::tr1::unordered_map<K, V> base;
      typedef typename base::value_type      value_type;

      UnorderedMap() : base() { /* nop */ }

      UnorderedMap(std::initializer_list<value_type> values) : base()
      {
        const typename std::initializer_list<value_type>::const_iterator itEnd = values.end();
        for(typename std::initializer_list<value_type>::const_iterator it = values.begin();  it != itEnd;  ++it)
          this->insert(*it);
      }

      ~UnorderedMap(){ /* nop */ }
    };
  }
}

#endif /* EMOJIDEX_DATA_UNORDERED_MAP_H */
