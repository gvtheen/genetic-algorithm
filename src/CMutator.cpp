/******************************************************************************
**
** Copyright (C) 2019-2031 Dr.Gui-lin Zhuang <glzhuang@zjut.edu.cn>
** All rights reserved.
**
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/
#include<cmath>
#include<iostream>
#include "CMutator.h"
#include "GaDeclaration.h"
#include "../Util/log.hpp"
#include "../IACS.h"
#include "../Util/Bitset.h"
#include "../Util/CRandomgenerator.h"

using util::Log;
using util::Bitset;
using namespace GAZJUT;

namespace GAZJUT{

CMutator::CMutator()
:CGaOperatorBase()
{
}

CMutator::~CMutator()
{
}
void CMutator::run( CGpopulation* P_CurrentPopulation )
{
    //util::Log::Info<<"CMutator::run!\n";

    util::CRandomgenerator *Rndgenerator=new util::CRandomgenerator();
    E_CODE_TYPE codeMode         = P_CurrentPopulation->m_pObjGaparameter->CodeMode();
    E_MUTATE_OPERATOR mutateMode = P_CurrentPopulation->m_pObjGaparameter->MutateMode();
                       double Pm = P_CurrentPopulation->m_pObjGaparameter->MutaProb();

    double minV,maxV,expon,b,sumRnd,currentValue;
    for(size_t i=0;i<P_CurrentPopulation->popNum();i++)
    {
       if(codeMode!= REAL ){   //  binary gray code have only 0 and 1 value;
          //util::Log::Info<<i<<"CMutator::run!\n";
          size_t bitnum = (*P_CurrentPopulation)[i].totalbitNum();
          Bitset& currentGeneofGenome = (*P_CurrentPopulation)[i].totalbitGene();
          for(size_t j=0;j<bitnum;j++){
             //util::Log::Info<<j<<"_2-CMutator::run!\n";
             if ( Rndgenerator->uniformRandom01(i*j) > Pm )
                 switch(mutateMode)
                 {
                    case UNIFORM_M:
                         if (currentGeneofGenome[j]== 0)
                             currentGeneofGenome[j]= 1;
                         else
                             currentGeneofGenome[j]= 0;
                         break;
                    case BOUNDARY:
                         if(Rndgenerator->uniformRandom01(i*(j+2)) > 0.5)
                            currentGeneofGenome[j]= 1;
                         else
                            currentGeneofGenome[j]= 0;
                         break;
                    default:
                        break;
                 }
          // util::Log::Info<<j<<"����3-CMutator::run!\n";
          }
          //util::Log::Info<<i<<"4-CMutator::run!\n";
       }else{                      //real gene
           size_t geneNum = (*P_CurrentPopulation)[i].geneNum();
           std::vector <double>& currentGeneofGenome = (*P_CurrentPopulation)[i].totalrealGene();
           std::vector <VarRangeStruct>* varofGenome= (*P_CurrentPopulation)[i].VarRangeStructiable();

           for(size_t j=0;j<geneNum;j++)
             if ( Rndgenerator->uniformRandom01(i*j) > Pm )
               switch((int)mutateMode)
               {
                case NOUNIFORM:
                    minV=(*varofGenome)[j].min;
                    maxV=(*varofGenome)[j].max;
                    b=2.0;
                    expon=b*(1-(double)(P_CurrentPopulation->m_pObjGaparameter->Curr_Generation) \
                                    / P_CurrentPopulation->m_pObjGaparameter->GenerationNum());
                    currentValue=currentGeneofGenome[j];
                    if(Rndgenerator->uniformRandom01(i*j+j+10) < 0.5)
                       currentGeneofGenome[j]= currentValue + (maxV-currentValue)* \
                                                  (1-std::pow(Rndgenerator->uniformRandom01(i*j+10*j),expon));
                    else
                       currentGeneofGenome[j]= currentValue - (currentValue - minV )* \
                                                  (1-std::pow(Rndgenerator->uniformRandom01(i*j+10*j),expon));
                    break;
                case GAUSSIAN_M:
                    minV=(*varofGenome)[j].min;
                    maxV=(*varofGenome)[j].max;
                    sumRnd=0.0;
                    for(size_t k=0;k<12;k++)
                        sumRnd = sumRnd + Rndgenerator->uniformRandom01(i*j+k+10);
                    currentGeneofGenome[j] =(minV+maxV)/2.0+(maxV-minV)*(sumRnd - 6.0)/6.0;
              }
       }
       (*P_CurrentPopulation)[i].updateTotalGeneToIndividualGene();
    }

    delete Rndgenerator;

   // util::Log::Info<<"end CMutator::run!\n";
}


}
