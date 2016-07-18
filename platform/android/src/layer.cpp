#include "layer.hpp"
#include "android_conversion.hpp"

#include <jni/jni.hpp>

#include <mbgl/platform/log.hpp>
#include <mbgl/style/conversion.hpp>
#include <mbgl/style/conversion/layer.hpp>

#include <string>

//XXX
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace mbgl {
namespace android {

    /**
     * Invoked when the construction is initiated from the jvm
     */
    Layer::Layer(jni::JNIEnv& env, std::unique_ptr<mbgl::style::Layer> coreLayer)
        : ownedLayer(std::move(coreLayer))
        , layer(*ownedLayer) {

        mbgl::Log::Debug(mbgl::Event::JNI, "Layer constructed, owning reference");
    }

    Layer::Layer(mbgl::Map& coreMap, mbgl::style::Layer& coreLayer) : layer(coreLayer) , map(&coreMap) {
        mbgl::Log::Debug(mbgl::Event::JNI, "Non-owning reference constructor");
    }

    Layer::~Layer() {
        mbgl::Log::Debug(mbgl::Event::JNI, "Layer destroyed");
    }

    jni::String Layer::getId(jni::JNIEnv& env) {
        return jni::Make<jni::String>(env, layer.getID());
    }

    void Layer::setLayoutProperty(jni::JNIEnv& env, jni::String jname, jni::Object<> jvalue) {
        mbgl::Log::Debug(mbgl::Event::JNI, "Set layout property");

        Value value(env, jvalue);

        //Convert and set property
        optional<mbgl::style::conversion::Error> error = mbgl::style::conversion::setLayoutProperty(layer, jni::Make<std::string>(env, jname), value);
        if (error) {
            mbgl::Log::Error(mbgl::Event::JNI, "Error setting property: " + jni::Make<std::string>(env, jname) + " " + error->message);
            return;
        }

        //Update the style
        map->update(mbgl::Update::RecalculateStyle);
    }

    void Layer::setPaintProperty(jni::JNIEnv& env, jni::String jname, jni::Object<> jvalue) {
        mbgl::Log::Debug(mbgl::Event::JNI, "Set paint property");

        Value value(env, jvalue);

        //Convert and set property
        //TODO: paint class
        optional<mbgl::style::conversion::Error> error = mbgl::style::conversion::setPaintProperty(layer, jni::Make<std::string>(env, jname), value, mbgl::optional<std::string>());
        if (error) {
            mbgl::Log::Error(mbgl::Event::JNI, "Error setting property: " + jni::Make<std::string>(env, jname) + " " + error->message);
            return;
        }

        //Update the style
        map->update(mbgl::Update::RecalculateStyle | mbgl::Update::Classes);
    }
}
}