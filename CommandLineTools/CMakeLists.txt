CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT( CommandLineTools )

IF (WIN32)
ADD_DEFINITIONS(-DUSE_STATIC_CIP_LIBS)
ENDIF (WIN32)

SET(BUILD_CONVERTDICOM ON CACHE BOOL "BUILD_CONVERTDICOM")
IF(BUILD_CONVERTDICOM)
 SUBDIRS (ConvertDicom)
ENDIF(BUILD_CONVERTDICOM)

SET(BUILD_MERGEPARTICLEDATASETS ON CACHE BOOL "BUILD_MERGEPARTICLEDATASETS")
IF(BUILD_MERGEPARTICLEDATASETS)
 SUBDIRS (MergeParticleDataSets)
ENDIF(BUILD_MERGEPARTICLEDATASETS)

SET(BUILD_REMOVEPARTICLESFROMPARTICLESDATASET ON CACHE BOOL "BUILD_REMOVEPARTICLESFROMPARTICLESDATASET")
IF(BUILD_REMOVEPARTICLESFROMPARTICLESDATASET)
 SUBDIRS (RemoveParticlesFromParticlesDataSet)
ENDIF(BUILD_REMOVEPARTICLESFROMPARTICLESDATASET)

SET(BUILD_EXTRACTPARTICLESFROMCHESTREGIONCHESTTYPE ON CACHE BOOL "BUILD_EXTRACTPARTICLESFROMCHESTREGIONCHESTTYPE")
IF(BUILD_EXTRACTPARTICLESFROMCHESTREGIONCHESTTYPE)
 SUBDIRS (ExtractParticlesFromChestRegionChestType)
ENDIF(BUILD_EXTRACTPARTICLESFROMCHESTREGIONCHESTTYPE)

SET(BUILD_GENERATEOTSULUNGCAST ON CACHE BOOL "BUILD_GENERATEOTSULUNGCAST")
IF(BUILD_GENERATEOTSULUNGCAST)
 SUBDIRS (GenerateOtsuLungCast)
ENDIF(BUILD_GENERATEOTSULUNGCAST)

SET(BUILD_GENERATEATLASCONVEXHULL ON CACHE BOOL "BUILD_GENERATEATLASCONVEXHULL")
IF(BUILD_GENERATEATLASCONVEXHULL)
 SUBDIRS (GenerateAtlasConvexHull)
ENDIF(BUILD_GENERATEATLASCONVEXHULL)

SET(BUILD_REGISTERLUNGATLAS ON CACHE BOOL "BUILD_REGISTERLUNGATLAS")
IF(BUILD_REGISTERLUNGATLAS)
 SUBDIRS (RegisterLungAtlas)
ENDIF(BUILD_REGISTERLUNGATLAS)

SET(BUILD_RESAMPLELABELMAP ON CACHE BOOL "BUILD_RESAMPLELABELMAP")
IF(BUILD_RESAMPLELABELMAP)
 SUBDIRS (ResampleLabelMap)
ENDIF(BUILD_RESAMPLELABELMAP)

SET(BUILD_RESCALELABELMAP ON CACHE BOOL "BUILD_RESCALELABELMAP")
IF(BUILD_RESCALELABELMAP)
 SUBDIRS (RescaleLabelMap)
ENDIF(BUILD_RESCALELABELMAP)


SET(BUILD_RESAMPLECT ON CACHE BOOL "BUILD_RESAMPLECT")
IF(BUILD_RESAMPLECT)
 SUBDIRS (ResampleCT)
ENDIF(BUILD_RESAMPLECT)

SET(BUILD_QUALITYCONTROL ON CACHE BOOL "BUILD_QUALITYCONTROL")
IF(BUILD_QUALITYCONTROL)
 SUBDIRS (QualityControl)
ENDIF(BUILD_QUALITYCONTROL)

SET(BUILD_REMOVECHESTTYPEFROMLABELMAPUSINGPARTICLES ON CACHE BOOL "BUILD_REMOVECHESTTYPEFROMLABELMAPUSINGPARTICLES")
IF(BUILD_REMOVECHESTTYPEFROMLABELMAPUSINGPARTICLES)
 SUBDIRS (RemoveChestTypeFromLabelMapUsingParticles)
