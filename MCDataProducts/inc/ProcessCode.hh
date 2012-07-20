#ifndef MCDataProducts_ProcessCode_hh
#define MCDataProducts_ProcessCode_hh
//
// An enum-matched-to-names class used to indicate why a SimParticle was
// created and why it stopped. The class contains enum entries for all
// physics processes known in G4; it also contains an enum entry to indicate
// that the particle is a primary particle and other enum entries to
// indicate that a particle was killed in one of the user actions written by G4.
//
// $Id: ProcessCode.hh,v 1.7 2012/07/20 16:47:19 genser Exp $
// $Author: genser $
// $Date: 2012/07/20 16:47:19 $
//
// Original author Rob Kutschke
//
// Notes:
// 0) The names starting with mu2e represent actions taken by SteppingAction.
//    The other codes are the names of G4 processes.
//
// 1) The enum_type is in the class.  There are other classes
//    that follow this model and lastEnum must be specific to each.
//
// 2) I do want both the name() operator and the << operator.
//    If only <<, then users will need to make temp ostringsteams
//    if they want to do their own formatting.
//
// 3) There are some notes on alternate implementations in
//    MCDataProducts/inc/GenId.hh
//
// 4) Root stores enum types as 32 bit ints.

#include <iostream>
#include <string>
#include <vector>

namespace mu2e {

  class ProcessCode {

  public:

    // Need to keep the enum and the _name member in sync.
    // Add new elements just before lastEnum; do not insert new elements
    // prior to this - it will break backwards compatibility.
    enum enum_type {
      unknown,                AlphaInelastic,          annihil,             AntiLambdaInelastic,
      AntiNeutronInelastic,   AntiOmegaMinusInelastic, AntiProtonInelastic, AntiSigmaMinusInelastic,
      AntiSigmaPlusInelastic, AntiXiMinusInelastic,    AntiXiZeroInelastic, CHIPSNuclearCaptureAtRest,
      compt,                  conv,                    Decay,               DeuteronInelastic,
      eBrem,                  eIoni,                   ElectroNuclear,      hBrems,
      hElastic,               hIoni,                   hPairProd,           ionIoni,
      KaonMinusInelastic,     KaonPlusInelastic,       KaonZeroLInelastic,  KaonZeroSInelastic,
      LambdaInelastic,        msc,                     muBrems,             muIoni,
      muMinusCaptureAtRest,   muMsc,                   muPairProd,          nCapture,
      NeutronInelastic,       nFission,                nKiller,             OmegaMinusInelastic,
      phot,                   PhotonInelastic,         PionMinusInelastic,  PionPlusInelastic,
      PositronNuclear,        ProtonInelastic,         SigmaMinusInelastic, SigmaPlusInelastic,
      StepLimiter,            Transportation,          TritonInelastic,     XiMinusInelastic,
      XiZeroInelastic,        mu2eLowEKine,            mu2eKillerVolume,    mu2eMaxSteps,
      mu2ePrimary,            muMinusConversionAtRest, hadElastic,          CoulombScat,
      nuclearStopping,        mu2eMaxGlobalTime,       TNuclearCapture,     muMinusAtomicCapture,
      MuAtomDecay,            Rayl,
      lastEnum,
      
      // An alias for backward compatibility
      mu2eHallAir = mu2eKillerVolume
    };

