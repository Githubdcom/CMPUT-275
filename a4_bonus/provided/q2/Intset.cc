#include "intSet.h"

// ---- helpers (file-local) ----
static void sortInts(int *a, int n) {
  // insertion sort (no extra headers)
  for (int i = 1; i < n; ++i) {
    int key = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = key;
  }
}

static int findIndex(const int *a, int n, int e) {
  for (int i = 0; i < n; ++i) {
    if (a[i] == e) return i;
  }
  return -1;
}

// ---- intSet implementation ----
intSet::intSet() : data(new int[4]), size(0), capacity(4) {}

intSet::intSet(const intSet& is)
  : data(new int[is.capacity]), size(is.size), capacity(is.capacity) {
  for (int i = 0; i < size; ++i) data[i] = is.data[i];
}

intSet::intSet(intSet&& is) : data(is.data), size(is.size), capacity(is.capacity) {
  is.data = nullptr;
  is.size = 0;
  is.capacity = 0;
}

intSet& intSet::operator=(const intSet& is) {
  if (this == &is) return *this;

  int *newData = new int[is.capacity];
  for (int i = 0; i < is.size; ++i) newData[i] = is.data[i];

  delete[] data;
  data = newData;
  size = is.size;
  capacity = is.capacity;
  return *this;
}

intSet& intSet::operator=(intSet&& is) {
  if (this == &is) return *this;

  delete[] data;
  data = is.data;
  size = is.size;
  capacity = is.capacity;

  is.data = nullptr;
  is.size = 0;
  is.capacity = 0;
  return *this;
}

intSet::~intSet() {
  delete[] data;
}

bool intSet::contains(int e) const {
  return findIndex(data, size, e) != -1;
}

void intSet::add(int e) {
  if (contains(e)) return;

  if (size == capacity) {
    int newCap = (capacity == 0 ? 4 : capacity * 2);
    int *newData = new int[newCap];
    for (int i = 0; i < size; ++i) newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
  }

  data[size] = e;
  ++size;
}

void intSet::remove(int e) {
  int idx = findIndex(data, size, e);
  if (idx == -1) return;

  // keep array compact: swap-with-last
  data[idx] = data[size - 1];
  --size;
}

bool intSet::isSubset(const intSet &s) const {
  // True if s is subset of *this
  for (int i = 0; i < s.size; ++i) {
    if (!contains(s.data[i])) return false;
  }
  return true;
}

bool intSet::operator==(const intSet &other) const {
  if (size != other.size) return false;
  // if every element of *this is in other, sizes equal => sets equal
  for (int i = 0; i < size; ++i) {
    if (!other.contains(data[i])) return false;
  }
  return true;
}

intSet intSet::operator|(const intSet &other) const {
  intSet out;

  // optional: reduce reallocs by pre-growing once
  int needed = size + other.size;
  while (out.capacity < needed) {
    int newCap = (out.capacity == 0 ? 4 : out.capacity * 2);
    int *newData = new int[newCap];
    for (int i = 0; i < out.size; ++i) newData[i] = out.data[i];
    delete[] out.data;
    out.data = newData;
    out.capacity = newCap;
  }

  for (int i = 0; i < size; ++i) out.add(data[i]);
  for (int i = 0; i < other.size; ++i) out.add(other.data[i]);
  return out;
}

intSet intSet::operator&(const intSet &other) const {
  intSet out;
  for (int i = 0; i < size; ++i) {
    if (other.contains(data[i])) out.add(data[i]);
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const intSet& is) {
  out << '(';

  if (is.size > 0) {
    // copy + sort for ascending output without changing internal order
    int *tmp = new int[is.size];
    for (int i = 0; i < is.size; ++i) tmp[i] = is.data[i];
    sortInts(tmp, is.size);

    for (int i = 0; i < is.size; ++i) {
      if (i > 0) out << ", ";
      out << tmp[i];
    }

    delete[] tmp;
  }

  out << ')';
  return out;
}