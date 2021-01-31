#include <iostream>
#include <cmath>
#include <iomanip>

#define ADFLT double

// ボトムアップ型クラス
class FBU {
    // 変数値
    double val;
    // 偏導関数値
    double d_val;
public:
    // コンストラクタ
    FBU(double v=0, double dv=0) {
        val = v;
        d_val = dv;
    }
    // 微分する入力変数として選択する関数
    void select(void) {
        d_val = 1.0;
    }
    // 変数値を返す
    double get_val(void) {
        return val;
    }
    // 偏導関数値を返す
    double get_d_val(void) {
        return d_val;
    }

    // 各種演算子の定義
    friend FBU operator + (FBU x, FBU y) {
        return FBU(x.val+y.val, x.d_val+y.d_val);
    }
    friend FBU operator - (FBU x, FBU y) {
        return FBU(x.val-y.val, x.d_val-y.d_val);
    }
    friend FBU operator * (FBU x, FBU y) {
        return FBU(x.val*y.val, x.d_val*y.val+x.val*y.d_val);
    }
    friend FBU operator / (FBU x, FBU y) {
        double w = x.val/y.val;
        return FBU(w, (x.d_val-w*y.d_val)/y.val);
    }
    friend FBU operator + (FBU x) {
        return FBU(x.val, x.d_val);
    }
    friend FBU operator - (FBU x) {
        return FBU(-x.val, -x.d_val);
    }
    friend bool operator < (FBU x, FBU y) {
        return x.val < y.val;
    }
    friend bool operator <= (FBU x, FBU y) {
        return x.val <= y.val;
    }
    friend bool operator > (FBU x, FBU y) {
        return x.val > y.val;
    }
    friend bool operator >= (FBU x, FBU y) {
        return x.val >= y.val;
    }
    
    // 基本関数の定義
    friend FBU sqrt(FBU x) {
        return FBU(std::sqrt(x.val), 0.5*x.d_val/std::sqrt(x.val));
    }
    friend FBU exp(FBU x) {
        return FBU(std::exp(x.val), x.d_val*std::exp(x.val));
    }
    friend FBU log(FBU x) {
        return FBU(log(x.val), x.d_val/x.val);
    }
    friend FBU pow(FBU x, FBU y)
    {
        return FBU(std::pow(x.val, y.val), y.val * std::pow(x.val, y.val - 1.0) * x.d_val);
    }
    friend FBU sin(FBU x)
    {
        return FBU(std::sin(x.val), std::cos(x.val) * x.d_val);
        
    }
    friend FBU cos(FBU x)
    {
        return FBU(std::cos(x.val), -1.0 * std::sin(x.val) * x.d_val);
    }
    friend FBU tan(FBU x)
    {
        return FBU(std::tan(x.val), x.d_val / std::pow(std::cos(x.val), 2.0));
    }
    friend FBU asin(FBU x)
    {
        return FBU(std::asin(x.val), x.d_val / std::sqrt(1.0 - std::pow(x.val, 2.0)));
    }
    friend FBU acos(FBU x)
    {
        return FBU(std::acos(x.val), -x.d_val / std::sqrt(1.0 - std::pow(x.val, 2.0)));
    }
    friend FBU atan(FBU x)
    {
        return FBU(std::atan(x.val), x.d_val / (1.0 + std::pow(x.val, 2.0)));
    }
    friend FBU sinh(FBU x)
    {
        return FBU(std::sinh(x.val), std::cosh(x.val) * x.d_val);
    }
    friend FBU cosh(FBU x)
    {
        return FBU(std::cosh(x.val), std::sinh(x.val) * x.d_val);
    }
    friend FBU tanh(FBU x)
    {
        return FBU(std::tanh(x.val), (1.0 - std::tanh(x.val)) * x.d_val);
    }
    // coutに出力するフォーマットの定義
    friend std::ostream& operator<<(std::ostream &s, FBU x) {
        return s << "BU_double("<< x.val << ", " << x.d_val << ") ";
    }

};