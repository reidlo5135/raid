#ifndef APPLICATION_SVM_HPP
#define APPLICATION_SVM_HPP

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <vector>
#include <regex>

namespace raid
{
    namespace ai
    {
        class SVMLearner final
        {
        private:
            std::vector<float> parse_path_string(const std::string &path_str);
        public:
            explicit SVMLearner();
            virtual ~SVMLearner();
            bool load_csv(const std::string &csv_name, cv::Mat &data, cv::Mat &labels);

        public:
            using SharedPtr = std::shared_ptr<SVMLearner>;

        };
    }
}

#endif