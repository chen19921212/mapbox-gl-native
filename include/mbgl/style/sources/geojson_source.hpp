#pragma once

#include <mbgl/style/source.hpp>
#include <mbgl/util/geojson.hpp>

namespace mbgl {
namespace style {

struct GeoJSONOptions {
    // GeoJSON-VT options
    uint8_t maxzoom = 18;
    uint16_t buffer = 64;
    double tolerance = 3.0;

    // Supercluster options
    bool cluster = false;
    uint16_t clusterRadius = 400;
    uint8_t clusterMaxZoom = 17;
};

class GeoJSONSource : public Source {
public:
    GeoJSONSource(const std::string& id, const GeoJSONOptions& options_ = GeoJSONOptions());

    void setURL(const std::string& url);
    void setGeoJSON(GeoJSON&&);

    // Private implementation

    class Impl;
    Impl* const impl;
};

} // namespace style
} // namespace mbgl
