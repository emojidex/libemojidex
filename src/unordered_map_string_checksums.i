
#ifdef SWIGJAVA

%include "cstring_to_jstring.i"

%typemap(jni) std::unordered_map<std::string, Emojidex::Data::Checksums>& "jobject"
%typemap(jtype) std::unordered_map<std::string, Emojidex::Data::Checksums>& "Object"
%typemap(jstype) std::unordered_map<std::string, Emojidex::Data::Checksums>& "java.util.HashMap<String , com.emojidex.libemojidex.Emojidex.Data.Checksums>"

%typemap(in) std::unordered_map<std::string, Emojidex::Data::Checksums>& (std::unordered_map<std::string, Emojidex::Data::Checksums> sMap)
{
  if(!$input)
  {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null map");
    return $null;
  }

  jclass hashMapClazz = jenv->FindClass("java/util/HashMap");
  jmethodID entrySetMethodId = jenv->GetMethodID(hashMapClazz, "entrySet", "()Ljava/util/Set;");
  jobject entrySet = jenv->CallObjectMethod($input, entrySetMethodId);
  if(!entrySet) return $null;

  jclass setClazz = jenv->FindClass("java/util/Set");
  jmethodID iteratorMethodId = jenv->GetMethodID(setClazz, "iterator", "()Ljava/util/Iterator;");
  jobject iterator = jenv->CallObjectMethod(entrySet, iteratorMethodId);
  if(!iterator) return $null;

  jclass iteratorClazz = jenv->FindClass("java/util/Iterator");
  jmethodID hasNextMethodId = jenv->GetMethodID(iteratorClazz, "hasNext", "()Z");
  jmethodID nextMethodId = jenv->GetMethodID(iteratorClazz, "next", "()Ljava/lang/Object;");
  jclass mapEntryClazz = jenv->FindClass("java/util/Map$Entry");
  jmethodID getKeyMethodId = jenv->GetMethodID(mapEntryClazz, "getKey", "()Ljava/lang/Object;");
  jmethodID getValueMethodId = jenv->GetMethodID(mapEntryClazz, "getValue", "()Ljava/lang/Object;");
  jclass checksumsClazz = jenv->FindClass("com/emojidex/libemojidex/Emojidex/Data/Checksums");
  jmethodID getCPtrMethodId = jenv->GetStaticMethodID(checksumsClazz, "getCPtr", "(Lcom/emojidex/libemojidex/Emojidex/Data/Checksums;)J");

  while(jenv->CallBooleanMethod(iterator, hasNextMethodId))
  {
    jobject entry = jenv->CallObjectMethod(iterator, nextMethodId);
    jstring key = (jstring)jenv->CallObjectMethod(entry, getKeyMethodId);
    jobject value = jenv->CallObjectMethod(entry, getValueMethodId);

    const char* keyResult = jenv->GetStringUTFChars(key, NULL);
    if(!keyResult)  return $null;

    const Emojidex::Data::Checksums *valueResult = (Emojidex::Data::Checksums *)jenv->CallStaticLongMethod(checksumsClazz, getCPtrMethodId, value);
    if(!valueResult)  return $null;

    sMap.insert(std::make_pair(keyResult, *valueResult));

    jenv->ReleaseStringUTFChars(key, keyResult);
    jenv->DeleteLocalRef(value);
    jenv->DeleteLocalRef(key);
    jenv->DeleteLocalRef(entry);
  }

  $1 = &sMap;
}
%typemap(out) std::unordered_map<std::string, Emojidex::Data::Checksums>&
{
  jclass hashMapClazz = jenv->FindClass("java/util/HashMap");
  jmethodID initMethodId = jenv->GetMethodID(hashMapClazz, "<init>", "()V");
  jmethodID putMethodId = jenv->GetMethodID(hashMapClazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
  $result = jenv->NewObject(hashMapClazz, initMethodId);

  jclass checksumsClazz = jenv->FindClass("com/emojidex/libemojidex/Emojidex/Data/Checksums");
  jmethodID checksumsInitMethodId = jenv->GetMethodID(checksumsClazz, "<init>", "(JZ)V");

  const std::unordered_map<std::string, Emojidex::Data::Checksums>::const_iterator itEnd = (*$1).end();
  for(std::unordered_map<std::string, Emojidex::Data::Checksums>::const_iterator it = (*$1).begin();  it != itEnd;  ++it)
  {
    jstring key = cstr2jstr(jenv, it->first);
    jobject value = jenv->NewObject(checksumsClazz, checksumsInitMethodId, (jlong)new Emojidex::Data::Checksums((const Emojidex::Data::Checksums &)it->second), true);

    jenv->CallObjectMethod($result, putMethodId, key, value);

    jenv->DeleteLocalRef(value);
    jenv->DeleteLocalRef(key);
  }
}

%typemap(javain) std::unordered_map<std::string, Emojidex::Data::Checksums>& "$javainput"
%typemap(javaout) std::unordered_map<std::string, Emojidex::Data::Checksums>& %{
  {
    return (java.util.HashMap<String, com.emojidex.libemojidex.Emojidex.Data.Checksums>)$jnicall;
  }
%}

#endif
