//GetTransformationSimilarityMetric3D

/** \file
 *  \ingroup commandLineTools 
 *  \details This program computes the similarity between a fixed image and a moving image following
 *           the application of one or multiple transformations (defined by .tfm files).
 *
 *  $Date: $
 *  $Revision: $
 *  $Author:  $
 *
 */



#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRegularStepGradientDescentOptimizer.h"
#include "itkResampleImageFilter.h"
#include "itkImageRegistrationMethod.h"
#include "itkCenteredTransformInitializer.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkKappaStatisticImageToImageMetric.h"
#include "itkAffineTransform.h"
#include "itkTransformFileWriter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkIdentityTransform.h"
#include "itkCIPExtractChestLabelMapImageFilter.h"
#include "GetTransformationSimilarityMetric3DCLP.h"
#include "cipConventions.h"
#include "cipHelper.h"
#include <sstream>

#include "itkImageSeriesReader.h"
#include "itkGDCMImageIO.h"
#include "itkGDCMSeriesFileNames.h"
#include <fstream>
#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageRegionIterator.h"
#include "itkRegionOfInterestImageFilter.h"
#include "itkCIPExtractChestLabelMapImageFilter.h"
#include "itkMutualInformationImageToImageMetric.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xinclude.h>
#include <libxml/xmlIO.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include "itkTransformFactory.h"
#include "itkTransformFileReader.h"
#include "itkTransformFactoryBase.h"
#include "itkNormalizedMutualInformationHistogramImageToImageMetric.h"
#include "itkImageMaskSpatialObject.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkKappaStatisticImageToImageMetric.h"
#include "itkGradientDifferenceImageToImageMetric.h"
#include "itkNormalizedCorrelationImageToImageMetric.h"
#include <itkSubsample.h>
#include <itkCompositeTransform.h>
#include <itkAffineTransform.h>
#include "itkResampleImageFilter.h"

