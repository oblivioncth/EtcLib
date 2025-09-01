# Add via ob standard library
include(OB/Library)
ob_add_standard_library(${LIB_TARGET_NAME}
    NAMESPACE "${PROJECT_NAMESPACE}"
    ALIAS "${LIB_ALIAS_NAME}"
    EXPORT_HEADER
        BASE_NAME "${LIB_ALIAS_NAME}"
        PATH "${PROJECT_NAME_LC}/${PROJECT_NAME_LC}_export.h"
    HEADERS_API
        COMMON "${LIB_ALIAS_NAME}"
        FILES
            Etc.h
            EtcColor.h
            EtcColorFloatRGBA.h
            EtcConfig.h
            EtcImage.h
    IMPLEMENTATION
        Etc.cpp
        EtcImage.cpp
        Codec/EtcBlock4x4.cpp
        Codec/EtcBlock4x4.h
        Codec/EtcBlock4x4Encoding.cpp
        Codec/EtcBlock4x4Encoding.h
        Codec/EtcBlock4x4EncodingBits.h
        Codec/EtcBlock4x4Encoding_ETC1.cpp
        Codec/EtcBlock4x4Encoding_ETC1.h
        Codec/EtcBlock4x4Encoding_R11.cpp
        Codec/EtcBlock4x4Encoding_R11.h
        Codec/EtcBlock4x4Encoding_RG11.cpp
        Codec/EtcBlock4x4Encoding_RG11.h
        Codec/EtcBlock4x4Encoding_RGB8.cpp
        Codec/EtcBlock4x4Encoding_RGB8.h
        Codec/EtcBlock4x4Encoding_RGB8A1.cpp
        Codec/EtcBlock4x4Encoding_RGB8A1.h
        Codec/EtcBlock4x4Encoding_RGBA8.cpp
        Codec/EtcBlock4x4Encoding_RGBA8.h
        Codec/EtcDifferentialTrys.cpp
        Codec/EtcDifferentialTrys.h
        Codec/EtcErrorMetric.h
        Codec/EtcIndividualTrys.cpp
        Codec/EtcIndividualTrys.h
        Codec/EtcMath.cpp
        Codec/EtcMath.h
    CONFIG STANDARD
)