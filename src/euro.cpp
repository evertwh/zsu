//---------------------------------------------------------------------------

#pragma hdrstop

#include "euro.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/** Fills the specified table with EUROCurrencyISOCodes mapping to
    EURORates for the 12 EURO countries */
static void initEuroRatesTable(map<string, double> & table)
{
  const int EUROCurrencies = 12;
  const double EURORates[] = {
    13.7603, // ATS
    40.3399, // BEF
    1.95583, // DEM
    166.386, // ESP
    5.94573, // FIM
    6.55957, // FRF
    340.750, // GRD
    0.787564, // IEP
    1936.27, // ITL
    40.3399, // LUF
    2.20371, // NLG
    200.482  // PTE
  };
  const string EUROCurrencyISOCode[] = {
    "ATS", // Austria schilling
    "BEF", // Belgium franc
    "DEM", // Germany mark
    "ESP", // Spain peseta
    "FIM", // Finland markka
    "FRF", // France franc
    "GRD", // Greece drachma
    "IEP", // Ireland pound
    "ITL", // Italy lira
    "LUF", // Luxembourg franc
    "NLG", // Netherlands guilder
    "PTE"  // Portugal escudo
  };

  for(int i = 0; i < EUROCurrencies; i++)
    table.insert(
      pair<string, double>
        (zsu::toLower(EUROCurrencyISOCode[i]), EURORates[i]));
}

//---------------------------------------------------------------------------
/** Lookup an currency exchange rate. If the currency can't be
    found, it returns the rate 1.0.
    @param code the EURO currency ISO code
static double getEuroRate(const string& code)
{
  static map<string, double> table;
  static bool init = true;

  if (init)
  {
    // do it only once...
    initEuroRatesTable(table);
    init = false;
  }

  map<string, double>::const_iterator it = table.find(zsu::toLower(code));

  return it != table.end() ? it->second : zsu::nan();
}                */
