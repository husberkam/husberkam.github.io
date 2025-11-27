// Copyright 2025 Huseyin Berat Kamer
// Header for height class, classes with members and mutator methods
#ifndef CSCE240_HEIGHT_H_
#define CSCE240_HEIGHT_H_

#include <string>
#include <iostream>
using std::string;
using std::ostream;

class Height {
 public:
  Height(double value = 0.0, const string& units = "feet");

  bool SetValue(double value);     // false if value < 0
  double GetValue() const;
  bool SetUnits(const string& u);  // false if invalid
  string GetUnits() const;

  void ConvertUnits(const string& target_units);  // no op if invalid

  friend ostream& operator<<(ostream& os, const Height& h);

 private:
  double value_;
  string units_;

  static bool IsValidUnits(const string& u);
  static double ToMeters(double value, const string& units);
  static double FromMeters(double meters, const string& units);
};

#endif  // CSCE240_HEIGHT_H_

