# Description:
# Java Native Interface (JNI) library intended for implementing the
# TensorFlow Lite External Delegate Java API using the TensorFlow Lite CC library.

load("//tensorflow/lite:build_def.bzl", "tflite_copts")
load("//tensorflow/lite/core/shims:cc_library_with_tflite.bzl", "cc_library_with_tflite")

package(
    # copybara:uncomment default_applicable_licenses = ["//tensorflow:license"],
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],
)

cc_library_with_tflite(
    name = "native",
    srcs = ["external_delegate_impl_jni.cc"],
    copts = tflite_copts(),
    tags = [
        "manual",
        "notap",
    ],
    deps = [
        "//tensorflow/lite/delegates/external:external_delegate",
        "//tensorflow/lite/java/jni",
    ],
    alwayslink = 1,
)
