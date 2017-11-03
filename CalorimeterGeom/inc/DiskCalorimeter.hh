#ifndef CalorimeterGeom_DiskCalorimeter_hh
#define CalorimeterGeom_DiskCalorimeter_hh
//
// Hold informations about the disk calorimeter 
//
// Original author B. Echenard
//
// Note 1: conversion of crystal <-> readout id
//         readout_id = crystal_id*nRoPerCrystal ... crystal_id*nRoPerCrystal + nRoPerCrystal-1		 

#include "CalorimeterGeom/inc/Calorimeter.hh"
#include "CalorimeterGeom/inc/CaloGeomInfo.hh"
#include "CalorimeterGeom/inc/CaloGeomUtil.hh"
#include "CalorimeterGeom/inc/Disk.hh"
#include "CalorimeterGeom/inc/Crystal.hh"

#include "CLHEP/Vector/ThreeVector.h"

#include <vector>
#include <memory>



namespace mu2e {
    

    class DiskCalorimeter: public Calorimeter {


	friend class DiskCalorimeterMaker;

	
        public:

            DiskCalorimeter();
            virtual ~DiskCalorimeter() {}


            // calo sections
	    virtual unsigned int              nDisk()     const  {return nDisks_;}
	    virtual const Disk&               disk(int i) const  {return *disks_.at(i);}

            	    
  	    // crystal / readout section
	    virtual unsigned int              nRO()          const  {return fullCrystalList_.size()*caloInfo_.nROPerCrystal();}
            virtual unsigned int              nCrystal()     const  {return fullCrystalList_.size();}
            virtual const Crystal&            crystal(int i) const  {return *fullCrystalList_.at(i);}
	            

            // calorimeter geometry information 
	    virtual const CaloInfo&           caloInfo() const  {return caloInfo_;} 
	    virtual const CaloGeomInfo&       geomInfo() const  {return geomInfo_;} 	    
	    virtual const CaloGeomUtil&       geomUtil() const  {return geomUtil_;} 
	                  CaloInfo&           caloInfo()        {return caloInfo_;} 
	                  CaloGeomInfo&       geomInfo()        {return geomInfo_;} 	    
	                  CaloGeomUtil&       geomUtil()        {return geomUtil_;} 
           


  	    // neighbors, indexing 
            virtual const std::vector<int>&  neighbors(int crystalId, bool rawMap)     const  {return fullCrystalList_.at(crystalId)->neighbors(rawMap);}	  
            virtual const std::vector<int>&  nextNeighbors(int crystalId, bool rawMap) const  {return fullCrystalList_.at(crystalId)->nextNeighbors(rawMap);} 
            virtual       std::vector<int>   neighborsByLevel(int crystalId, int level, bool rawMap) const; 
            virtual int                      crystalIdxFromPosition(const CLHEP::Hep3Vector& pos) const;
            virtual int                      nearestIdxFromPosition(const CLHEP::Hep3Vector& pos) const; 


            // get to know me!
            virtual void                     print(std::ostream &os = std::cout)          const;

            

	private:
            
            double                        deltaZ(const CLHEP::Hep3Vector& p1, const CLHEP::Hep3Vector& p2) const;
            double                        deltaPerp(int ic, const CLHEP::Hep3Vector& pos) const;
            

	    typedef std::shared_ptr<Disk> DiskPtr;
	    int                           nDisks_;
            int                           nCrates_;
            int                           nBoards_;
	    std::vector<DiskPtr>          disks_;
            
            CaloInfo                      caloInfo_;
	    CaloGeomInfo                  geomInfo_;
	    std::vector<Crystal const*>   fullCrystalList_; //non-owning crystal pointers
	    CaloGeomUtil                  geomUtil_;
     };

}    

#endif 