namespace
{
#define MY_ENCODING "ISO-8859-1"

typedef itk::Image< unsigned short, 3 >                                                                UnsignedShortImageType;
typedef itk::Image< short, 3 >                                                                         ShortImageType;
typedef itk::ImageFileReader< ShortImageType >                                                         ShortReaderType;
typedef itk::ImageFileReader< UnsignedShortImageType >                                                 ImageReaderType;
typedef itk::RegularStepGradientDescentOptimizer                                                       OptimizerType;
typedef itk::ImageRegistrationMethod< ShortImageType, ShortImageType >                                 RegistrationType;
typedef itk::NearestNeighborInterpolateImageFunction< ShortImageType, double >                         InterpolatorType;
typedef itk::AffineTransform<double, 3 >                                                               TransformType;
typedef itk::CenteredTransformInitializer< TransformType, ShortImageType, ShortImageType >             InitializerType;
typedef OptimizerType::ScalesType                                                                      OptimizerScalesType;
typedef itk::ImageRegionIteratorWithIndex< UnsignedShortImageType >                                    IteratorType;
typedef itk::ImageRegionIteratorWithIndex< ShortImageType >                                            CTIteratorType;
typedef itk::RegionOfInterestImageFilter< ShortImageType, ShortImageType >                             RegionOfInterestType;
typedef itk::ResampleImageFilter< ShortImageType, ShortImageType >                                     ResampleType;
typedef itk::IdentityTransform< double, 3 >                                                            IdentityType;
typedef itk::CIPExtractChestLabelMapImageFilter                                                        LabelMapExtractorType;
typedef itk::ImageSeriesReader< cip::CTType >                                                          CTSeriesReaderType;
typedef itk::GDCMImageIO                                                                               ImageIOType;
typedef itk::GDCMSeriesFileNames                                                                       NamesGeneratorType;
typedef itk::ImageFileReader< cip::CTType >                                                            CTFileReaderType;
typedef itk::ImageRegionIteratorWithIndex< cip::LabelMapType >                                         LabelMapIteratorType;
typedef itk::MutualInformationImageToImageMetric<ShortImageType, ShortImageType >                      MIMetricType;
typedef itk::NormalizedMutualInformationHistogramImageToImageMetric< ShortImageType, ShortImageType >  NMIMetricType;
typedef itk::MeanSquaresImageToImageMetric<  ShortImageType, ShortImageType  >                         msqrMetricType;
typedef itk::NormalizedCorrelationImageToImageMetric<ShortImageType, ShortImageType  >                 ncMetricType;
typedef itk::GradientDifferenceImageToImageMetric<ShortImageType, ShortImageType  >                  gdMetricType;
typedef itk::CompositeTransform< double, 3 > CompositeTransformType;
typedef itk::ImageFileWriter< ShortImageType >  WriterType;

struct REGIONTYPEPAIR
{
  unsigned char region;
  unsigned char type;
};

//struct for saving the xml file wih similarity information
struct SIMILARITY_XML_DATA
{
  float similarityValue;
  std::string transformationLink[5];
  std::string transformation_isInverse[5];
  unsigned int transformation_order[5];
  std::string fixedID;
  std::string movingID;
  std::string similarityMeasure;
  std::string regionAndTypeUsed;
};


//Reads a .tfm file and returns an itkTransform
TransformType::Pointer GetTransformFromFile( std::string fileName )
{
    itk::TransformFileReader::Pointer transformReader = itk::TransformFileReader::New();
    transformReader->SetFileName( fileName );
        try
        {
            transformReader->Update();
        }
        catch ( itk::ExceptionObject &excp )
        {
            std::cerr << "Exception caught reading transform:";
            std::cerr << excp << std::endl;
        }
        
        itk::TransformFileReader::TransformListType::const_iterator it;
        
        it = transformReader->GetTransformList()->begin();
        
        TransformType::Pointer transform = static_cast< TransformType* >( (*it).GetPointer() );
        
        return transform;
}
    
cip::LabelMapType::Pointer ReadLabelMapFromFile( std::string labelMapFileName )
{
  std::cout << "Reading label map..." << std::endl;
  cip::LabelMapReaderType::Pointer reader = cip::LabelMapReaderType::New();
  reader->SetFileName( labelMapFileName );
  try
    {
    reader->Update();
    }
  catch ( itk::ExceptionObject &excp )
    {
    std::cerr << "Exception caught reading label map:";
    std::cerr << excp << std::endl;
    }

  return reader->GetOutput();
}


ShortImageType::Pointer ReadCTFromFile( std::string fileName )
{
  ShortReaderType::Pointer reader = ShortReaderType::New();
    reader->SetFileName( fileName );
  try
    {
    reader->Update();
    }
  catch ( itk::ExceptionObject &excp )
    {
    std::cerr << "Exception caught reading CT image:";
    std::cerr << excp << std::endl;
    return NULL;
    }

  return reader->GetOutput();
}

//writes the similarity measures to an xml file
// the similarity info is stored in the SIMILARITY_XML_DATA struct
void WriteMeasuresXML(const char *file, SIMILARITY_XML_DATA &theXMLData)
{      
  std::cout<<"Writing similarity XML file"<<std::endl;
  xmlDocPtr doc = NULL;       /* document pointer */
  xmlNodePtr root_node = NULL; /* Node pointers */
  xmlDtdPtr dtd = NULL;       /* DTD pointer */
    

  xmlNodePtr transfo_node[5];
    
  for(int i = 0; i< 5; i++)
        transfo_node[i]= NULL;


  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST "Inter_Subject_Measure");
  xmlDocSetRootElement(doc, root_node);

  dtd = xmlCreateIntSubset(doc, BAD_CAST "root", NULL, BAD_CAST "InterSubjectMeasures_v2.dtd");
 
  // xmlNewChild() creates a new node, which is "attached"
  // as child node of root_node node. 
  std::ostringstream similaritString;
  //std::string tempsource;
  similaritString <<theXMLData.similarityValue;
  
  xmlNewChild(root_node, NULL, BAD_CAST "movingID", BAD_CAST (theXMLData. movingID.c_str()));
  xmlNewChild(root_node, NULL, BAD_CAST "fixedID", BAD_CAST (theXMLData.fixedID.c_str()));
  xmlNewChild(root_node, NULL, BAD_CAST "SimilarityMeasure", BAD_CAST (theXMLData.similarityMeasure.c_str()));
  xmlNewChild(root_node, NULL, BAD_CAST "SimilarityValue", BAD_CAST (similaritString.str().c_str()));
  xmlNewChild(root_node, NULL, BAD_CAST "regionAndTypeUsed", BAD_CAST (theXMLData.regionAndTypeUsed.c_str()));
  
