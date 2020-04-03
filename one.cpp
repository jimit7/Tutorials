#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for (int i = 0; i < m; ++i) cin >> jobs_[i];
  }

  void heapify(vector<pair<int, long long>> &heap, int k) {
    int smallest = k;
    int left = (2 * k) + 1;
    int right = (2 * k) + 2;

    if (left < heap.size()) {
      if (heap[left].second < heap[smallest].second)
        smallest = left;
      else if (heap[left].second == heap[smallest].second) {
        if (heap[left].first < heap[smallest].first) smallest = left;
      }
    }

    if (right < heap.size()) {
      if (heap[right].second < heap[smallest].second)
        smallest = right;
      else if (heap[right].second == heap[smallest].second) {
        if (heap[left].first < heap[smallest].first) smallest = right;
      }
    }

    if (left < heap.size() && right < heap.size() &&
        heap[left].second == heap[right].second) {
      if (heap[left].first < heap[right].first)
        smallest = left;
      else
        smallest = right;
    }

    if (smallest != k) {
      swap(heap[k], heap[smallest]);
      heapify(heap, smallest);
    }
  }

  void changePriority(vector<pair<int, long long>> &heap, int incr) {
    heap[0].second += incr;
    heapify(heap, 0);
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<pair<int, long long>> next_free_time(num_workers_);

    for (int i = 0; i < num_workers_; i++) {
      next_free_time[i].first = i;
      next_free_time[i].second = 0;
    }
    for (int i = 0; i < jobs_.size(); ++i) {
      pair<int, long long> next_worker = next_free_time[0];
      assigned_workers_[i] = next_worker.first;
      start_times_[i] = next_worker.second;
      changePriority(next_free_time, jobs_[i]);
    }

  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
