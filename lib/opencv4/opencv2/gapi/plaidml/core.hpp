// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Copyright (C) 2019 Intel Corporation


#ifndef OPENCV_GAPI_PLAIDML_CORE_HPP
#define OPENCV_GAPI_PLAIDML_CORE_HPP

#include "../gkernel.hpp"     // GKernelPackage
#include "../own/exports.hpp" // GAPI_EXPORTS

namespace cv { namespace gapi { namespace core { namespace plaidml {

GAPI_EXPORTS cv::GKernelPackage kernels();

}}}}

#endif // OPENCV_GAPI_PLAIDML_CORE_HPP
