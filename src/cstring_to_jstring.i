
%{
namespace
{
  jstring cstr2jstr(JNIEnv *jenv, const std::string& src)
  {
    jstring jresult = 0;

    jthrowable exception = jenv->ExceptionOccurred();
    if(exception != NULL) jenv->ExceptionClear();

    int len = src.length();
    jstring encode = jenv->NewStringUTF("UTF-8");
    jclass string_class = jenv->FindClass("java/lang/String");
    jmethodID init_method = jenv->GetMethodID(string_class, "<init>", "([BLjava/lang/String;)V");
    jbyteArray byte_array = jenv->NewByteArray(len);

    if(encode != NULL && string_class != NULL && init_method != NULL && byte_array != NULL)
    {
      jenv->SetByteArrayRegion(byte_array, 0, len, (jbyte*)src.c_str());

      jresult = (jstring)jenv->NewObject(string_class, init_method, byte_array, encode);
    }

    if(exception != NULL) jenv->Throw(exception);

    jenv->DeleteLocalRef((jobject)exception);
    jenv->DeleteLocalRef((jobject)encode);
    jenv->DeleteLocalRef((jobject)string_class);
    jenv->DeleteLocalRef((jobject)byte_array);

    return jresult;
  }
}
%}