ENDIF(BUILD_REMOVECHESTTYPEFROMLABELMAPUSINGPARTICLES)

SET(BUILD_SEGMENTLUNGLOBES ON CACHE BOOL "BUILD_SEGMENTLUNGLOBES")
IF(BUILD_SEGMENTLUNGLOBES)
 SUBDIRS (SegmentLungLobes)
ENDIF(BUILD_SEGMENTLUNGLOBES)

SET(BUILD_READDICOMWRITETAGS ON CACHE BOOL "BUILD_READDICOMWRITETAGS")
IF(BUILD_READDICOMWRITETAGS)
 SUBDIRS (ReadDicomWriteTags)
ENDIF(BUILD_READDICOMWRITETAGS)

SET(BUILD_SPLITLEFTLUNGRIGHTLUNG ON CACHE BOOL "BUILD_SPLITLEFTLUNGRIGHTLUNG")
IF(BUILD_SPLITLEFTLUNGRIGHTLUNG)
 SUBDIRS (SplitLeftLungRightLung)
ENDIF(BUILD_SPLITLEFTLUNGRIGHTLUNG)

SET(BUILD_EXTRACTCHESTLABELMAP ON CACHE BOOL "BUILD_EXTRACTCHESTLABELMAP")
IF(BUILD_EXTRACTCHESTLABELMAP)
 SUBDIRS (ExtractChestLabelMap)
ENDIF(BUILD_EXTRACTCHESTLABELMAP)

SET(BUILD_LABELPARTICLESBYCHESTREGIONCHESTTYPE ON CACHE BOOL "BUILD_LABELPARTICLESBYCHESTREGIONCHESTTYPE")
IF(BUILD_LABELPARTICLESBYCHESTREGIONCHESTTYPE)
 SUBDIRS (LabelParticlesByChestRegionChestType)
ENDIF(BUILD_LABELPARTICLESBYCHESTREGIONCHESTTYPE)

SET(BUILD_GENERATESTENCILEDLABELMAPFROMPARTICLES ON CACHE BOOL "BUILD_GENERATESTENCILEDLABELMAPFROMPARTICLES")
IF(BUILD_GENERATESTENCILEDLABELMAPFROMPARTICLES)
 SUBDIRS (GenerateStenciledLabelMapFromParticles)
ENDIF(BUILD_GENERATESTENCILEDLABELMAPFROMPARTICLES)

SET(BUILD_GENERATEDISTANCEMAPFROMLABELMAP ON CACHE BOOL "BUILD_GENERATEDISTANCEMAPFROMLABELMAP")
IF(BUILD_GENERATEDISTANCEMAPFROMLABELMAP)
 SUBDIRS (GenerateDistanceMapFromLabelMap)
ENDIF(BUILD_GENERATEDISTANCEMAPFROMLABELMAP)

SET(BUILD_FILTERVESSELPARTICLEDATA ON CACHE BOOL "BUILD_FILTERVESSELPARTICLEDATA")
IF(BUILD_FILTERVESSELPARTICLEDATA)
 SUBDIRS (FilterVesselParticleData)
ENDIF(BUILD_FILTERVESSELPARTICLEDATA)

SET(BUILD_FILTERAIRWAYPARTICLEDATA ON CACHE BOOL "BUILD_FILTERAIRWAYPARTICLEDATA")
IF(BUILD_FILTERAIRWAYPARTICLEDATA)
 SUBDIRS (FilterAirwayParticleData)
ENDIF(BUILD_FILTERAIRWAYPARTICLEDATA)

SET(BUILD_SCOURPARTICLEDATA ON CACHE BOOL "BUILD_SCOURPARTICLEDATA")
IF(BUILD_SCOURPARTICLEDATA)
 SUBDIRS (ScourParticleData)
ENDIF(BUILD_SCOURPARTICLEDATA)

SET(BUILD_READNRRDSWRITEVTK ON CACHE BOOL "BUILD_READNRRDSWRITEVTK")
IF(BUILD_READNRRDSWRITEVTK)
 SUBDIRS (ReadNRRDsWriteVTK)
ENDIF(BUILD_READNRRDSWRITEVTK)

