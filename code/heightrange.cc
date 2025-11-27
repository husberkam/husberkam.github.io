// Copyright 2025 Huseyin Berat Kamer
// implementations of the member functions for the HeightRange class
#include "heightrange.h"
#include <string>
using std::string;
#include <iostream>

// same conversion constants
const double kInchToCm_HR = 2.54;
const double kInchesPerFoot_HR = 12.0;
const double kCmPerMeter_HR = 100.0;

// helper
double ToMetersValue(double value, const string& units) {
  if (units == "meters") return value;
  if (units == "centimeters") return value / kCmPerMeter_HR;
  if (units == "feet") return (value * kInchesPerFoot_HR * kInchToCm_HR) / kCmPerMeter_HR;
  if (units == "inches") return (value * kInchToCm_HR) / kCmPerMeter_HR;
  return value;
}

HeightRange::HeightRange() : shortest_(0.0, "feet"), tallest_(0.0, "feet") {}

HeightRange::HeightRange(const Height& a, const Height& b) {
  const double am = ToMetersValue(a.GetValue(), a.GetUnits());
  const double bm = ToMetersValue(b.GetValue(), b.GetUnits());
  if (am <= bm) {
    shortest_ = a;
    tallest_  = b;
  } else {
    shortest_ = b;
    tallest_  = a;
  }
}

Height HeightRange::GetShortest() const { return shortest_; }
Height HeightRange::GetTallest() const { return tallest_; }

void HeightRange::SetShortest(const Height& h) {
  const double hm = ToMetersValue(h.GetValue(), h.GetUnits());
  const double tall_m = ToMetersValue(tallest_.GetValue(), tallest_.GetUnits());
  if (hm <= tall_m) shortest_ = h;
}

void HeightRange::SetTallest(const Height& h) {
  const double hm = ToMetersValue(h.GetValue(), h.GetUnits());
  const double short_m = ToMetersValue(shortest_.GetValue(), shortest_.GetUnits());
  if (hm >= short_m) tallest_ = h;
}

bool HeightRange::InRange(const Height& h, bool include_endpoints) const {
  const double x  = ToMetersValue(h.GetValue(), h.GetUnits());
  const double lo = ToMetersValue(shortest_.GetValue(), shortest_.GetUnits());
  const double hi = ToMetersValue(tallest_.GetValue(), tallest_.GetUnits());
  if (include_endpoints) return (lo <= x) && (x <= hi);
  return (lo < x) && (x < hi);
}

Height HeightRange::Width() const {
  const double lo = ToMetersValue(shortest_.GetValue(), shortest_.GetUnits());
  const double hi = ToMetersValue(tallest_.GetValue(), tallest_.GetUnits());
  double diff_m = hi - lo;
  if (diff_m < 0) diff_m = 0;

  Height result(diff_m, "meters");
  result.ConvertUnits(tallest_.GetUnits());
  return result;
}

