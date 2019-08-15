#ifndef RecoDataProducts_CosmicTrackSeed_hh
#define RecoDataProducts_CosmicTrackSeed_hh
//
// S. Middleton - seed class for striaght track fit
//

// Mu2e includes
#include "BTrk/TrkBase/TrkT0.hh"
#include "TrackerGeom/inc/Tracker.hh"
#include "RecoDataProducts/inc/ComboHit.hh"
#include "RecoDataProducts/inc/TrkStrawHitSeed.hh"
#include "RecoDataProducts/inc/CosmicTrack.hh"
#include "RecoDataProducts/inc/TimeCluster.hh"
#include "RecoDataProducts/inc/TrkFitFlag.hh"
#include "canvas/Persistency/Common/Ptr.h"
#include <vector>

namespace mu2e {
  
  class TimeCluster;

  struct CosmicTrackSeed {

    TrkT0 const& t0() const { return _t0; }//from the Time cluster
    const std::vector<StrawHitIndex>& _shits       () const { return _strawHitIdxs; }
    
    std::vector<TrkStrawHitSeed> const& trkstrawhits() const { return _trkstrawhits;}
    ComboHitCollection const& hits() const { return _thits; }
    CosmicTrack const& track() const { return _track; }
    TrkFitFlag const& status() const { return _status; }
    art::Ptr<TimeCluster> const& timeCluster() const { return _timeCluster; }
    
    TrkT0	             _t0;	      // t0 for this track
    ComboHitCollection       _thits;	      // hits for track
    CosmicTrack              _track;	     // Cosmic track created from these hits
   
    TrkFitFlag	             _status;      // status of processes used to create this seed
    art::Ptr<TimeCluster>    _timeCluster; // associated time cluster
    std::vector<StrawHitIndex> _strawHitIdxs; // associated straw hits: can be empty
    std::vector<TrkStrawHitSeed>  _trkstrawhits; //vector of associated trkstrawhits
    std::vector<Straw> _straws; //vector of straw info 
    std::vector<Panel> _panels; //vector of panel info 
    std::vector<Plane> _planes; //vector of plane info 
    std::vector<Station> _stations; //vector of station info 
  };
   typedef std::vector<mu2e::CosmicTrackSeed> CosmicTrackSeedCollection;
} // namespace mu2e

#endif /* RecoDataProducts_CosmicTrackSeed_hh */