SET(BUILD_COMPUTECROSSSECTIONALAREA ON CACHE BOOL "BUILD_COMPUTECROSSSECTIONALAREA")
IF(BUILD_COMPUTECROSSSECTIONALAREA)
 SUBDIRS (ComputeCrossSectionalArea)
ENDIF(BUILD_COMPUTECROSSSECTIONALAREA)

SET(BUILD_COMPUTEINTENSITYSTATISTICS ON CACHE BOOL "BUILD_COMPUTEINTENSITYSTATISTICS")
IF(BUILD_COMPUTEINTENSITYSTATISTICS)
 SUBDIRS (ComputeIntensityStatistics)
ENDIF(BUILD_COMPUTEINTENSITYSTATISTICS)

SET(BUILD_FILTERFISSUREPARTICLEDATA ON CACHE BOOL "BUILD_FILTERFISSUREPARTICLEDATA")
IF(BUILD_FILTERFISSUREPARTICLEDATA)
 SUBDIRS (FilterFissureParticleData)
ENDIF(BUILD_FILTERFISSUREPARTICLEDATA)

SET(BUILD_GENERATELOBESURFACEMODELS ON CACHE BOOL "BUILD_GENERATELOBESURFACEMODELS")
IF(BUILD_GENERATELOBESURFACEMODELS)
 SUBDIRS (GenerateLobeSurfaceModels)
ENDIF(BUILD_GENERATELOBESURFACEMODELS)

SET(BUILD_CLASSIFYFISSUREPARTICLES ON CACHE BOOL "BUILD_CLASSIFYFISSUREPARTICLES")
IF(BUILD_CLASSIFYFISSUREPARTICLES)
 SUBDIRS (ClassifyFissureParticles)
ENDIF(BUILD_CLASSIFYFISSUREPARTICLES)

SET(BUILD_CROPLUNG ON CACHE BOOL "BUILD_CROPLUNG")
IF(BUILD_CROPLUNG)
  SUBDIRS (CropLung)
ENDIF(BUILD_CROPLUNG)

SET(BUILD_GENERATEMODEL ON CACHE BOOL "BUILD_GENERATEMODEL")
IF(BUILD_GENERATEMODEL)
  SUBDIRS (GenerateModel)
ENDIF(BUILD_GENERATEMODEL)

SET(BUILD_GENERATEIMAGESUBVOLUMES ON CACHE BOOL "BUILD_GENERATEIMAGESUBVOLUMES")
IF(BUILD_GENERATEIMAGESUBVOLUMES)
  SUBDIRS (GenerateImageSubVolumes)
ENDIF(BUILD_GENERATEIMAGESUBVOLUMES)

SET(BUILD_GENERATEMEDIANFILTEREDIMAGE ON CACHE BOOL "BUILD_GENERATEMEDIANFILTEREDIMAGE")
IF(BUILD_GENERATEMEDIANFILTEREDIMAGE)
  SUBDIRS (GenerateMedianFilteredImage)
ENDIF(BUILD_GENERATEMEDIANFILTEREDIMAGE)

IF (VTK_USE_BOOST)

ENDIF(VTK_USE_BOOST)

SET(BUILD_EVALUATELUNGLOBESEGMENTATIONRESULTS ON CACHE BOOL "BUILD_EVALUATELUNGLOBESEGMENTATIONRESULTS")
IF(BUILD_EVALUATELUNGLOBESEGMENTATIONRESULTS)
  SUBDIRS (EvaluateLungLobeSegmentationResults)
ENDIF(BUILD_EVALUATELUNGLOBESEGMENTATIONRESULTS)

SET(BUILD_CONVERTLABELMAPVALUETOCHESTREGIONCHESTTYPE ON CACHE BOOL "BUILD_CONVERTLABELMAPVALUETOCHESTREGIONCHESTTYPE")
IF(BUILD_CONVERTLABELMAPVALUETOCHESTREGIONCHESTTYPE)
  SUBDIRS (ConvertLabelMapValueToChestRegionChestType)
ENDIF(BUILD_CONVERTLABELMAPVALUETOCHESTREGIONCHESTTYPE)

