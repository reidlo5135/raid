#include "application/svm.hpp"

using namespace raid::ai;

SVMLearner::SVMLearner()
{

}

SVMLearner::~SVMLearner()
{

}

std::vector<float>
SVMLearner::parse_path_string(const std::string &path_str)
{
    std::vector<float> path_data;
    std::regex number_regex("-?\\d+\\.\\d+");
    std::sregex_iterator iter(path_str.begin(), path_str.end(), number_regex);
    std::sregex_iterator end;

    while (iter != end)
    {
        path_data.push_back(stof((*iter).str()));
        ++iter;
    }

    return path_data;
}

bool
SVMLearner::load_csv(const std::string &csv_name, cv::Mat &data, cv::Mat &labels)
{
    std::ifstream file(csv_name);

    if (!file.is_open())
    {
        return false;
    }

    std::vector<std::vector<float>> data_vec;
    std::vector<int> label_vec;
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string time_str, path_str;

        getline(ss, time_str, ',');
        getline(ss, path_str, ',');

        std::vector<float> path_data = this->parse_path_string(path_str);

        if (!path_data.empty())
        {
            data_vec.push_back(path_data);
            label_vec.push_back(1);
        }
    }

    file.close();

    if (data_vec.empty())
    {
        std::cerr << "⚠ CSV 파일이 비어 있음!" << std::endl;
        return false;
    }

    int feature_size = data_vec[0].size();
    data = cv::Mat(data_vec.size(), feature_size, CV_32F);
    labels = cv::Mat(label_vec.size(), 1, CV_32S);

    for (size_t i = 0; i < data_vec.size(); i++)
    {
        for (size_t j = 0; j < feature_size; j++)
        {
            data.at<float>(i, j) = data_vec[i][j];
        }
        labels.at<int>(i, 0) = label_vec[i];
    }

    return true;
}