%module(package="Emojidex::Service") "Emojidex::Service::Transactor"

%nspace Emojidex::Service::Transactor;

%include <std_string.i>

#ifdef SWIGJAVA
%typemap(out) std::string
{
  jthrowable exception = jenv->ExceptionOccurred();
  if(exception != NULL) jenv->ExceptionClear();

  int len = $1.length();
  jstring encode = jenv->NewStringUTF("UTF-8");
  jclass string_class = jenv->FindClass("java/lang/String");
  jmethodID init_method = jenv->GetMethodID(string_class, "<init>", "([BLjava/lang/String;)V");
  jbyteArray byte_array = jenv->NewByteArray(len);

  if(encode != NULL && string_class != NULL && init_method != NULL && byte_array != NULL)
  {
    jenv->SetByteArrayRegion(byte_array, 0, len, (jbyte*)$1.c_str());

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
include "service/transactor.h"
%}

// Ignore unordered_map.
%ignore Emojidex::Service::Transactor::queryTemplate;
%ignore Emojidex::Service::Transactor::get;

// %include "service/transactor.h"
namespace Emojidex {
  namespace Service {
    // performs transactions with an emojidex API server
    class Transactor
    {
    private:
      std::string generateQueryString(const std::unordered_map<std::string, std::string>& query);
      boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* getStream();
      std::string request(const std::string& requestname, const std::string& endpoint, const std::unordered_map<std::string, std::string>& query, int* status);
    public:
      Transactor();

      std::unordered_map<std::string, std::string> queryTemplate(bool defaults = true);

      std::string get(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL);
      std::string post(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL);
      std::string del(const std::string& endpoint, const std::unordered_map<std::string, std::string>& query = {{"", ""}}, int* status = NULL);
    };
  }
}
