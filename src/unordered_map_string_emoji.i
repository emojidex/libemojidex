
#ifdef SWIGJAVA

%typemap(jni) std::unordered_map<std::string, Emojidex::Data::Emoji>* "jobject"
%typemap(jtype) std::unordered_map<std::string, Emojidex::Data::Emoji>* "Object"
%typemap(jstype) std::unordered_map<std::string, Emojidex::Data::Emoji>* "java.util.HashMap<String , com.emojidex.libemojidex.Emojidex.Data.Emoji>"

%typemap(in) std::unordered_map<std::string, Emojidex::Data::Emoji>* (std::unordered_map<std::string, Emojidex::Data::Emoji> sMap)
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
  jclass emojiClazz = jenv->FindClass("com/emojidex/libemojidex/Emojidex/Data/Emoji");
  jmethodID getCPtrMethodId = jenv->GetStaticMethodID(emojiClazz, "getCPtr", "(Lcom/emojidex/libemojidex/Emojidex/Data/Emoji;)J");

  while(jenv->CallBooleanMethod(iterator, hasNextMethodId))
  {
    jobject entry = jenv->CallObjectMethod(iterator, nextMethodId);
    jstring key = (jstring)jenv->CallObjectMethod(entry, getKeyMethodId);
    jobject value = jenv->CallObjectMethod(entry, getValueMethodId);

    const char* keyResult = jenv->GetStringUTFChars(key, NULL);
    if(!keyResult)  return $null;

    const Emojidex::Data::Emoji *valueResult = (Emojidex::Data::Emoji *)jenv->CallStaticLongMethod(emojiClazz, getCPtrMethodId, value);
    if(!valueResult)  return $null;

    sMap.insert(std::make_pair(keyResult, *valueResult));

    jenv->ReleaseStringUTFChars(key, keyResult);
    jenv->DeleteLocalRef(value);
    jenv->DeleteLocalRef(key);
    jenv->DeleteLocalRef(entry);
  }

  $1 = &sMap;
}
%typemap(out) std::unordered_map<std::string, Emojidex::Data::Emoji>*
{
  jclass hashMapClazz = jenv->FindClass("java/util/HashMap");
  jmethodID initMethodId = jenv->GetMethodID(hashMapClazz, "<init>", "()V");
  jmethodID putMethodId = jenv->GetMethodID(hashMapClazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
  $result = jenv->NewObject(hashMapClazz, initMethodId);

  jclass emojiClazz = jenv->FindClass("com/emojidex/libemojidex/Emojidex/Data/Emoji");
  jmethodID emojiInitMethodId = jenv->GetMethodID(emojiClazz, "<init>", "(JZ)V");

  const std::unordered_map<std::string, Emojidex::Data::Emoji>::const_iterator itEnd = (*$1).end();
  for(std::unordered_map<std::string, Emojidex::Data::Emoji>::const_iterator it = (*$1).begin();  it != itEnd;  ++it)
  {
    jobject emoji = jenv->NewObject(emojiClazz, emojiInitMethodId, (jlong)new Emojidex::Data::Emoji((const Emojidex::Data::Emoji &)it->second), true);

    jenv->CallObjectMethod($result, putMethodId, jenv->NewStringUTF(it->first.c_str()), emoji);
  }
}

%typemap(javain) std::unordered_map<std::string, Emojidex::Data::Emoji>* "$javainput"
%typemap(javaout) std::unordered_map<std::string, Emojidex::Data::Emoji>* %{
  {
    return (java.util.HashMap<String, com.emojidex.libemojidex.Emojidex.Data.Emoji>)$jnicall;
  }
%}

#endif
