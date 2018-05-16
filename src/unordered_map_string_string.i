
#ifdef SWIGJAVA

%include "cstring_to_jstring.i"

%typemap(jni) std::unordered_map<std::string, std::string>&, std::unordered_map<std::string, std::string>* "jobject"
%typemap(jtype) std::unordered_map<std::string, std::string>&, std::unordered_map<std::string, std::string>* "Object"
%typemap(jstype) std::unordered_map<std::string, std::string>&, std::unordered_map<std::string, std::string>* "java.util.HashMap<String ,String>"

%typemap(in) std::unordered_map<std::string, std::string>& (std::unordered_map<std::string, std::string> sMap), std::unordered_map<std::string, std::string>* (std::unordered_map<std::string, std::string> sMap)
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

  while(jenv->CallBooleanMethod(iterator, hasNextMethodId))
  {
    jobject entry = jenv->CallObjectMethod(iterator, nextMethodId);
    jstring key = (jstring)jenv->CallObjectMethod(entry, getKeyMethodId);
    jstring value = (jstring)jenv->CallObjectMethod(entry, getValueMethodId);

    const char* keyResult = jenv->GetStringUTFChars(key, NULL);
    if(!keyResult)  return $null;

    const char* valueResult = jenv->GetStringUTFChars(value, NULL);
    if(!valueResult)  return $null;

    sMap.insert(std::make_pair(keyResult, valueResult));

    jenv->ReleaseStringUTFChars(value, valueResult);
    jenv->ReleaseStringUTFChars(key, keyResult);
    jenv->DeleteLocalRef(value);
    jenv->DeleteLocalRef(key);
    jenv->DeleteLocalRef(entry);
  }

  $1 = &sMap;
}
%typemap(out) std::unordered_map<std::string, std::string>&, std::unordered_map<std::string, std::string>*
{
  jclass hashMapClazz = jenv->FindClass("java/util/HashMap");
  jmethodID initMethodId = jenv->GetMethodID(hashMapClazz, "<init>", "()V");
  jmethodID putMethodId = jenv->GetMethodID(hashMapClazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
  $result = jenv->NewObject(hashMapClazz, initMethodId);

  const std::unordered_map<std::string, std::string>::const_iterator itEnd = (*$1).end();
  for(std::unordered_map<std::string, std::string>::const_iterator it = (*$1).begin();  it != itEnd;  ++it)
  {
    jstring key = cstr2jstr(jenv, it->first);
    jstring value = cstr2jstr(jenv, it->second);

    jenv->CallObjectMethod($result, putMethodId, key, value);

    jenv->DeleteLocalRef(value);
    jenv->DeleteLocalRef(key);
  }
}

%typemap(javain) std::unordered_map<std::string, std::string>&, std::unordered_map<std::string, std::string>* "$javainput"
%typemap(javaout) std::unordered_map<std::string, std::string>&, std::unordered_map<std::string, std::string>* %{
  {
    return (java.util.HashMap<String, String>)$jnicall;
  }
%}

#endif
