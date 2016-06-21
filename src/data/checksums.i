%module(package="Emojidex::Data") "Emojidex::Data::Checksums"

%nspace Emojidex::Data::Checksums;

%include <std_string.i>

%{
#include "data/checksums.h"
%}

// Ignore unordered_map.
%ignore Emojidex::Data::Checksums::png;

// %include "data/checksums.h"
namespace Emojidex {
  namespace Data {
    //! Holds a map of checksums for image assets that can be used to check against local assets
    class Checksums
    {
    public:
      //! The MD5 sum of the SVG file for an emoji
      std::string svg;
      //! A map of MD5 sums for various sizes of PNG images for an emoji
      std::unordered_map <std::string, std::string> png;

      //! Get the MD5 sum for a file of the specified format and specified size
      /*!
       * format_code can be either "svg" or "png"
       * size_code can be any size specified in the emojidex developer docs (eg: "px32" or "hdpi")
       */
      std::string sum(std::string format_code, std::string size_code);
    };
  }
}
