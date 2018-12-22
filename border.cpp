#include "Border.h"

Border::Border(const int &n_, std::vector<double> left_, std::vector<double> right_): n(n_), left(n_), right(n_){
    for(int i = 0; i < n; ++i){
        left[i] = left_[i];
        right[i] = right_[i];
    }
}

void Border::changeDim(const int &n_){
    n = n_;
}

void Border::changeLeft(std::vector<double> left_){
    left.resize(n);
    for(int i = 0; i < n; ++i){
        left[i] = left_[i];
    }
}

void Border::changeRight(std::vector<double> right_){
    right.resize(n);
    for(int i = 0; i < n; ++i){
        right[i] = right_[i];
    }
}

void Border::changeBorder(const int &n_, std::vector<double> left_, std::vector<double> right_){
    changeDim(n_);
    changeLeft(left_);
    changeRight(right_);
}