    for(int i = 0; i<5; i++)
    {
        if (!theXMLData.transformationLink[i].empty())
        {
            transfo_node[i] = xmlNewChild(root_node, NULL, BAD_CAST "transformation", BAD_CAST (""));
            xmlNewChild(transfo_node[i], NULL, BAD_CAST "transformation_file", BAD_CAST (theXMLData.transformationLink[i].c_str()));
            xmlNewChild(transfo_node[i], NULL, BAD_CAST "transformation_isInverse", BAD_CAST (theXMLData.transformation_isInverse[i].c_str()));
            std::ostringstream order_string;
            order_string << theXMLData.transformation_order[i];
            xmlNewChild(transfo_node[i], NULL, BAD_CAST "transformation_order", BAD_CAST (order_string.str().c_str()));
        }
    }
    
  xmlSaveFormatFileEnc(file, doc, "UTF-8", 1);
  xmlFreeDoc(doc);

}

} //end namespace

int main( int argc, char *argv[] )
{
   std::vector< unsigned char >  regionVec;
   std::vector< unsigned char >  typeVec;
   std::vector< unsigned char >  regionPairVec;
   std::vector< unsigned char >  typePairVec;
   const char* similarity_type;
  
  // std::cout<< "about to parse args"<<std::endl;

  PARSE_ARGS;

 
  //Read in region and type pair
  std::vector< REGIONTYPEPAIR > regionTypePairVec;
 

  //Read in fixed image label map from file and subsample
  cip::LabelMapType::Pointer fixedLabelMap = cip::LabelMapType::New();
  cip::LabelMapType::Pointer subSampledFixedImage = cip::LabelMapType::New();
  if ( strcmp( fixedLabelmapFileName.c_str(), "q") != 0 )
    {
    std::cout << "Reading label map from file..." << std::endl;
    fixedLabelMap = ReadLabelMapFromFile( fixedLabelmapFileName );

    if (fixedLabelMap.GetPointer() == NULL)
      {
      return cip::LABELMAPREADFAILURE;
      }
    }
  else
    {
    std::cout <<"No  label map specified"<< std::endl;
    }
  

  //If specified, read in moving image label map from file and subsample
  typedef itk::ImageMaskSpatialObject< 3 >   MaskType;
  MaskType::Pointer  spatialObjectMask = MaskType::New();
  cip::LabelMapType::Pointer movingLabelMap = cip::LabelMapType::New();
  cip::LabelMapType::Pointer subSampledMovingImage = cip::LabelMapType::New();
    
  if ( strcmp( movingLabelmapFileName.c_str(), "q") != 0 )
    {

    movingLabelMap = ReadLabelMapFromFile( movingLabelmapFileName );
        
    if (movingLabelMap.GetPointer() == NULL)
      {
      return cip::LABELMAPREADFAILURE;
      }
    }
  else
    {
    std::cout <<"No  label map specified"<< std::endl;
    }
    
    //Read the CT images
  ShortImageType::Pointer ctFixedImage = ShortImageType::New();
  ctFixedImage = ReadCTFromFile( fixedCTFileName );
  if (ctFixedImage.GetPointer() == NULL)
      {
        return cip::NRRDREADFAILURE;
      }



  ShortImageType::Pointer ctMovingImage = ShortImageType::New();
  ctMovingImage = ReadCTFromFile( movingCTFileName);
  if (ctMovingImage.GetPointer() == NULL)
      {
        return cip::NRRDREADFAILURE;
      }

   //Set mask  object

  typedef itk::Image< unsigned char, 3 >   ImageMaskType;
  typedef itk::ImageFileReader< ImageMaskType >    MaskReaderType;
  MaskReaderType::Pointer  maskReader = MaskReaderType::New();
  
  if ( strcmp( movingLabelmapFileName.c_str(), "q") != 0 )
    {
      maskReader->SetFileName(movingLabelmapFileName.c_str() );

      try
	{
	  maskReader->Update();
	}
      catch( itk::ExceptionObject & err )
	{
	  std::cerr << "ExceptionObject caught !" << std::endl;
	  std::cerr << err << std::endl;
	  return EXIT_FAILURE;
	}
      spatialObjectMask->SetImage(maskReader->GetOutput());

    }

  //parse transform arg  and join transforms together
  
   //last transform applied first, so make last transform
    CompositeTransformType::Pointer transform = CompositeTransformType::New();
    TransformType::Pointer transformTemp2 = TransformType::New();
    for ( unsigned int i=0; i<inputTransformFileName.size(); i++ )
      {

        TransformType::Pointer transformTemp = TransformType::New();
        transformTemp = GetTransformFromFile(inputTransformFileName[i] );
        // Invert the transformation if specified by command like argument. Only inverting the first transformation
        if((i==0)&& (isInvertTransform == true))
        {
          transformTemp->SetMatrix( transformTemp->GetInverseMatrix());
          transform->AddTransform(transformTemp);
        }
            
        else
          transform->AddTransform(transformTemp);
       
      }

    transform->SetAllTransformsToOptimizeOn();

  OptimizerScalesType optimizerScales( transform->GetNumberOfParameters() );
  optimizerScales[0] =  1.0;   optimizerScales[1] =  1.0;   optimizerScales[2] =  1.0;
  optimizerScales[3] =  1.0;   optimizerScales[4] =  1.0;   optimizerScales[5] =  1.0;
  optimizerScales[6] =  1.0;   optimizerScales[7] =  1.0;   optimizerScales[8] =  1.0;
  optimizerScales[9]  =  0.001;
  optimizerScales[10] =  0.001;
  optimizerScales[11] =  0.001;


  InterpolatorType::Pointer interpolator = InterpolatorType::New();
  std::cout<<"initializing optimizer"<<std::endl;
  OptimizerType::Pointer optimizer = OptimizerType::New();
  optimizer->SetNumberOfIterations( 0 ); //0 good
    
  ShortImageType::SpacingType spacing;
  ShortImageType::SizeType    size;
  ShortImageType::PointType   origin;
    
  spacing = ctFixedImage->GetSpacing();
  size    = ctFixedImage->GetLargestPossibleRegion().GetSize();
  origin  = ctFixedImage->GetOrigin();
    
    
   
  RegistrationType::Pointer registration = RegistrationType::New();
  registration->SetOptimizer( optimizer );
  registration->SetInterpolator( interpolator );
  registration->SetTransform(transform);
  registration->SetFixedImage( ctFixedImage);

  registration->SetMovingImage(ctMovingImage);
  registration->SetInitialTransformParameters( transform->GetParameters());

    
  std::cout<<"initializing metric"<<std::endl;
 
    if (similarityMetric =="NMI")
    {
      NMIMetricType::Pointer metric = NMIMetricType::New();
      NMIMetricType::HistogramType::SizeType histogramSize;
      histogramSize.SetSize(2);
      histogramSize[0] = 20;
      histogramSize[1] = 20;
      metric->SetHistogramSize( histogramSize );

      if ( strcmp( movingLabelmapFileName.c_str(), "q") != 0 )
            metric->SetMovingImageMask( spatialObjectMask );
      registration->SetMetric( metric );
     
    }
    else if (similarityMetric =="msqr")
      {
    	msqrMetricType::Pointer metric = msqrMetricType::New();
        registration->SetMetric( metric );
      }
    else if (similarityMetric =="nc")
      {
          ncMetricType::Pointer metric = ncMetricType::New();
          if ( strcmp( movingLabelmapFileName.c_str(), "q") != 0 )
              metric->SetMovingImageMask( spatialObjectMask );
        registration->SetMetric( metric );
      }
    else if (similarityMetric =="gd")
      {
	     gdMetricType::Pointer metric = gdMetricType::New();
         registration->SetMetric( metric );
      }
   else //MI is default
     {
        MIMetricType::Pointer metric = MIMetricType::New();
        metric->SetFixedImageStandardDeviation( 13.5 );
        metric->SetMovingImageStandardDeviation( 13.5 );
         
        if ( strcmp( movingLabelmapFileName.c_str(), "q") != 0 )
          metric->SetMovingImageMask( spatialObjectMask );
        registration->SetMetric( metric );       	
     }
 
    similarity_type = registration->GetMetric()->GetNameOfClass();
    std::cout << "Similarity metric used, new: "<<similarity_type<<std::endl;
 
  try
    {
        registration->Initialize();
        registration->Update();
    }
  catch( itk::ExceptionObject &excp )
    {
      std::cerr << "ExceptionObject caught while executing registration" <<
      std::endl;
      std::cerr << excp << std::endl;
    }

  OptimizerType::ParametersType finalParams = registration->GetLastTransformParameters();
  int numberOfIterations2 = optimizer->GetCurrentIteration();
  const double similarityValue = registration->GetMetric()->GetValue(finalParams);
  std::cout<<" iteration = "<<numberOfIterations2<<"  metric="<<similarityValue<<std::endl;
    
    
  SIMILARITY_XML_DATA ctSimilarityXMLData;
  ctSimilarityXMLData.regionAndTypeUsed.assign("");

  ctSimilarityXMLData.similarityValue = (float)(similarityValue);
  
  ctSimilarityXMLData.similarityMeasure.assign(similarity_type);
    
    
  
  // Prepare the transformation filename 
  if ( strcmp(inputTransformFileName[0].c_str(), "q") != 0 )
    {
      std::string infoFilename = inputTransformFileName[0];
      int result = infoFilename.find_last_of('.');
      if (std::string::npos != result)
	{
	  infoFilename.erase(result);

	}
      // append extension:
      infoFilename.append("_measures.xml");
      
      if ( strcmp(outputXMLFileName.c_str(), "q") != 0 )  
	{
	  infoFilename.assign(outputXMLFileName.c_str());
	}
      int pathLength = 0, pos=0, next=0;   
      
      if ( strcmp(movingImageID.c_str(), "q") != 0 ) 
	{
	  ctSimilarityXMLData.movingID.assign(movingImageID);

	}
      else
	{       
	  //first find length of path
	  next=1;
	  while(next>=1)
	    {
	      next = movingCTFileName.find("/", next+1);    
	      pathLength++;
	    }
	  pos=0;
	  next=0;
	  
	  std::string tempSourceID;
	  for (int i = 0; i < (pathLength-1);i++)
	    {
	      pos= next+1;
	      next = movingCTFileName.find("/", next+1);
	    }               

	  ctSimilarityXMLData.movingID.assign(movingCTFileName.c_str());
	  ctSimilarityXMLData.movingID.erase(next,ctSimilarityXMLData.movingID.length()-1);
	  ctSimilarityXMLData.movingID.erase(0, pos);
	}
      
      if ( strcmp(fixedImageID.c_str(), "q") != 0 ) 
	{

	  ctSimilarityXMLData.fixedID =fixedImageID.c_str();
	}
    else

	{ 
	  pos=0;
	  next=0;
	  for (int i = 0; i < (pathLength-1);i++)
	    { 
	      pos = next+1;
	      next = fixedCTFileName.find('/', next+1);  
	    }

	  ctSimilarityXMLData.fixedID.assign(fixedCTFileName.c_str());
      ctSimilarityXMLData.fixedID.erase(next,ctSimilarityXMLData.fixedID.length()-1);
	  ctSimilarityXMLData.fixedID.erase(0, pos );
        }	
	    
      //remove path from output transformation file before storing in xml
      //For each transformation
      for ( unsigned int i=0; i<inputTransformFileName.size(); i++ )
      { 
          pos=0;
          next=0;
          for (int ii = 0; ii < (pathLength);ii++)
          {
            pos = next+1;
              next = inputTransformFileName[0].find('/', next+1);
          }
          ctSimilarityXMLData.transformationLink[i].assign(inputTransformFileName[i].c_str());
          ctSimilarityXMLData.transformation_order[i]= i;
          if((i==0)&& (isInvertTransform == true))
              ctSimilarityXMLData.transformation_isInverse[i].assign("True");
          else
              ctSimilarityXMLData.transformation_isInverse[i].assign("False");
          ctSimilarityXMLData.transformationLink[i].erase(0,pos);
      }

      
      
      std::cout<<"saving output to: "<<infoFilename.c_str()<<std::endl;
      WriteMeasuresXML(infoFilename.c_str(), ctSimilarityXMLData);

    }
 
  return 0;

}