SET(BUILD_GENERATEREGIONHISTOGRAMANDPARENCHYMAPHENOTYPES ON CACHE BOOL "BUILD_GENERATEREGIONHISTOGRAMANDPARENCHYMAPHENOTYPES")
IF(BUILD_GENERATEREGIONHISTOGRAMANDPARENCHYMAPHENOTYPES)
  SUBDIRS (GenerateRegionHistogramsAndParenchymaPhenotypes)
ENDIF(BUILD_GENERATEREGIONHISTOGRAMANDPARENCHYMAPHENOTYPES)

SET(BUILD_COMPUTEDISTANCEMAP ON CACHE BOOL "BUILD_COMPUTEDISTANCEMAP")
IF(BUILD_COMPUTEDISTANCEMAP)
  SUBDIRS (ComputeDistanceMap)
ENDIF(BUILD_COMPUTEDISTANCEMAP)

SET(BUILD_TRANSFERFIELDDATATOFROMPOINTDATA ON CACHE BOOL "BUILD_TRANSFERFIELDDATATOFROMPOINTDATA")
IF(BUILD_TRANSFERFIELDDATATOFROMPOINTDATA)
  SUBDIRS (TransferFieldDataToFromPointData)
ENDIF(BUILD_TRANSFERFIELDDATATOFROMPOINTDATA)

SET(BUILD_PERTURBPARTICLES ON CACHE BOOL "BUILD_PERTURBPARTICLES")
IF(BUILD_PERTURBPARTICLES)
  SUBDIRS (PerturbParticles)
ENDIF(BUILD_PERTURBPARTICLES)

SET(BUILD_READWRITEREGIONANDTYPEPOINTS ON CACHE BOOL "BUILD_READWRITEREGIONANDTYPEPOINTS")
IF(BUILD_READWRITEREGIONANDTYPEPOINTS)
  SUBDIRS (ReadWriteRegionAndTypePoints)
ENDIF(BUILD_READWRITEREGIONANDTYPEPOINTS)

SET(BUILD_PERFORMMORPHOGICAL ON CACHE BOOL "BUILD_PERFORMMORPHOGICAL")
IF(BUILD_PERFORMMORPHOGICAL)
  SUBDIRS (PerformMorphological)
ENDIF(BUILD_PERFORMMORPHOGICAL)

SET(BUILD_GENERATEOVERLAYIMAGES ON CACHE BOOL "BUILD_GENERATEOVERLAYIMAGES")
IF(BUILD_GENERATEOVERLAYIMAGES)
  SUBDIRS (GenerateOverlayImages)
ENDIF(BUILD_GENERATEOVERLAYIMAGES)

SET(BUILD_GETTRANSFORMATIONSIMILARITYMETRIC ON CACHE BOOL "BUILD_GETTRANSFORMATIONSIMILARITYMETRIC")
IF(BUILD_GETTRANSFORMATIONSIMILARITYMETRIC)
  SUBDIRS (GetTransformationSimilarityMetric)
ENDIF(BUILD_GETTRANSFORMATIONSIMILARITYMETRIC)

SET(BUILD_GETTRANSFORMATIONKAPPA2D ON CACHE BOOL "BUILD_GETTRANSFORMATIONKAPPA2D")
IF(BUILD_GETTRANSFORMATIONKAPPA2D)
  SUBDIRS (GetTransformationKappa2D)
ENDIF(BUILD_GETTRANSFORMATIONKAPPA2D)

SET(BUILD_GETTRANSFORMATIONKAPPA ON CACHE BOOL "BUILD_GETTRANSFORMATIONKAPPA")
IF(BUILD_GETTRANSFORMATIONKAPPA)
  SUBDIRS (GetTransformationKappa)
ENDIF(BUILD_GETTRANSFORMATIONKAPPA)

