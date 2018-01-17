%module(package="Emojidex::Data") "Emojidex::Data::Emoji"

%nspace Emojidex::Data::Emoji;

%include "StringVector.i"

// For java.
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
%ignore Emojidex::Data::Emoji::fillFromMsgPack;

%include "data/emoji.h"
