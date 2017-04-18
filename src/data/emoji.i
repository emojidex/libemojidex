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
    //! emoji data container
    class Emoji
    {
    public:
      //! The moji [character] or compound
      /*!
       * Standard emoji only. This contians the actual caracter or set 
       * of chracters. For example it could be "💩"
       */
      std::string moji;
      //! The name code/short code of the emoji
      std::string code;
      //! The unicode ID of the emoji
      std::string unicode;
      //! The category this emoji belongs in
      std::string category;
      //! The tags associated with this emoji
      std::vector<std::string> tags;
      //! The base emoji (what variants are based off of)
      /*!
       * In the case that this emoji is its own base, this value will be the 
       * same as the code attribute.
       */
      std::string base;
      //! The variants/variations of this emoji
      std::vector<std::string> variants;
      //! The link URL associated with this emoji, if any.
      std::string link;
      // detailed
      //! Identifies if the image associated with this emoji is wide
      bool is_wide;
      //! Identifies if copyright protection (no commercial use) has been applied
      bool copyright_lock;
      //! The number of times this emoji has been used
      unsigned int times_used;
      //! The number of times this emoji has been favorited
      unsigned int times_favorited;
      //! The score (weighted popularity, times used, and other factors)
      int score;
      //! The owner/author of the images and/or information of this emoji
      std::string attribution;
      //! The ID of the user who registered/controlls this emoji
      std::string user_id;
      //! The price of the control rights to this emoji
      double current_price;
      //! Identifies if this is the primary record for an emoji (rarely important)
      bool primary;
      //! Identifies if this emoji has been permanantly locked to an account
      bool permalock;
      //! Date the emoji was registered
      std::string registered_at;
      //! Date the link associated with this emoji expires (if there is a link)
      std::string link_expiration;
      //! Date the lock on this emoji expires (if there is a lock)
      std::string lock_expiration;
      //! Number of times this emoji has been edited/the image has changed
      unsigned int times_changed;
      //! Number of users who have added this emoji to their favorites
      unsigned int favorited;

      //! List of checksums for images. Use this to check if your images are up to date
      Emojidex::Data::Checksums checksums;

      Emoji();

      //! Fill the emoji information from a raw JSON string
      void fillFromJSONString(std::string json);
      //! Fill the emoji information from a RapidJSON value
      void fillFromJSON(rapidjson::Value& d);
      //! Fill the emoji information from a msgpack object
      void fillFromMsgPack(const msgpack::object& d);
    };
  }
}

// Rename template classes.
#ifndef TEMPLATE_STRING_VECTOR
#define TEMPLATE_STRING_VECTOR
%template(StringVector) std::vector<std::string>;
#endif
