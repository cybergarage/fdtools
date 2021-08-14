// Copyright (C) 2020 Satoshi Konno. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <fdtools/img/image.h>
#include <fdtools/plugins/d88/d88.h>
#include <fdtools/plugins/raw/raw.h>

const std::string TEST_IMAGE_DIRECTORY = "./img";

void ImageLoarderExporterCompareTest(const boost::filesystem::path&, FDT_IMAGE_IMAGER);
void ImageExportTest(FdtImage* img, FDT_IMAGE_IMAGER export_image_new_func);