IF (CIP_USE_BOOST)
  SET(BUILD_READPARTICLESWRITECONNECTEDPARTICLES ON CACHE BOOL   "BUILD_READPARTICLESWRITECONNECTEDPARTICLES")
  IF(BUILD_READPARTICLESWRITECONNECTEDPARTICLES)
    SUBDIRS (ReadParticlesWriteConnectedParticles)
  ENDIF(BUILD_READPARTICLESWRITECONNECTEDPARTICLES)

  SET(BUILD_LABELAIRWAYPARTICLESBYGENERATION ON CACHE BOOL "BUILD_LABELAIRWAYPARTICLESBYGENERATION")
  IF(BUILD_LABELAIRWAYPARTICLESBYGENERATION)
    SUBDIRS (LabelAirwayParticlesByGeneration)
  ENDIF(BUILD_LABELAIRWAYPARTICLESBYGENERATION)

  SET(BUILD_GENERATESTATISTICSFORAIRWAYGENERATIONLABELING ON CACHE BOOL "BUILD_GENERATESTATISTICSFORAIRWAYGENERATIONLABELING")
  IF(BUILD_GENERATESTATISTICSFORAIRWAYGENERATIONLABELING)
      SUBDIRS (GenerateStatisticsForAirwayGenerationLabeling)
  ENDIF(BUILD_GENERATESTATISTICSFORAIRWAYGENERATIONLABELING)
ENDIF (CIP_USE_BOOST)

SET(BUILD_READWRITEIMAGEDATA ON CACHE BOOL "BUILD_READWRITEIMAGEDATA")
IF(BUILD_READWRITEIMAGEDATA)
  SUBDIRS (ReadWriteImageData)
ENDIF(BUILD_READWRITEIMAGEDATA)

SET(BUILD_GETSTRUCTURESINLABELMAP ON CACHE BOOL "BUILD_GETSTRUCTURESINLABELMAP")
IF(BUILD_GETSTRUCTURESINLABELMAP)
  SUBDIRS (GetStructuresInLabelMap)
ENDIF(BUILD_GETSTRUCTURESINLABELMAP)

SET(BUILD_GENERATEPARTIALLUNGLABELMAP ON CACHE BOOL "BUILD_GENERATEPARTIALLUNGLABELMAP")
IF(BUILD_GENERATEPARTIALLUNGLABELMAP)
  SUBDIRS (GeneratePartialLungLabelMap)
ENDIF(BUILD_GENERATEPARTIALLUNGLABELMAP)

SET(BUILD_READVIDAWRITECIP ON CACHE BOOL "BUILD_READVIDAWRITECIP")
IF(BUILD_READVIDAWRITECIP)
  SUBDIRS (ReadVidaWriteCIP)
ENDIF(BUILD_READVIDAWRITECIP)

SET(BUILD_REGISTERLABELMAPS ON CACHE BOOL "BUILD_REGISTERLABELMAPS")
IF(BUILD_REGISTERLABELMAPS)
  SUBDIRS (RegisterLabelMaps)
ENDIF(BUILD_REGISTERLABELMAPS)

SET(BUILD_REGISTERCT ON CACHE BOOL "BUILD_REGISTERCT")
IF(BUILD_REGISTERCT)
  SUBDIRS (RegisterCT)
ENDIF(BUILD_REGISTERCT)

SET(BUILD_MERGECHESTLABELMAPS ON CACHE BOOL "BUILD_MERGECHESTLABELMAPS")
IF(BUILD_MERGECHESTLABELMAPS)
  SUBDIRS (MergeChestLabelMaps)
ENDIF(BUILD_MERGECHESTLABELMAPS)

SET(BUILD_MASKOUTLABELMAPSTRUCTURES ON CACHE BOOL "BUILD_MASKOUTLABELMAPSTRUCTURES")
IF(BUILD_MASKOUTLABELMAPSTRUCTURES)
  SUBDIRS (MaskOutLabelMapStructures)
ENDIF(BUILD_MASKOUTLABELMAPSTRUCTURES)

SET(BUILD_COMPUTEFEATURESTRENGTH ON CACHE BOOL "BUILD_COMPUTEFEATURESTRENGTH")
IF(BUILD_COMPUTEFEATURESTRENGTH)
  SUBDIRS (ComputeFeatureStrength)
ENDIF(BUILD_COMPUTEFEATURESTRENGTH)

SET(BUILD_LABELMAPFROMREGIONANDTYPEPOINTS ON CACHE BOOL "BUILD_LABELMAPFROMREGIONANDTYPEPOINTS")
IF(BUILD_LABELMAPFROMREGIONANDTYPEPOINTS)
  SUBDIRS (LabelMapFromRegionAndTypePoints)
