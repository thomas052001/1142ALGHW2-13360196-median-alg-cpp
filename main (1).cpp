#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// 用來同時儲存數值與權重
struct Item {
    int x;
    double w;
};

// 印出排序後資料
void printSortedValues(const vector<Item>& items) {
    cout << "Sorted data (x, w):\n";
    for (const auto& item : items) {
        cout << "(" << item.x << ", " << fixed << setprecision(2) << item.w << ") ";
    }
    cout << "\n";
}

// ------------------------------
// 1. 求中位數
// ------------------------------
double findMedian(vector<int> values) {
    if (values.empty()) return 0.0; // 若無資料，回傳 0
    
    // 1. 將 values 由小到大排序
    sort(values.begin(), values.end());
    
    // 2. 取得資料筆數 n
    int n = values.size();
    
    // 3. 若 n 為奇數，回傳中間值
    // 4. 若 n 為偶數，回傳中間兩個值的平均
    if (n % 2 == 1) {
        return values[n / 2];
    } else {
        return (values[n / 2 - 1] + values[n / 2]) / 2.0;
    }
}

// ------------------------------
// 2. 求加權中位數
// 定義：排序後，找到最小的 x_k，使得
// 左側權重總和 <= 0.5，且右側權重總和 <= 0.5
// 常用實作方式：找第一個累積權重 >= 0.5 的元素
// ------------------------------
int findWeightedMedian(vector<Item> items) {
    if (items.empty()) return -1; 
    // 1. 將 items 依照 x 由小到大排序
    //    可使用 sort 搭配 lambda
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.x < b.x; // 按 x 值排序
    });
    
    // 2. 呼叫 printSortedValues(items) 顯示排序結果
    printSortedValues(items);
    
    // 3. 設定 cumulativeWeight = 0.0
    double cumulativeWeight = 0.0;
    
    // 4. 逐一走訪排序後的 items：
    for (const auto& item : items) {
        
        // - 累加目前權重 item.w
        cumulativeWeight += item.w;
        
        // - 印出 x、w、cumulative
        cout << "x:" << setw(2) << item.x
            << " | w: " << fixed << setprecision(2) << item.w 
            << " | cumulative: " << cumulativeWeight << "\n";
        
        // - 若 cumulativeWeight >= 0.5，回傳 item.x
        // 浮點數精度可能會有極微小的誤差，但在這題的要求下直接使用 >= 即可
            if (cumulativeWeight >= 0.5) {
            return item.x;
        }
    }
    // 5. 若最後仍未找到，回傳 -1
    return -1; 
}

int main() {
    // 題目資料
    vector<int> x = {4, 3, 8, 5, 7, 10, 0, 9, 2, 11};
    vector<double> w = {0.05, 0.12, 0.08, 0.15, 0.14, 0.09, 0.10, 0.10, 0.06, 0.11};

    // 組合成 (x, w)
    vector<Item> items;
    for (int i = 0; i < x.size(); i++) {
        items.push_back({x[i], w[i]});
    }

    cout << "Original x values:\n";
    for (int v : x) cout << v << " ";
    cout << "\n\n";

    // 計算中位數
    double median = findMedian(x);
    cout << "Median = " << fixed << setprecision(1) << median << "\n\n";

    // 計算加權中位數
    int weightedMedian = findWeightedMedian(items);
    cout << "\nWeighted Median = " << weightedMedian << "\n";

    return 0;
}
