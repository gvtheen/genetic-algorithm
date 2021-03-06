#ifndef CGAPARAMETER_H
#define CGAPARAMETER_H
#include <string>
#include <map>
#include <vector>
#include "GaDeclaration.h"
#include "../IACS.h"
using IACSZJUT::VarRangeStruct;

namespace CALCZJUT{
   class CParameter;
}
namespace GAZJUT{

class CGaparameter
{
    public:

        CGaparameter();
        virtual ~CGaparameter();
        CGaparameter(std::vector <VarRangeStruct>&  myVar);
        CGaparameter( CGaparameter& other);
        //operator
        CGaparameter& operator=( CGaparameter& other);

        void   defaultInit();
        void   output();

        size_t    GenerationNum();
        size_t    PopNum();
        size_t    CrossNum();
        void   add_Curr_Generation();
        //void   SetPopNum(int);
        double CrossProb();
        //void   SetCrossProb(double);
        double MutaProb();
        //void   SetMutaProb(double);

        std::vector <VarRangeStruct>* VarRange();
        void                   setVarRange(std::vector<VarRangeStruct>&);

        void                   checkVarRange();
        std::string            GeneFile();
        std::string            InputFile();
        //void   SetGeneFile(string);
        GAZJUT::E_GA_TYPE      SearchType();
        //void   SetSearchType(E_GA_TYPE);
        E_SELECT_OPERATOR      SelectMode();

        E_CROSSOVER_OPERATOR   CrossMode();
        //void   SetCrossMode(E_CROSSOVER_OPERATOR);
        E_MUTATE_OPERATOR      MutateMode();
        //void   SetMutateMode(E_MUTATE_OPERATOR);
        E_GENEFORMATION_TYPE   InitGenMode();
        //void   SetIntilGenMode(E_GENEFORMATION_TYPE);
        //void   SetEvaluateEXE(E_EVALUATOR_EXE);
        E_SCALING_TYPE         ScalingMode();
        //void   SetScalingMode(E_SCALING_TYPE);
        E_CODE_TYPE            CodeMode();
        //void   SetCodeMode(E_CODE_TYPE);
        //overload operator
        //std::string& operator[](std::string key_name);
        void setKeyValue(const std::string key,const std::string value);
        void setKeyValue(const char* key,const std::string value);
        void setKeyValue(const char* key,const char* value);

        std::string& getKeyValue(const char* key);
        void getKeyValue(std::vector<std::string>& res, const char* key);
        //const parameter
        //scalling
        size_t       Curr_Generation;
        size_t       SelectCUTOFFNum = 5;
        // scale parameters
        const double ScaleLinearMultiplier     = 1.2;
        const double ScaleSigmaTruncMultiplier = 2.0;
        const double ScalePowerLawFactor       = 1.0005;
        const double ScaleBoltzMinTemp         = 1.0;
        const double ScaleBoltzFactor          = 0.05;
        const double ScaleBoltzStart           = 40.0;

        const double UnifArithmCrossConstant   = 0.25;
        const double NoUnifArithmCrossConstant = 0.10;

        std::multimap<std::string, std::string>      *m_mapCmdString;
    private:
        friend class CALCZJUT::CParameter;

        std::vector<VarRangeStruct>     m_VarRangeofPopulation;
//        size_t                   m_PopNum;
//        size_t                   m_GenerationNum;
//        size_t                   m_CrossNum;
//        double                   m_CrossProb;
//	    double                   m_MutaProb;
//	    std::string              m_GeneFile;
//        std::string              m_SearchType;
//	    std::string              m_CrossMode;
//	    std::string              m_MutateMode;
//	    std::string              m_SelectMode;
//	    std::string              m_IntilGenMode;
//	    std::string              m_EvaluateEXE;
//	    std::string              m_ScalingMode;
//	    std::string              m_CodeMode;
};

}
#endif // CGAPARAMETER_H
