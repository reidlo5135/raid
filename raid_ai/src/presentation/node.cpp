#include "presentation/node.hpp"

using namespace raid::ai;

AINode::AINode()
    : Node(NODE_NAME)
{
    this->node_ = std::shared_ptr<rclcpp::Node>(this, [](rclcpp::Node *){});

    this->svm_learner_ = std::make_shared<SVMLearner>();

    std::string package_name = "raid_common";
    std::string package_path = ament_index_cpp::get_package_share_directory(package_name);
    std::string csv_path = package_path + "/csv/navigation.csv";

    RCLCPP_INFO(this->node_->get_logger(), "package_name : %s", package_name.c_str());
    RCLCPP_INFO(this->node_->get_logger(), "package_path : %s", package_path.c_str());
    RCLCPP_INFO(this->node_->get_logger(), "csv_path : %s", csv_path.c_str());

    cv::Mat data, labels;

    if (!this->svm_learner_->load_csv(csv_path, data, labels))
    {
        RCLCPP_ERROR(this->node_->get_logger(), "Unknown csv");
    }

    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(data, cv::ml::ROW_SAMPLE, labels);
    RCLCPP_INFO(this->node_->get_logger(), "traning done");

    cv::Mat testSample(1, data.cols, CV_32F, cv::Scalar(0));
    testSample.at<float>(0, 0) = 5.0;
    testSample.at<float>(0, 1) = 0.1;
    testSample.at<float>(0, 6) = 1.0;
    float prediction = svm->predict(testSample);
    RCLCPP_INFO(this->node_->get_logger(), "predicition : %f", prediction);
}

AINode::~AINode() = default;