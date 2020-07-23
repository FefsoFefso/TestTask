// Skvortsov Kirill
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

const std::string PATH = "/home/fefso/CLionProjects/picture_convert/flowers.jpeg";
const int NEW_COLS = 700;
const int NEW_ROWS = 700;

int GetId(int id, double coef) {
    return (int)(coef * (double)id - 0.5);
}

int main(int argc, char** argv) {
    cv::Mat image = cv::imread(PATH);

    if (!image.data) {
        std::cout <<  "Can't get image" << std::endl ;
        return 0;
    }

    cv::Mat new_image(NEW_ROWS, NEW_COLS, CV_8UC3, cv::Scalar(0, 0, 0));

    double match_rows_coef = (double)image.rows / (double)NEW_ROWS;
    double match_cols_coef = (double)image.cols / (double)NEW_COLS;

    for (int i = 0; i < NEW_ROWS; ++i) {
        for (int j = 0; j < NEW_COLS; ++j) {
            new_image.at<cv::Vec3b>(i, j)[0] =
                    image.at<cv::Vec3b>(GetId(i, match_rows_coef), GetId(j, match_cols_coef))[0];

            new_image.at<cv::Vec3b>(i, j)[1] =
                    image.at<cv::Vec3b>(GetId(i, match_rows_coef), GetId(j, match_cols_coef))[1];

            new_image.at<cv::Vec3b>(i, j)[2] =
                    image.at<cv::Vec3b>(GetId(i, match_rows_coef), GetId(j, match_cols_coef))[2];
        }
    }

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", new_image);

    cv::waitKey(0);
    return 0;
}
