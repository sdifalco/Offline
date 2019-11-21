#include "CRVResponse/inc/CrvHelper.hh"

namespace mu2e 
{
  void CrvHelper::GetStepPointsFromCrvRecoPulse(const art::Ptr<CrvRecoPulse> &crvRecoPulse,
                                                const art::Handle<CrvDigiMCCollection> &digis,
                                                std::set<art::Ptr<StepPointMC> > &steps)
  {
    if(!digis.isValid()) return;

    const std::vector<size_t> &waveformIndices = crvRecoPulse->GetWaveformIndices();
    for(size_t i=0; i<waveformIndices.size(); i++) 
    {
      size_t waveformIndex = waveformIndices[i];
      const CrvDigiMC &digi = digis->at(waveformIndex);
      const std::vector<art::Ptr<StepPointMC> > &stepPoints = digi.GetStepPoints();
      for(size_t j=0; j<stepPoints.size(); j++)
      {
        if(stepPoints[j].isNonnull()) steps.insert(stepPoints[j]);
      }
    }
  }

  void CrvHelper::GetInfoFromStepPoints(const std::set<art::Ptr<StepPointMC> > &steps, 
                                        const SimParticleTimeOffset &timeOffsets,
                                        double &energyDeposited, double &earliestHitTime,
                                        CLHEP::Hep3Vector &earliestHitPos,
                                        art::Ptr<SimParticle> &mostLikelySimParticle)
  {
    energyDeposited=0;
    std::map<art::Ptr<SimParticle>,double> simParticleMap;
    std::set<art::Ptr<StepPointMC> >::const_iterator stepPointIter;
    for(stepPointIter=steps.begin(); stepPointIter!=steps.end(); stepPointIter++)
    {
      const StepPointMC &step = **stepPointIter;
      energyDeposited+=step.totalEDep();
      simParticleMap[step.simParticle()]+=step.totalEDep();
    }

    std::map<art::Ptr<SimParticle>,double>::const_iterator simParticleIter;
    double simParticleDepEnergy=0;
    for(simParticleIter=simParticleMap.begin(); simParticleIter!=simParticleMap.end(); simParticleIter++)
    {
      if(simParticleIter->second>simParticleDepEnergy)
      {
        simParticleDepEnergy=simParticleIter->second;
        mostLikelySimParticle=simParticleIter->first;
      }
    }

    //TODO: Is this still necessary? Removing it for now.
    //time folding is not applied here, but was used to create the digis, ...
    //so we need to avoid that some step points from a different micro bunch 
    //could be accidentally found to be the step point with the earliest hit time.
    //therefore, only step points of the most likely sim particle will be considered.
    earliestHitTime=NAN;
    for(stepPointIter=steps.begin(); stepPointIter!=steps.end(); stepPointIter++)
    {
      const StepPointMC &step = **stepPointIter;
      double t = timeOffsets.timeWithOffsetsApplied(step);
      if(isnan(earliestHitTime) || earliestHitTime>t)
      {
        earliestHitTime=t;
        earliestHitPos=step.position();
      }
    }
  }

  void CrvHelper::GetInfoFromCrvRecoPulse(const art::Ptr<CrvRecoPulse> &crvRecoPulse, 
                                          const art::Handle<CrvDigiMCCollection> &digis,
                                          const SimParticleTimeOffset &timeOffsets,
                                          double &energyDeposited, double &earliestHitTime,
                                          CLHEP::Hep3Vector &earliestHitPos,
                                          art::Ptr<SimParticle> &mostLikelySimParticle)
  {
    std::set<art::Ptr<StepPointMC> > steps;

    CrvHelper::GetStepPointsFromCrvRecoPulse(crvRecoPulse, digis, steps);
    CrvHelper::GetInfoFromStepPoints(steps, timeOffsets, energyDeposited, 
                                     earliestHitTime, earliestHitPos, mostLikelySimParticle);
  }

} // end namespace mu2e

