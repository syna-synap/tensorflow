/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <jni.h>

#include <memory>
#include <type_traits>

#include "tensorflow/lite/delegates/external/external_delegate.h"


extern "C" {

JNIEXPORT jlong JNICALL
Java_org_tensorflow_lite_external_ExternalDelegate_createDelegate(
    JNIEnv* env, jclass clazz, jstring lib_dir, jstring cache_dir) {


  const char* lib_path = env->GetStringUTFChars(lib_dir, nullptr);
  if (!lib_path) {
      return 0;
  }

  auto options = TfLiteExternalDelegateOptionsDefault(lib_path);

  const char* cache_path = nullptr;

  if (cache_dir) {
    cache_path = env->GetStringUTFChars(cache_dir, nullptr);

    const char* allow_cache_key = "allowed_cache_mode";
    const char* allow_cache_value = "true";
    const char* cache_file_key = "cache_file_path";
    const char* cache_file_value = cache_path;
    options.insert(&options, allow_cache_key, allow_cache_value);
    options.insert(&options, cache_file_key, cache_file_value);

  }

  auto delegate = TfLiteExternalDelegateCreate(&options);

  if (lib_path) {
    env->ReleaseStringUTFChars(lib_dir, lib_path);
  }

  if (cache_dir) {
    env->ReleaseStringUTFChars(cache_dir, cache_path);
  }

  return reinterpret_cast<jlong>(delegate);
}


JNIEXPORT void JNICALL
Java_org_tensorflow_lite_external_ExternalDelegate_deleteDelegate(
    JNIEnv* env, jclass clazz, jlong delegate) {

  TfLiteExternalDelegateDelete(reinterpret_cast<TfLiteDelegate*>(delegate));
}

}  // extern "C"