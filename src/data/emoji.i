%module(package="Emojidex::Data") "Emojidex::Data::Emoji"

%nspace Emojidex::Data::Emoji;

%include <std_string.i>
%include <std_vector.i>
%include "data/checksums.i"

// For java.
SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
%typemap(javaimports) Emojidex::Data::Emoji %{
import com.emojidex.libemojidex.StringVector;
%}

#ifdef SWIGJAVA
%typemap(out) const std::string&
{
  jthrowable exception = jenv->ExceptionOccurred();
  if(exception != NULL) jenv->ExceptionClear();

  int len = $1->length();
  jstring encode = jenv->NewStringUTF("UTF-8");
  jclass string_class = jenv->FindClass("java/lang/String");
  jmethodID init_method = jenv->GetMethodID(string_class, "<init>", "([BLjava/lang/String;)V");
  jbyteArray byte_array = jenv->NewByteArray(len);

  if(encode != NULL && string_class != NULL && init_method != NULL && byte_array != NULL)
  {
    jenv->SetByteArrayRegion(byte_array, 0, len, (jbyte*)$1->c_str());

    $result = (jstring)jenv->NewObject(string_class, init_method, byte_array, encode);
  }

  if(exception != NULL) jenv->Throw(exception);

  jenv->DeleteLocalRef((jobject)exception);
  jenv->DeleteLocalRef((jobject)encode);
  jenv->DeleteLocalRef((jobject)string_class);
  jenv->DeleteLocalRef((jobject)byte_array);
}
#endif

%{
#include "data/emoji.h"
%}

// Ignore rapidjson.
%ignore Emojidex::Data::Emoji::fillFromJSON;

// %include "data/emoji.h"
namespace Emojidex {
  namespace Data {
    // emoji base data
    class Emoji
    {
    public:
      std::string moji;
      std::string code;
      std::string unicode;
      std::string category;
      std::vector<std::string> tags;
      std::string base;
      std::vector<std::string> variants;
      std::string link;
      // detailed
      bool is_wide;
      bool copyright_lock;
      unsigned int times_used;
      unsigned int times_favorited;
      int score;
      std::string attribution;
      std::string user_id;
      double current_price;
      bool primary;
      bool permalock;
      std::string registered_at;
      std::string link_expiration;
      std::string lock_expiration;
      unsigned int times_changed;
      unsigned int favorited;

      Emojidex::Data::Checksums checksums;

      Emoji();

      void fillFromJSONString(std::string json);
      void fillFromJSON(rapidjson::Value& d);
    };
  }
}

// Rename template classes.
#ifndef TEMPLATE_STRING_VECTOR
#define TEMPLATE_STRING_VECTOR
%template(StringVector) std::vector<std::string>;
#endif
