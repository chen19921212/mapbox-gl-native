#pragma once

#include <mbgl/util/noncopyable.hpp>
#include <mbgl/map/map.hpp>
#include <mbgl/style/layer.hpp>

#include "value.hpp"

#include <jni/jni.hpp>

namespace mbgl {
namespace android {

class Layer : private mbgl::util::noncopyable {
public:

    static constexpr auto Name() { return "com/mapbox/mapboxsdk/style/layers/Layer"; };

    /*
     * Called when a Java object is created on the c++ side
     */
    Layer(mbgl::Map&, mbgl::style::Layer&);

    /*
     * Called when a Java object was created from the jvm side
     */
    Layer(jni::JNIEnv&, std::unique_ptr<mbgl::style::Layer>);

    virtual ~Layer();

    virtual jni::jobject* createJavaPeer(jni::JNIEnv&) = 0;

    jni::String getId(jni::JNIEnv&);

    void setLayoutProperty(jni::JNIEnv&, jni::String, jni::Object<> value);

    void setPaintProperty(jni::JNIEnv&, jni::String, jni::Object<> value);

protected:
    std::unique_ptr<mbgl::style::Layer> ownedLayer;
    mbgl::style::Layer& layer;
    mbgl::Map* map;

};

} //android
} //mbgl




