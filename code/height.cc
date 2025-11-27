// 2025 Copyright Huseyin Berat Kamer
// implementations of the member functions for the Height class
#include "height.h"
#include <string>
using std::string;
#include <iostream>
using std::ostream;

// unit conversion constants
const double kInchToCm = 2.54;
const double kInchesPerFoot = 12.0;
const double kCmPerMeter = 100.0;

Height::Height(double value, const string& units) : value_(0.0), units_("feet") {

  if (value >= 0.0) {
    if (IsValidUnits(units)) {
      value_ = value;
      units_ = units;
    } else {
      value_ = value;    // bad units ---->>> keep value
      units_ = "feet";   // default units
    }
  }
}

bool Height::SetValue(double value) {
  if (value < 0.0) return false;
  value_ = value;
  return true;
}

double Height::GetValue() const { return value_; }

bool Height::SetUnits(const string& u) {
  if (!IsValidUnits(u)) return false;
  units_ = u;
  return true;
}

string Height::GetUnits() const { return units_; }

void Height::ConvertUnits(const string& target_units) {
  if (!IsValidUnits(target_units) || target_units == units_) return;
  double meters = ToMeters(value_, units_);
  value_ = FromMeters(meters, target_units);
  units_ = target_units;
}

ostream& operator<<(ostream& os, const Height& h) {
  os << h.value_ << ' ' << h.units_;
  return os;
}

// helpers
bool Height::IsValidUnits(const string& u) {
  return (u == "inches") || (u == "feet") || (u == "centimeters") || (u == "meters");
}

double Height::ToMeters(double value, const string& units) {
  if (units == "meters") return value;
  if (units == "centimeters") return value / kCmPerMeter;
  if (units == "feet") return (value * kInchesPerFoot * kInchToCm) / kCmPerMeter;
  if (units == "inches") return (value * kInchToCm) / kCmPerMeter;
  return value;
}

double Height::FromMeters(double meters, const string& units) {
  if (units == "meters") return meters;
  if (units == "centimeters") return meters * kCmPerMeter;
  if (units == "feet") return (meters * kCmPerMeter) / (kInchesPerFoot * kInchToCm);
  if (units == "inches") return (meters * kCmPerMeter) / kInchToCm;
  return meters;
}
