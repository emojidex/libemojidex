%module(package="Emojidex::Data") UnorderedMap

%{
#include "data/unordered_map.h"
%}

//%include "./unordered_map.h"
namespace Emojidex {
  namespace Data {
    // UnorderedMap is a wrapper around std::unordered map for portability
    template<class K, class V>
    class UnorderedMap : public std::unordered_map<K, V>
    {
    public:
      typedef typename std::unordered_map<K, V> base;
      typedef typename base::value_type      value_type;

      UnorderedMap() : base() { /* nop */ }

      //UnorderedMap(std::initializer_list<value_type> values) : base()
      //{
      //  const typename std::initializer_list<value_type>::const_iterator itEnd = values.end();
      //  for(typename std::initializer_list<value_type>::const_iterator it = values.begin();  it != itEnd;  ++it)
      //    this->insert(*it);
      //}

      ~UnorderedMap(){ /* nop */ }
    };
  }
}
