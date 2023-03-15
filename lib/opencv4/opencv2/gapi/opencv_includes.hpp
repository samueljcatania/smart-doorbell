// This file is part of OpenCV project.

// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Copyright (C) 2018 Intel Corporation


#ifndef OPENCV_GAPI_OPENCV_INCLUDES_HPP
#define OPENCV_GAPI_OPENCV_INCLUDES_HPP

#if !defined(GAPI_STANDALONE)
#  include "../core/mat.hpp"
#  include "../core/cvdef.h"
#  include "../core/types.hpp"
#  include "../core/base.hpp"
#define GAPI_OWN_TYPES_LIST     cv::gapi::own::Rect,                           \
                                cv::gapi::own::Size,                           \
                                cv::gapi::own::Point,                          \
                                cv::gapi::own::Point2f,                        \
                                cv::gapi::own::Scalar,                         \
                                cv::gapi::own::Mat
#else   // Without OpenCV
#  include "own/cvdefs.hpp"
#  include "own/types.hpp"  // cv::gapi::own::Rect/Size/Point
#  include "own/scalar.hpp" // cv::gapi::own::Scalar
#  include "own/mat.hpp"
// replacement of cv's structures:
namespace cv {
    using Rect    = gapi::own::Rect;
    using Size    = gapi::own::Size;
    using Point   = gapi::own::Point;
    using Point2f = gapi::own::Point2f;
    using Scalar  = gapi::own::Scalar;
    using Mat     = gapi::own::Mat;
}  // namespace cv
#define GAPI_OWN_TYPES_LIST     cv::gapi::own::VoidType

#endif // !defined(GAPI_STANDALONE)

#endif // OPENCV_GAPI_OPENCV_INCLUDES_HPP
