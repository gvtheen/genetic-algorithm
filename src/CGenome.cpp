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
#include "CGenome.h"
#include "CRealgene.h"
#include "CGraygene.h"
#include "CBinarygene.h"
#include "GaUtilityFunction.h"
#include "../IACS.h"
#include "../Util/log.hpp"

using util::Log;
using IACSZJUT::VarRangeStruct;

namespace GAZJUT{

CGenome::CGenome()
{
	this->m_geneNum=0;
	this->m_varNumofGenome=0;
	this->m_totalbitNum=0;
	//pointer
}
CGenome::CGenome(std::vector <VarRangeStruct>* vec_genVal,E_CODE_TYPE codeType,size_t index)
{
	this->m_codeType = codeType;
	this->init(vec_genVal);
	this->m_index = index;
}
CGenome::CGenome(CGenome& myGenome)
{
   // util::Log::Info<<"CGenome::CGenome(CGenome& myGenome)!\n";
    this->m_codeType=myGenome.codetype();
	this->init(myGenome.m_VarRangeStructofGenome);
	//util::Log::Info<<"CGenome::CGenome(CGenome& myGenome)-2!\n";
	std::vector <double> realValue;
	myGenome.getDecValue(realValue);
    this->updateDecValueGene(realValue);
    this->m_index = myGenome.index();

    //util::Log::Info<<"end CGenome::CGenome(CGenome& myGenome)!\n";
}
//copy object
CGenome* CGenome::clone()
{
	return new CGenome(*this);
}
///
void CGenome::updateDecValueGene(std::vector <double>& myDecValue)
{
    if( this->m_codeType!=REAL )   //clear all data.
        this->m_totalgeneofGenome.clear();
    else
        this->m_totalRealofGenome.clear();

	for(size_t i=0;i<this->m_geneNum;i++)
    {
        m_Genome[i]->updatecode(myDecValue[i]);
        //collect gene into total gen of genome
        if( this->m_codeType!=REAL )
            this->concatenateBitsets(this->m_totalgeneofGenome,m_Genome[i]->bitGene());
        else
            this->m_totalRealofGenome.push_back(m_Genome[i]->realGene());
    }
}

void CGenome::updateTotalGeneToIndividualGene()
{
    if(this->m_codeType == REAL)
    {
        for(size_t i=0;i<this->m_geneNum;i++)
            m_Genome[i]->realGene()=this->m_totalRealofGenome[i];
    }else{
/*
m_totalgeneofGenome = gene1 gene2 gene3 gene4....geneN;
*/
        //util::Log::Info<<"CGenome::updateTotalGeneToIndividualGene()!\n";
        size_t index=0;
        for(int i=this->m_geneNum-1;i>=0;i--)
        {
             //util::Log::Info<<i<<"  _H_CGenome::updateTotalGeneToIndividualGene()!\n";
             size_t bit_Num = this->m_Genome[i]->bitNum();
            Bitset& bitGene = this->m_Genome[i]->bitGene();
            for(size_t j=0;j<bit_Num;j++)
                bitGene[j]=this->m_totalgeneofGenome[index++];
             //util::Log::Info<<i<<"_2_CGenome::updateTotalGeneToIndividualGene()!\n";
            this->m_Genome[i]->decode();
        }
        //util::Log::Info<<"CGenome::updateTotalGeneToIndividualGene()!\n";
    }
}
void CGenome::getDecValue(std::vector <double>& realValue)
{
//	#ifdef DEBUG
//      Log::Debug<<"*********** CGenome::getDecValue***********"<< std::endl;
//    #endif
	if(realValue.size()>0)
       realValue.clear();

	std::vector<CGenebase*>::iterator it;
	for(it=this->m_Genome.begin(); it<this->m_Genome.end(); it++)
        realValue.push_back((*it)->value());
}
//
void CGenome::setFitness(const double fit)
{
	this->m_fitness=fit;
}
double CGenome::fitness()const
{
	return this->m_fitness;
}
//
void CGenome::setRawScore(const double rawcore)
{
	this->m_rawscore=rawcore;
}
double CGenome::rawscore()const
{
	return this->m_rawscore;
}
//
void CGenome::setOrigValue(const double oriValue)
{
    this->m_origValue = oriValue;
}
double CGenome::origValue()const
{
    return this->m_origValue;
}
//
void  CGenome::setCumufitness(const double value)
{
	this->m_cumufitness=value;
}
double CGenome::cumufitness()const
{
	return this->m_cumufitness;
}
//
double CGenome::relativefitness()const
{
	return this->m_relativefitness;
}
void  CGenome::setRelativefitness(const double value)
{
	this->m_relativefitness=value;
}
//return two type of gene
Bitset& CGenome::totalbitGene()
{
	return this->m_totalgeneofGenome;
}
void CGenome::setTotalbitGene(const Bitset my_totalbitgene)
{
    this->m_totalgeneofGenome = my_totalbitgene;
    this->updateTotalGeneToIndividualGene();
}

//
std::vector <double>& CGenome::totalrealGene()
{
    return this->m_totalRealofGenome;
}
void CGenome::setTotalrealGene(std::vector <double>& my_totalrealgene)
{
    this->m_totalRealofGenome.assign(my_totalrealgene.begin(),my_totalrealgene.end());
    this->updateTotalGeneToIndividualGene();
}

//
size_t CGenome::geneNum()const
{
	return this->m_geneNum;
}
size_t CGenome::totalbitNum()const
{
	return this->m_totalbitNum;
}
std::vector <VarRangeStruct>* CGenome::VarRangeStructiable()
{
    return this->m_VarRangeStructofGenome;
}
CGenebase* CGenome::extractGene(int i)
{
	if(i<0)
	{
	    Log::Error<<i <<" is error! CGenome_extractGene"<<std::endl;
	    boost::throw_exception(std::runtime_error("i<0. CGenome_extractGene!\n"));
	}
	return this->m_Genome[i];
}
void  CGenome::insertGeneToGenome(CGenebase* mygene)
{
	this->m_geneNum=this->m_geneNum+1;
	this->m_totalbitNum=this->m_geneNum + mygene->bitNum();
	this->m_Genome.push_back(mygene);
	this->m_VarRangeStructofGenome->push_back(*(mygene->m_VarRangeStruct));

	if(mygene->codeType!= REAL)
	  this->concatenateBitsets(this->m_totalgeneofGenome,mygene->bitGene());
    else
      this->m_totalRealofGenome.push_back(mygene->m_value);

}
bool CGenome::isNormalFinish()const
{
    return this->FinishState;
}
void CGenome::setFinishState(bool stat)
{
    this->FinishState = stat;
}
//
size_t CGenome::index()const
{
   return this->m_index;
}
void CGenome::setIndex(size_t m)
{
    this->m_index=m;
}
//
/*
according to the gene-variable array, all of gene objects were initialized
*/
void CGenome::init()
{
    assert(this->m_VarRangeStructofGenome);

    this->init(this->m_VarRangeStructofGenome);
}
void CGenome::init(std::vector <VarRangeStruct>* vec_genVal)
{
	this->m_varNumofGenome=vec_genVal->size();
	this->m_geneNum=this->m_varNumofGenome;
	this->m_totalbitNum=0;

    // set gene-variable array to vector of gene-var
    this->m_VarRangeStructofGenome = vec_genVal;//.assign(vec_genVal.begin(),vec_genVal.end());
    //util::Log::Info<<"CGenome::init(std::vector <VarRangeStruct>& vec_genVal)!\n";

    for(size_t i=0;i<this->m_varNumofGenome;i++)
	{
	    //util::Log::Info<<i<<"   CGenome::init(std::vector <VarRangeStruct>& vec_genVal)!\n";
	    if (this->m_codeType==BINARY){
             //util::Log::Info<<i<<" 1  CGenome::init(std::vector <VarRangeStruct>& vec_genVal)!\n";
	         m_Genome.push_back( new CBinarygene(&(*vec_genVal)[i]));
        }else if (this->m_codeType==GRAY){
            //util::Log::Info<<i<<" 2  CGenome::init(std::vector <VarRangeStruct>& vec_genVal)!\n";
             m_Genome.push_back( new CGraygene(&(*vec_genVal)[i]));
        }else{
             //util::Log::Info<<i<<" 3  CGenome::init(std::vector <VarRangeStruct>& vec_genVal)!\n";
             m_Genome.push_back( new CRealgene(&(*vec_genVal)[i]));
        }
        if( this->m_codeType!=REAL ){
              this->concatenateBitsets(this->m_totalgeneofGenome,m_Genome[i]->bitGene());
        }else
              m_totalRealofGenome.push_back(m_Genome[i]->realGene());
	}
	this->m_totalbitNum = m_totalgeneofGenome.size();
	//util::Log::Info<<"end CGenome::init(std::vector <VarRangeStruct>& vec_genVal)!\n";
}
void CGenome::concatenateBitsets(Bitset& first, const Bitset& second)
{
    Bitset secondCopy(second);
    secondCopy.resize(first.size() + second.size());
    //Increase the size of the bit buffer to fit the data being placed in it
    first.resize(first.size() + second.size());
    //shift the bits in the firstCopy to the left
    first <<= second.size();
    //"copy" the bits from the secondCopy into the firstCopy
    first |= secondCopy;
/*
  gene1=1010
  gene2=0111
  after doing concatenateBitsets(gene1,gene2)
  gene1=10100111  // gene1 =  original gene1 + gene2;
*/
}
// operator
bool CGenome::operator==(CGenome& myGenome)
{
	if (this->m_geneNum!=myGenome.geneNum() || ( this->m_codeType!=REAL && \
                                             this->m_totalbitNum!=myGenome.totalbitNum()) )
	   return false;
    if(m_totalgeneofGenome == myGenome.totalbitGene())
       return true;
    else
	   return false;
}
bool CGenome::operator ^= (CGenome& myGenome)
{
	bool res=true;
	std::vector <double> V_left, V_right;
	double tmp;
	double COMPARE_RADIO=0.05;
	if (this->m_geneNum!=myGenome.geneNum() || ( this->m_codeType!=REAL && \
                                             this->m_totalbitNum!=myGenome.totalbitNum()) )
		return false;

	this->getDecValue(V_left);
	myGenome.getDecValue(V_right);

	for(unsigned int i=0;i<V_left.size();i++)
	{
		 tmp= ( V_left[i] > V_right[i] )? V_left[i] : V_right[i];
		 tmp=fabs(V_left[i] - V_right[i])/tmp;
		 if(tmp > COMPARE_RADIO){
		 	res=false;
		 	break;
		 }
	}
	return res;
}
double CGenome::operator [] (size_t index)
{
    assert(index < this->geneNum());

    return this->m_Genome[index]->value();
}
double CGenome::operator[](std::string index_name)
{
	if(index_name=="rawscore")
	   return this->m_rawscore;
	else if(index_name=="fitness")
	   return this->m_fitness;
	else if(index_name=="origvalue")
	   return this->m_origValue;
	else{
	   Log::Error<<" str of [] can not match! CGenome_[]operator!\n";
	   boost::throw_exception(std::runtime_error("str of [] can not match! CGenome_[]operator!\n"));
	}
}
CGenome& CGenome::operator=(CGenome& _mbf)
{
    //util::Log::Info<<"CGenome::operator =!\n";

    if(this == &_mbf)
        return *this;
    if(this->m_Genome.size()>0){
        for(size_t i=0;i<this->m_Genome.size();i++)
            delete this->m_Genome[i];
    }
    this->m_Genome.clear();
    for(size_t i=0;i<_mbf.geneNum();i++)
        this->m_Genome.push_back(_mbf.extractGene(i)->clone());
    this->m_geneNum = _mbf.geneNum();
    this->m_fitness = _mbf.fitness();
    this->m_origValue = _mbf.origValue();
    this->m_rawscore = _mbf.rawscore();
    this->m_cumufitness = _mbf.cumufitness();
    this->m_relativefitness = _mbf.relativefitness();

    this->m_codeType = _mbf.codetype();
    this->FinishState = _mbf.isNormalFinish();

    this->m_totalbitNum = _mbf.totalbitNum();
    this->m_VarRangeStructofGenome=_mbf.VarRangeStructiable();
    this->m_index = _mbf.index();

    this->m_totalgeneofGenome =  _mbf.totalbitGene();
    this->m_totalRealofGenome.clear();
    for(size_t i=0;i<_mbf.geneNum();i++)
        this->m_totalRealofGenome.push_back(_mbf[i]);
    this->m_varNumofGenome=this->m_VarRangeStructofGenome->size();

    return *this;
}
E_CODE_TYPE CGenome::codetype()
{
    return this->m_codeType;
}
CGenome::~CGenome()
{
	for(size_t i=0;i<m_Genome.size();i++)
        delete m_Genome[i];
	m_Genome.clear();
	//m_VarRangeStructofGenome.clear();
	m_totalRealofGenome.clear();
	m_totalgeneofGenome.clear();
}

}
