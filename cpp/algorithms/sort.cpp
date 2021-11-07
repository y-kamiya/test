#include <iostream>
#include <sstream>
#include <vector>

void insertionSort(std::vector<int> &a) {
    int N = (int)a.size();
    for (int i = 1; i < N; ++i) {
        int v = a[i];

        int j = i;
        for (; j > 0; --j) {
            // 挿入候補位置の値が候補の値よりも小さければそれ以降の探索は必要なし
            if (a[j-1] <= v) {
                break;
            }
            // 一つ後ろへずらす
            a[j] = a[j-1];
        }

        // 挿入候補の値を挿入
        a[j] = v;
    }
}

void mergeSort(std::vector<int> &a, int left, int right) {
    int diff = right - left;
    if (diff == 1) {
        return;
    }

    int mid = left + diff / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid, right);

    // 一時領域にコピー(leftはそのまま、rightはreverseの状態で)
    std::vector<int> buf;
    for (int i = left; i < mid; ++i) {
        buf.push_back(a[i]);
    }
    for (int i = right - 1; i >= mid; --i) {
        buf.push_back(a[i]);
    }

    int index_left = 0;
    int index_right = (int)buf.size() - 1;
    for (int i = left; i < right; ++i) {
        if (buf[index_left] <= buf[index_right]) {
            a[i] = buf[index_left++];
        } else {
            a[i] = buf[index_right--];
        }
    }
}

void quickSort(std::vector<int> &a, int left, int right) {
    int diff = right - left;
    if (diff <= 1) {
        return;
    }

    int pivot_index = (left + right) / 2;
    int pivot = a[pivot_index];
    // forループを簡単にするためにpivotを右端と取り替えておく
    std::swap(a[pivot_index], a[right - 1]);

    int i = left;
    for (int j = left; j < right - 1; ++j) {
        // pivot未満の値を左に詰めていく
        if (a[j] < pivot) {
            std::swap(a[i++], a[j]);
        }
    }
    // pivotの値を適切な場所に挿入
    std::swap(a[i], a[right - 1]);

    quickSort(a, left, i);
    quickSort(a, i + 1, right);
}

// 親ノードの方が値が大きいヒープを作成
void heapify(std::vector<int> &a, int root_index, int N) {
    int child_index_left = root_index * 2 + 1;
    if (child_index_left >= N) {
        return;
    }
    int child_index_right = child_index_left + 1;

    int child_index = child_index_left;
    if (child_index_right < N && a[child_index_right] > a[child_index_left]) {
        ++child_index;
    }

    if (a[child_index] <= a[root_index]) {
        return;
    }

    std::swap(a[root_index], a[child_index]);

    heapify(a, child_index, N);
}

void heapSort(std::vector<int> &a) {
    int N = (int)a.size();

    // vectorをヒープ化
    for (int i = N / 2 - 1; i >= 0; --i) {
        heapify(a, i, N);
    }

    for (int i = N - 1; i > 0; --i) {
        // 最大の値(root node)をvectorの最後尾へ
        std::swap(a[0], a[i]);
        // 残りの要素でヒープ化
        heapify(a, 0, i);
    }
}

// すべての値が0以上MAX未満であるという条件下でソート
// O(N + A)のオーダーなため条件が合えば高速
void bucketSort(std::vector<int> &a) {
    int MAX = 100;
    int N = (int)a.size();

    // 各要素の個数をカウント
    std::vector<int> num(MAX, 0);
    for (int i = 0; i < N; ++i) {
        ++num[a[i]];
    }

    // numの累積和
    // sum[v]: v以下の値の個数
    std::vector<int> sum(MAX, 0);
    for (int v = 0; v < MAX; ++v) {
        sum[v] = sum[v - 1] + num[v];
    }

    std::vector<int> buf(N);
    for (int i = N - 1; i >= 0; --i) {
        buf[--sum[a[i]]] = a[i];
    }

    a = buf;
}

std::string toString(const std::vector<int> a) {
    std::stringstream output;
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(output, " "));
    return output.str();
}

int main() {
    int N = 7;
    std::vector<int> a = {4, 5, 2, 6, 8, 7, 10};

    std::cout << "before: " << toString(a) << std::endl;
    // insertionSort(a);
    // mergeSort(a, 0, N);
    // quickSort(a, 0, N);
    // heapSort(a);
    bucketSort(a);
    std::cout << "after : " << toString(a) << std::endl;
}