ENDIF(BUILD_LABELMAPFROMREGIONANDTYPEPOINTS)

SET(BUILD_GENERATESIMPLELUNGMASK ON CACHE BOOL 
"BUILD_GENERATESIMPLELUNGMASK")
IF(BUILD_GENERATESIMPLELUNGMASK)
  SUBDIRS (GenerateSimpleLungMask)
ENDIF(BUILD_GENERATESIMPLELUNGMASK)

SET(BUILD_GENERATEBINARYTHINNING3D ON CACHE BOOL 
"BUILD_GENERATEBINARYTHINNING3D")
IF(BUILD_GENERATEBINARYTHINNING3D)
  SUBDIRS (GenerateBinaryThinning3D)
ENDIF(BUILD_GENERATEBINARYTHINNING3D)

SET(BUILD_CONVERTCHESTREGIONCHESTTYPETOLABELMAPVALUE ON CACHE BOOL
"BUILD_CONVERTCHESTREGIONCHESTTYPETOLABELAMPVALUE")
IF(BUILD_CONVERTCHESTREGIONCHESTTYPETOLABELMAPVALUE)
  SUBDIRS(ConvertChestRegionChestTypeToLabelMapValue)
ENDIF(BUILD_CONVERTCHESTREGIONCHESTTYPETOLABELMAPVALUE)

SET(BUILD_FILTERCONNECTEDCOMPONENTS ON CACHE BOOL
"BUILD_FILTERCONNECTEDCOMPONENTS")
IF(BUILD_FILTERCONNECTEDCOMPONENTS)
  SUBDIRS(FilterConnectedComponents)
ENDIF(BUILD_FILTERCONNECTEDCOMPONENTS)

SET(BUILD_ENHANCEFISSURESINIMAGE ON CACHE BOOL
"BUILD_ENHANCEFISSURESINIMAGE")
IF(BUILD_ENHANCEFISSURESINIMAGE)
  SUBDIRS(EnhanceFissuresInImage)
ENDIF(BUILD_ENHANCEFISSURESINIMAGE)

SET(BUILD_COMPUTEFISSUREFEATUREVECTORS ON CACHE BOOL
"BUILD_COMPUTEFISSUREFEATUREVECTORS")
IF(BUILD_COMPUTEFISSUREFEATUREVECTORS)
  SUBDIRS(ComputeFissureFeatureVectors)
ENDIF(BUILD_COMPUTEFISSUREFEATUREVECTORS)

SET(BUILD_FITLOBESURFACEMODELSTOPARTICLEDATA ON CACHE BOOL
"BUILD_FITLOBESURFACEMODELSTOPARTICLEDATA")
IF(BUILD_FITLOBESURFACEMODELSTOPARTICLEDATA)
  SUBDIRS(FitLobeSurfaceModelsToParticleData)
ENDIF(BUILD_FITLOBESURFACEMODELSTOPARTICLEDATA)

SET(BUILD_GENERATELESIONSEGMENTATION ON CACHE BOOL
"BUILD_GENERATELESIONSEGMENTATION")
IF(BUILD_GENERATELESIONSEGMENTATION)
  SUBDIRS(GenerateLesionSegmentation)
ENDIF(BUILD_GENERATELESIONSEGMENTATION)

SET(BUILD_REMAPLABELMAP ON CACHE BOOL
"BUILD_REMAPLABELMAP")
IF(BUILD_REMAPLABELMAP)
  SUBDIRS(RemapLabelMap)
ENDIF(BUILD_REMAPLABELMAP)

SET(BUILD_GENERATENLMFILTEREDIMAGE ON CACHE BOOL
"BUILD_GENERATENLMFILTEREDIMAGE")
IF(BUILD_GENERATENLMFILTEREDIMAGE)
  SUBDIRS(GenerateNLMFilteredImage)
ENDIF(BUILD_GENERATENLMFILTEREDIMAGE)

SET(BUILD_ComputeAirwayWallFromParticles ON CACHE BOOL
"BUILD_ComputeAirwayWallFromParticles")
IF(BUILD_ComputeAirwayWallFromParticles)
  SUBDIRS(ComputeAirwayWallFromParticles)
ENDIF(BUILD_ComputeAirwayWallFromParticles)