    // Keep this list of names in sync with the enum. Used in ProcessCode.cc
    // lastEnum does not appear in this list of names.
#define PROCESSCODE_NAMES                                                                                   \
    "unknown",                "AlphaInelastic",          "annihil",             "AntiLambdaInelastic",       \
    "AntiNeutronInelastic",   "AntiOmegaMinusInelastic", "AntiProtonInelastic", "AntiSigmaMinusInelastic",   \
    "AntiSigmaPlusInelastic", "AntiXiMinusInelastic",    "AntiXiZeroInelastic", "CHIPSNuclearCaptureAtRest", \
    "compt",                  "conv",                    "Decay",               "DeuteronInelastic",         \
    "eBrem",                  "eIoni",                   "ElectroNuclear",      "hBrems",                    \
    "hElastic",               "hIoni",                   "hPairProd",           "ionIoni",                   \
    "KaonMinusInelastic",     "KaonPlusInelastic",       "KaonZeroLInelastic",  "KaonZeroSInelastic",        \
    "LambdaInelastic",        "msc",                     "muBrems",             "muIoni",                    \
    "muMinusCaptureAtRest",   "muMsc",                   "muPairProd",          "nCapture",                  \
    "NeutronInelastic",       "nFission",                "nKiller",             "OmegaMinusInelastic",       \
    "phot",                   "PhotonInelastic",         "PionMinusInelastic",  "PionPlusInelastic",         \
    "PositronNuclear",        "ProtonInelastic",         "SigmaMinusInelastic", "SigmaPlusInelastic",        \
    "StepLimiter",            "Transportation",          "TritonInelastic",     "XiMinusInelastic",          \
    "XiZeroInelastic",        "mu2eLowEKine",            "mu2eKillerVolume",    "mu2eMaxSteps",              \
    "mu2ePrimary",            "muMinusConversionAtRest", "hadElastic",          "CoulombScat",               \
    "nuclearStopping",        "mu2eMaxGlobalTime",       "TNuclearCapture",     "muMinusAtomicCapture",      \
    "MuAtomDecay",            "Rayl"

  public:

    // The most important c'tor and accessor methods are first.
    ProcessCode( enum_type id):
      _id(id)
    {}

    // Constructor from an int; should not be needed often.  This checks for validity and throws.
    explicit ProcessCode( int id);

    // ROOT requires a default c'tor.
    ProcessCode():
      _id(unknown){
    }

    // Accept compiler supplied d'tor, copy c'tor and assignment operator.

    enum_type id() const { return _id;}

    // Return the name that corresponds to this enum.
    std::string name() const {
      return std::string( _name[_id] );
    }

    // Return the process code that corresponds to this name.
    // Return ProcessCode(unknown) if there is no such string.
    static ProcessCode findByName ( std::string const& name);

    // This operator implements:
    //   ProcessCode a;
    //   enum_type b;
    // a = b;
    ProcessCode& operator=(ProcessCode::enum_type const& c){
      _id = c;
      return *this;
    }

    // This operator implements:
    //   ProcessCode a;
    //   enum_type b = a;
    operator ProcessCode::enum_type ()const{
      return _id;
    }

    // Tests for equality.
    bool operator==(const ProcessCode g) const{
      return ( _id == g._id );
    }

    bool operator==(const ProcessCode::enum_type g) const{
      return ( _id == g );
    }

    // Accessor for the version.
    static int version() { return _version; }

    // Static version of the name method.
    static const std::string name( enum_type id ){
      return std::string( _name[id] );
    }

    // Check validity of an Id. Unknown is defined to be valid.
    static bool isValid( enum_type id){
      if ( id <  unknown  ) return false;
      if ( id >= lastEnum ) return false;
      return true;
    }

    // Number of valid codes, not including lastEnum, but including "unknown".
    static size_t size(){
      return lastEnum;
    }

    // Print all valid codes and their text strings.
    static void printAll( std::ostream& ost = std::cout);

    // Return a list of codes that are mu2e specific.
    static std::vector<ProcessCode> mu2eCodes();

    // Member function version of static functions.
    bool isValid() const{
      return isValid(_id);
    }

    // List of names corresponding to the enum.
    const static char* _name[];

  private:

    // The one and only per-instance member datum.
    enum_type _id;

    // Can this make sense?  What happens if I read in two different
    // files that have different versions?  Should I use cvs version instead?
    // This is really an edm question not a question for the class itself.
    static const unsigned _version = 1000;

  };

  // Shift left (printing) operator.
  inline std::ostream& operator<<(std::ostream& ost,
                                  const ProcessCode& id ){
    ost << "( "
        << id.id() << ": "
        << id.name()
        << " )";
    return ost;
  }

}

#endif /* MCDataProducts_ProcessCode_hh */
