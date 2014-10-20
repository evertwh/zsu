//---------------------------------------------------------------------------

#pragma hdrstop

#include "misc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
string zsu::toString(const double& value)
{
  if (zsu::isnan(value)) return VAL_NAN;
  if (value > 0 && zsu::isinf(value)) return VAL_POSINFINITY;
  if (value < 0 && zsu::isinf(value)) return VAL_NEGINFINITY;
  std::ostringstream oss;
  oss << setprecision(MAX_PRECISION) << value;
  return oss.str();
}

//---------------------------------------------------------------------------
bool zsu::fromString(const string& str, double* value)
{
  if (str == VAL_NAN)
  {
    *value = zsu::nan();
    return true;
  }
  if (str == VAL_POSINFINITY)
  {
    *value = zsu::inf();
    return true;
  }
  if (str == VAL_NEGINFINITY)
  {
    *value = -zsu::inf();
    return true;
  }
  char* beginPtr = const_cast<char*>(str.c_str());
  char* endPtr = 0;
  double tmpValue = strtod(beginPtr, &endPtr);
  // Take care with code below.
  // Extra checks necessary under GNU because: endPtr != str.begin() if str = "".
  if ((0 != endPtr) && 
      (endPtr != beginPtr) &&
      (0 != str.size()) &&
      (static_cast<int>(str.size()) == distance(beginPtr, endPtr)))
  {
    *value = tmpValue;
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------
double zsu::euroconvert(double x, string fromstr, string tostr)
{
  double rate = 1.0;
  double amount = x;

  if(fromstr == tostr) {
    return amount;
  } else if(fromstr == "EUR") {
    rate = getEuroRate(tostr);
  } else if(tostr == "EUR") {
    rate = 1.0 / getEuroRate(fromstr);
  } else {
    double fromRate = 1.0 / getEuroRate(fromstr);
    amount = x * fromRate; // how about rounding off?
    rate = getEuroRate(tostr);
  }

  if (zsu::isnan(rate)) return zsu::nan();

  return amount * rate; // how about rounding off?
}

//---------------------------------------------------------------------------
string zsu::getCurrentTime(void)
{
  // format current local time as
  // YEAR-MM-DD hh:mm:ss GMT {+/- hh:mm)
  time_t currentTime;
  time(&currentTime);
  struct tm gmtTime(*gmtime(&currentTime));
  struct tm localTime(*localtime(&currentTime));
  int diff((localTime.tm_hour*60+localTime.tm_min) -
           (gmtTime.tm_hour*60+gmtTime.tm_min));
  if (diff > 12*60) diff -= 24*60;
  if (diff < -12*60) diff += 24*60;

  char buf[100];
  if (diff == 0)
    {
      sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d GMT",
              1900+localTime.tm_year,
              1+localTime.tm_mon,
              localTime.tm_mday,
              localTime.tm_hour,
              localTime.tm_min,
              localTime.tm_sec);
    }
  else if (diff > 0)
    {
      sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d GMT +%d:%02d",
              1900+localTime.tm_year,
              1+localTime.tm_mon,
              localTime.tm_mday,
              localTime.tm_hour,
              localTime.tm_min,
              localTime.tm_sec,
              diff/60, diff%60);
    }
  else if (diff < 0)
    {
      diff = -diff;
      sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d GMT -%d:%02d",
              1900+localTime.tm_year,
              1+localTime.tm_mon,
              localTime.tm_mday,
              localTime.tm_hour,
              localTime.tm_min,
              localTime.tm_sec,
              diff/60, diff%60);
    }

  string timeString(buf);
  //code below was necessary when using standard C asctime etc.
  //timeString.erase(timeString.length()-1); // erase '\n' character at the end
  //timeString = zsu::strip(timeString); // erase any whitespace at front or end

  return timeString;
}

//---------------------------------------------------------------------------
